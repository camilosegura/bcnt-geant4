#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
    DefineMaterials();
}

DetectorConstruction::~DetectorConstruction()
{}

void DetectorConstruction::DefineMaterials()
{
    // Define materials
    G4NistManager *nist = G4NistManager::Instance();

    // Define Boron 10
    G4int nComponents, nIsotopes;
    G4String name = "B10";
    G4double z = 5; // Atomic number for Boron
    G4double a = 10.012937 * g/mole; // Atomic mass of B-10
    G4Isotope* isoB10 = new G4Isotope(name, z, 10, a);

    G4Element* elBoron10 = new G4Element("Boron10", "B10", nIsotopes = 1);
    elBoron10->AddIsotope(isoB10, 100.*perCent); // 100% abundance of B-10

    
    tumor = new G4Material("Tumor", 2.34*g/cm3, 1);
    tumor->AddElement(elBoron10, 100.0*perCent);

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Define materials
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *wordMat = nist->FindOrBuildMaterial("G4_AIR");

    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexWorld[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptWord = new G4MaterialPropertiesTable();
    mptWord->AddProperty("RINDEX", energy, rindexWorld, 2);

    wordMat->SetMaterialPropertiesTable(mptWord);

    G4Box *solidWord = new G4Box("solidWorld", 30.0*um, 30.0*um, 30.0*um);

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWord, wordMat, "logicWorld");

    G4VPhysicalVolume *physWord = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);


    G4double startPhi = 0.0 * deg;
    G4double deltaPhi = 360.0 * deg;
    G4double startTheta = 0.0 * deg;
    G4double deltaTheta = 180.0 * deg;  // Full sphere (180 degrees for theta)

    G4double innerRadiusTumor = 0.0*mm;
    G4double outerRadiusTumor = 10*um;

    G4Sphere *solidTumor = new G4Sphere("solidTumor", innerRadiusTumor, outerRadiusTumor, startPhi, deltaPhi, startTheta, deltaTheta);
    logicTumor = new G4LogicalVolume(solidTumor, tumor, "logicTumor");
    
    G4VisAttributes *tumorVisAtt = new G4VisAttributes(G4Colour(8.0, 8.0, 8.0, 1.0));
    tumorVisAtt->SetForceSolid(true);

    logicTumor->SetVisAttributes(tumorVisAtt);
    G4VPhysicalVolume *physTumor = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTumor, "physTumor", logicWorld, false, 0, true);


    return physWord;
}

void DetectorConstruction::ConstructSDandField(){
    SensitiveDetector *sensitiveDetector = new SensitiveDetector("SensitiveDetector");
    
    // Asociar el detector sensible al tunor
    logicTumor->SetSensitiveDetector(sensitiveDetector);
}