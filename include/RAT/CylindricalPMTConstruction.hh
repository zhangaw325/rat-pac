#ifndef __RAT_CylindricalPMTConstruction__
#define __RAT_CylindricalPMTConstruction__

#include <string>
#include <vector>
#include <RAT/DB.hh>
#include <G4Material.hh>
#include <RAT/GLG4TorusStack.hh>
#include <G4OpticalSurface.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <RAT/WaveguideFactory.hh>
#include <RAT/Factory.hh>
#include <RAT/PMTConstruction.hh>

namespace RAT {
  

struct CylindricalPMTConstructionParams {
  CylindricalPMTConstructionParams () { 
    efficiencyCorrection = 1.0;
    invisible = false;
  };
  
  bool invisible;
  
  // Body
  double caseThickness; // mm
  double glassThickness; // mm
  double pmtRadius; // mm
  double pmtHeight; // mm
  double photocathodeRadius; // mm
  
  G4Material *outerCase;
  G4Material *glass;
  G4Material *vacuum;
  
  G4OpticalSurface *photocathode;

  G4VSensitiveDetector *detector;
  
  double efficiencyCorrection; // default to 1.0 for no correction

};

class CylindricalPMTConstruction : public PMTConstruction {
public:
  CylindricalPMTConstruction(DBLinkPtr params, G4LogicalVolume *mother);
  virtual ~CylindricalPMTConstruction() { }
  
  virtual G4LogicalVolume *BuildVolume(const std::string &prefix);
  virtual G4VSolid *BuildSolid(const std::string &prefix);
  virtual G4PVPlacement* PlacePMT(G4RotationMatrix *pmtrot, 
				  G4ThreeVector pmtpos, 
				  const std::string &name, 
				  G4LogicalVolume *logi_pmt, 
				  G4VPhysicalVolume *mother_phys, 
				  bool booleanSolid, int copyNo);
  
protected:
  
  // physical volumes
  G4PVPlacement* glass_phys;
  G4PVPlacement* vacuum_phys;
  //G4PVPlacement* stopper_phys;
  
  G4LogicalVolume *log_pmt;
  CylindricalPMTConstructionParams fParams;

};

} // namespace RAT

#endif
