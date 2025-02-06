#ifndef DetectorConstruction_h
#define DetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserPhysicsList.hh"
#include "G4ThreeVector.hh"
#include "G4Isotope.hh"

#include "SensitiveDetector.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    
    virtual G4VPhysicalVolume* Construct();

private:
    G4LogicalVolume *logicDetector;
    G4LogicalVolume *logicBrain;
    G4LogicalVolume *logicSkull;
    G4LogicalVolume *logicSkin;
    G4LogicalVolume *logicTumor;
    virtual void ConstructSDandField();

    void DefineMaterials();
    G4Material* skin;
    G4Material* skull;
    G4Material* brain;
    G4Material* tumor;
};
#endif
