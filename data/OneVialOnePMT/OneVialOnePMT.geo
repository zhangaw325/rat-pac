{
    "index": "world", 
    "drawstyle": "wireframe", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        0.5
    ], 
    "material": "air", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "", 
    "invisible": 1, 
    "size": [
        120.0, 
        120.0, 
        600.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "dark_box", 
    "drawstyle": "wireframe", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        0.5
    ], 
    "material": "cardboard", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "world", 
    "size": [
        110.0, 
        110.0, 
        550.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "air_box", 
    "drawstyle": "wireframe", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        0.5
    ], 
    "material": "air", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "dark_box", 
    "size": [
        100.0, 
        100.0, 
        500.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "vial_wall", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        0.0, 
        0.5
    ], 
    "r_min": 12.4, 
    "material": "glass", 
    "valid_begin": [
        0, 
        0
    ], 
    "r_max": 12.7, 
    "size_z": 19.05, 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        19.05
    ], 
    "type": "tube", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "cd", 
    "name": "GEO", 
    "color": [
        0.0, 
        1.0, 
        0.0, 
        0.5
    ], 
    "material": "scintillator", 
    "valid_begin": [
        0, 
        0
    ], 
    "r_max": 12.4, 
    "size_z": 7.5, 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        7.5
    ], 
    "type": "tube", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "vial_bottom", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        0.0, 
        0.5
    ], 
    "material": "glass", 
    "valid_begin": [
        0, 
        0
    ], 
    "r_max": 12.7, 
    "size_z": 0.15, 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        -0.075
    ], 
    "type": "tube", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "vial_lid", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        0.0, 
        0.5
    ], 
    "material": "glass", 
    "valid_begin": [
        0, 
        0
    ], 
    "r_max": 12.7, 
    "size_z": 0.15, 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        38.175
    ], 
    "type": "tube", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "pmts", 
    "pmt_detector_type": "idpmt", 
    "enable": 1, 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        0.5
    ], 
    "sensitive_detector": "/mydet/pmt/inner", 
    "material": null, 
    "pmt_model": "r7723", 
    "pos_table": "PMTINFO", 
    "valid_begin": [
        0, 
        0
    ], 
    "orientation": "manual", // "point" means all PMTs at a point
	     	             // "manual" means there is a dir_x, dir_y, dir_z
	                     // in pos_table for manual orientation of PMTs
    "mother": "air_box", 
    "efficiency_correction": 1.0, 
    "type": "pmtarray", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "scintillation_strip_0", 
    "sensitive_detector": "/mydet/veto/genericchamber", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        1.0
    ], 
    "material": "pvc", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        80.0
    ], 
    "size": [
        10.0, 
        10.0, 
        2.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "scintillation_strip_1", 
    "sensitive_detector": "/mydet/veto/genericchamber", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        1.0
    ], 
    "material": "pvc", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        82.0
    ], 
    "size": [
        10.0, 
        10.0, 
        2.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "scintillation_strip_2", 
    "sensitive_detector": "/mydet/veto/genericchamber", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        1.0
    ], 
    "material": "pvc", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        84.0
    ], 
    "size": [
        10.0, 
        10.0, 
        2.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "scintillation_strip_3", 
    "sensitive_detector": "/mydet/veto/genericchamber", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        1.0
    ], 
    "material": "pvc", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        86.0
    ], 
    "size": [
        10.0, 
        10.0, 
        2.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "scintillation_strip_4", 
    "sensitive_detector": "/mydet/veto/genericchamber", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        1.0
    ], 
    "material": "pvc", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        88.0
    ], 
    "size": [
        10.0, 
        10.0, 
        2.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
{
    "index": "scintillation_strip_5", 
    "sensitive_detector": "/mydet/veto/genericchamber", 
    "name": "GEO", 
    "color": [
        1.0, 
        1.0, 
        1.0, 
        1.0
    ], 
    "material": "pvc", 
    "valid_begin": [
        0, 
        0
    ], 
    "mother": "air_box", 
    "position": [
        0.0, 
        0.0, 
        90.0
    ], 
    "size": [
        10.0, 
        10.0, 
        2.0
    ], 
    "type": "box", 
    "valid_end": [
        0, 
        0
    ]
}
