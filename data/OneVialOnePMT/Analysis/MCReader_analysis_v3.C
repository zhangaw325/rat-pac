#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include <RAT/DS/Run.hh>
#include <RAT/DS/PMTInfo.hh>
#include <RAT/DS/Root.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DS/MCParticle.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/PMT.hh>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TApplication.h>

//this version is used to read multiple TTrees from the simulation

int main(int argc, char **argv) {

    if (argc != 2 ) {
        cout << "Usage: ./MCReader_analysis_v3 output.root " << endl;
    }

    string dir = "/media/sf_E_DRIVE/Research/BNL-EDG/Simulation/OneVialOnePMT/Analysis/";     //directory that contains the ROOT Tree files
    const int numberofinputfiles = 1; 
    //argv[3] is the output root file. Note ONLY ONE root file is output
    string inputrootfile[numberofinputfiles];
    inputrootfile[0]=dir+"Gamma_4400keV_5WbLS_perpendicular1.root";

    //prepare histograms etc and output root file
    //my trigger types, in the simulation I can set two trigger types:
    //1 - plastic trigger, 2 - multiplicity trigger, 3 - either trigger is counted
    int triggertype[3]={1, 2, 3};
    string strig[3]={"hodoscope","multiplicity","all"};
    double edepcut = 0.5; // 0.5 MeV cut
    
    TFile* foutroot = new TFile(argv[1],"recreate");
    const int pmtnb = 1;
    TH1F* hCharge[pmtnb][3];
    TH1F* hTime[pmtnb][3];
    TH2F* hCharge_vs_Time[pmtnb][3];
    TH2F* hPMTChargeMap = new TH2F("PMTChargeMap","",20,-520,520,20,-520,520);
    TH2F* hPMTChargeMapAverage = new TH2F("PMTChargeMap_npe","",20,-520,520,20,-520,520);
    TH2F* hPMTChargeMap_Hodo =  new TH2F("PMTChargeMap_hodo","",20,-520,520,20,-520,520);
    TH2F* hPMTChargeMap_HodoAverage =  new TH2F("PMTChargeMap_hodo_npe","",20,-520,520,20,-520,520);
    TH2F* hPMTChargeMap_MultiAverage =  new TH2F("PMTChargeMap_MultiTrig_npe","",20,-520,520,20,-520,520);
    TH1F* hNumberOfHittingPMTs=new TH1F("NbOfHitPMT","",401,-0.5,400.5);
    TH2F* hTotalChargeVsNHit = new TH2F("TotalChargeVsNHit","",100000,0,10000,401,-0.5,400.5); hTotalChargeVsNHit->SetXTitle("npe"); hTotalChargeVsNHit->SetYTitle("Counts");
    TH2F* hTotalChargeVsNHit_Hodo = new TH2F("TotalChargeVsNHit_Hodo","",100000,0,10000,401,-0.5,400.5); hTotalChargeVsNHit_Hodo->SetXTitle("npe"); hTotalChargeVsNHit_Hodo->SetYTitle("Counts");
    TH2F* hPMTTimeMapAverage = new TH2F("PMTTimeMapAvg","",20,-520,520,20,-520,520);
    TH2F* hPMTTimeMapAverage_hodo = new TH2F("PMTTimeMapAvg_hodo","",20,-520,520,20,-520,520);
//    TH2F* hPMTTimeVsNHit = new TH2F("PMTTimeVsNHit","",100000,0,10000,401,-0.5,400.5);
    TGraph* gMaxQvsEnergy = new TGraph();
    TGraph* gTotQvsEnergy = new TGraph();
    TH1F* hMaxQ = new TH1F("hMaxQ","",10000,0,5000);
    TH1F* hTotQ = new TH1F("hTotQ","",70000,0,70000);

    char hName[50];
    TH1F* hEdepInPS[6][3];
    TH1F* hHitTimeInPS[6][3];
    bool ispstrigger = false, ismultitrigger = false;

    double pmtchargeholder[pmtnb];
    double pmttimeholder[pmtnb];
    int pmtidholder[pmtnb];
    float pmt_x[pmtnb], pmt_y[pmtnb];
    //fstream fin_pmtpos("PMTpos_check_8PMTs.txt",ios::in);
    //for(int i=0; i<pmtnb; i++) {fin_pmtpos>>pmt_x[i]>>pmt_y[i];}
    pmt_x[0] = 0.0; pmt_y[0]=0.0;

    for(int i=0; i<6; i++){
        for(int j=0;j<3;j++){
            sprintf(hName,"hEdepInPs_%d_%sTrig",i,strig[j].c_str());
            //cout<<hName<<endl;
            hEdepInPS[i][j]=new TH1F(hName,"",500,0,10);
            hEdepInPS[i][j]->SetXTitle("Energy (MeV)");
            hEdepInPS[i][j]->SetYTitle("Counts");
            sprintf(hName,"hHitTimeInPs_%d_%sTrig",i,strig[j].c_str());
            //cout<<hName<<endl;
            hHitTimeInPS[i][j]=new TH1F(hName,"",500,0,10000);
            hHitTimeInPS[i][j]->SetXTitle("Time ()");
            hHitTimeInPS[i][j]->SetYTitle("Counts");
        }
    }
    for(int i=0; i<pmtnb; i++){
        for(int j=0;j<3;j++){
            sprintf(hName,"hCharge_S%d_%sTrig",i,strig[j].c_str());
            //cout<<hName<<endl;
            hCharge[i][j] = new TH1F(hName,"",4000*4,0,4000*2);
            hCharge[i][j]->SetXTitle("npe");
            hCharge[i][j]->SetYTitle("Counts");
            sprintf(hName,"hTime_S%d_%sTrig",i,strig[j].c_str());
            //cout<<hName<<endl;
            hTime[i][j]=new TH1F(hName,"",1000,0,50);
            hTime[i][j]->SetXTitle("Time");
            hTime[i][j]->SetYTitle("Counts");
            sprintf(hName,"hCharge_vs_Time_S%d_%sTrig",i,strig[j].c_str());
            //cout<<hName<<endl;
            hCharge_vs_Time[i][j]=new TH2F(hName,"",1000,0,50,5000,0,500);
            hCharge_vs_Time[i][j]->SetXTitle("Time");
            hCharge_vs_Time[i][j]->SetYTitle("npe");
        }
    }

    fstream fout("testout1.txt",ios::out);
    TCanvas* c; 
    TGraph2D* gTest = new TGraph2D();
    int graphcnt=0;
    int hodotrigcnts = 0;
    //end preparing histograms etc and output root file

    TFile* f;
    TTree* T;
    TTree* runT;

for(int ffff=0; ffff<numberofinputfiles; ffff++){ // start loop reading the root tree files
    //open the root file
     // if(ffff!=0 && ffff!=2) continue;
    f = new TFile(inputrootfile[ffff].c_str(),"read");
    std::cout<<"Reading "<<inputrootfile[ffff]<<std::endl;
    T = (TTree*) f->Get("T");
    runT = (TTree*) f->Get("runT");
    
    RAT::DS::Run *run = new RAT::DS::Run();
    runT->SetBranchAddress("run", &run);
    if (runT->GetEntries() != 1) {
        cout << "Funny run tree, aborting" << endl;
        return -1;
    }
    runT->GetEntry(0);
    RAT::DS::PMTInfo *pmtinfo = run->GetPMTInfo();
    
    RAT::DS::Root *ds = new RAT::DS::Root();
    T->SetBranchAddress("ds", &ds);
    
    int nEvents = T->GetEntries();
    cout << "Reading in " << nEvents << " events" << endl;

    bool flag=false;
    //reading in events
    for (int i = 0; i < nEvents; i++) { //atoi(argv[3]) nEvents
        //if(flag==true) {std::cout<<"This is event number "<<i<<std::endl; break;}
        if(i%1==0) cout<<"Event "<<i<<endl;
        T->GetEntry(i);
        if (ds->GetEVCount() != 1) {
            cout << "EV " << i << " is multi-trigger, ignoring" << endl;
            continue;
        }
        
        RAT::DS::MC *mc = ds->GetMC();
        RAT::DS::EV *ev = ds->GetEV(0);

        //cout<<"tcharge "<<ev->GetTotalCharge()<<endl;
        std::vector<int> myTriggerFlag = ev->GetTriggerFlag();
        std::vector<double> myTriggerEdep = ev->GetTriggerEdep();
        std::vector<double> myTriggerHitTime = ev->GetTriggerHitTime();

        int nPrim = mc->GetMCParticleCount();
        int npe = mc->GetNumPE();
        //MCParticle
        TVector3 evpos = mc->GetMCParticle(0)->GetPosition(); // in millimeter
        int pdgcode = mc->GetMCParticle(0)->GetPDGCode();
        string particlename = mc->GetMCParticle(0)->GetParticleName();
        float evtime = mc->GetMCParticle(0)->GetTime();
        float ke = mc->GetMCParticle(0)->GetKE(); // in MeV
        TVector3 momentum = mc->GetMCParticle(0)->GetMomentum(); // in MeV/c
        TVector3 polarization = mc->GetMCParticle(0)->GetPolarization(); // 
        //MCSummary
        TVector3 energyCentroid = mc->GetMCSummary()->GetEnergyCentroid(); 

        TVector3 energyRMS = mc->GetMCSummary()->GetEnergyRMS();
        float totalScintEdep = mc->GetMCSummary()->GetTotalScintEdep(); // in MeV
        //MCTrack
        int mctrackcnt = mc->GetMCTrackCount();
        if(mctrackcnt!=0) cout<<"--->mctrackcnt "<<mctrackcnt<<endl;
        //TCanvas* cTest1 = new TCanvas(); int thiscnt1 = 0;
        //TGraph* gTest1 = new TGraph();
        for(int imctrackcnt=0;imctrackcnt<mctrackcnt;imctrackcnt++){
            int mctrackstepcnt = mc->GetMCTrack(imctrackcnt)->GetMCTrackStepCount();
              fout<<imctrackcnt<<"\t"<<mc->GetMCTrack(imctrackcnt)->GetID()<<"\t"<<mc->GetMCTrack(imctrackcnt)->GetParentID()<<"\t"<<mctrackstepcnt<<endl;
            fout<< "---->Track " << imctrackcnt << " id " << mc->GetMCTrack(imctrackcnt)->GetID() 
                << " pName " << mc->GetMCTrack(imctrackcnt)->GetParticleName() << " parent " << mc->GetMCTrack(imctrackcnt)->GetParentID()<< " stepcnt "<< mctrackstepcnt <<endl;
            //gTest1->SetPoint(thiscnt1,mc->GetMCTrack(imctrackcnt)->GetID(),imctrackcnt); thiscnt1++;

            for(int jmcstepcnt=0;jmcstepcnt<mctrackstepcnt;jmcstepcnt++){
                TVector3 stepEndPoint = mc->GetMCTrack(imctrackcnt)->GetMCTrackStep(jmcstepcnt)->GetEndpoint();
                fout<< "----------> steps " << jmcstepcnt << " ke "<< mc->GetMCTrack(imctrackcnt)->GetMCTrackStep(jmcstepcnt)->GetKE()
                << " end_points (" <<stepEndPoint[0]<<", "<<stepEndPoint[1]<<", "<<stepEndPoint[2]<<")" << " time " << mc->GetMCTrack(imctrackcnt)->GetMCTrackStep(jmcstepcnt)->GetGlobalTime()<<" process "<< mc->GetMCTrack(imctrackcnt)->GetMCTrackStep(jmcstepcnt)->GetProcess() << " volume " << mc->GetMCTrack(imctrackcnt)->GetMCTrackStep(jmcstepcnt)->GetVolume() <<endl;
                //if(i>=0 && i<=15){gTest->SetPoint(graphcnt,stepEndPoint[0],stepEndPoint[1],stepEndPoint[2]); graphcnt++;}
            }

        }

        int nHits = ev->GetPMTCount();
        float totalq = ev->GetTotalCharge();

        float tempq = 0;
        float maxq = 0;
        float tttt, energy; //fin_energy>>tttt>>energy;

        hNumberOfHittingPMTs->Fill(nHits);
        //float totalcharge = 0;
        for(int j=0; j<nHits; j++){
            RAT::DS::PMT *pmt = ev->GetPMT(j);
            int id = pmt->GetID(); cout<<"id "<<id<<endl;
            TVector3 hitpos = pmtinfo->GetPosition(id);
            double charge = pmt->GetCharge();
            //int mcphotoncnt = pmt->GetMCPhotonCount();
            double hittime = pmt->GetTime() - evtime;
            //double flighttime = (hitpos - evpos).Mag() / 224.9;
            //const double residtime = (hittime-flighttime);
            
            //hitresid->Fill(residtime);
            //1.589 is the old number from input spe spectrum
            //0.1817 is the one from the detector 130.406
            pmtchargeholder[id]=charge/130.406; // convert to npe
            pmttimeholder[id]=hittime;
            pmtidholder[j]=id;
            tempq += charge/130.406;
            if(charge>maxq) maxq=charge;
           // fout << "\t\t Hit " << j << " on PMT " << id << " at (" << hitpos[0] << ", "<< hitpos[1] << ", " << hitpos[2] << ')' << ", npe "<< pmtchargeholder[id] << endl;
            hPMTChargeMap->Fill(hitpos[0],hitpos[1],pmtchargeholder[id]);
            //pmt_x[id]=hitpos[0]; pmt_y[id]=hitpos[1];

            hTime[pmtidholder[j]][2]->Fill(pmttimeholder[pmtidholder[j]]);
            hCharge_vs_Time[pmtidholder[j]][2]->Fill(pmttimeholder[pmtidholder[j]],pmtchargeholder[pmtidholder[j]]);
            hCharge[pmtidholder[j]][2]->Fill(pmtchargeholder[pmtidholder[j]]);

        }//end nHit loop
        hTotalChargeVsNHit->Fill(tempq,nHits);
        
        
        //if(maxq>0){
            gMaxQvsEnergy->SetPoint(i,energy,maxq/130.406);
            gTotQvsEnergy->SetPoint(i,energy,tempq);
            hMaxQ->Fill(maxq/130.406);
            hTotQ->Fill(tempq);
        //}
        
    }  // end of for loop reading ONE root file
   }// end of loop for reading ALL root files
    
   foutroot->cd();
    
    for(int i=0; i<6; i++){
      for(int j=0; j<3; j++){
        hEdepInPS[i][j]->Write();
        hHitTimeInPS[i][j]->Write();
      }
    }
    for(int i=0; i<pmtnb; i++){
      for(int j=0; j<3; j++){
        hCharge[i][j]->Write();
        hTime[i][j]->Write();
        hCharge_vs_Time[i][j]->Write();
      }
    }
    hPMTChargeMap->Write();
    hPMTChargeMapAverage->Write();
    hPMTChargeMap_Hodo->Write();
    hPMTChargeMap_HodoAverage->Write();
    hPMTChargeMap_MultiAverage->Write();
    hNumberOfHittingPMTs->Write();
    hTotalChargeVsNHit->Write();
    hTotalChargeVsNHit_Hodo->Write();
    hPMTTimeMapAverage->Write();
    hPMTTimeMapAverage_hodo->Write();
    TCanvas* cMaxQvsEnergy=new TCanvas();
    cMaxQvsEnergy->SetName("cMaxQvsEnergy");
    gMaxQvsEnergy->GetXaxis()->SetTitle("Mu energy (GeV)");
    gMaxQvsEnergy->GetYaxis()->SetTitle("Maximum npe");
    gMaxQvsEnergy->SetMarkerStyle(7); gMaxQvsEnergy->SetMarkerColor(kRed); gMaxQvsEnergy->Draw("AP");
    cMaxQvsEnergy->Write();
    TCanvas* cTotQvsEnergy=new TCanvas(); cTotQvsEnergy->SetName("cTotQvsEnergy");
    gTotQvsEnergy->GetXaxis()->SetTitle("Mu energy (GeV)");
    gTotQvsEnergy->GetYaxis()->SetTitle("Total npe");
    gTotQvsEnergy->SetMarkerStyle(7);gTotQvsEnergy->SetMarkerColor(kRed); gTotQvsEnergy->Draw("AP");
    cTotQvsEnergy->Write();
    hMaxQ->Write(); hTotQ->Write();
    foutroot->Close();
    cout<<"Number of hodo tirggers: "<<hodotrigcnts<<endl;
    
    return 0; 

}
