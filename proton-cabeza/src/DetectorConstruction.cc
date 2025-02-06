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

    // Define elements
    G4Element* elH = nist->FindOrBuildElement("H");
    G4Element* elC = nist->FindOrBuildElement("C");
    G4Element* elN = nist->FindOrBuildElement("N");
    G4Element* elO = nist->FindOrBuildElement("O");
    G4Element* elP = nist->FindOrBuildElement("P");
    G4Element* elCa = nist->FindOrBuildElement("Ca");
    G4Element* elB = nist->FindOrBuildElement("B");

    G4Element* elBoron10 = new G4Element("Boron10", "B10", nIsotopes = 1);
    elBoron10->AddIsotope(isoB10, 100.*perCent); // 100% abundance of B-10

    // Define skin tissue
    // https://physics.nist.gov/cgi-bin/Star/compos.pl?matno=250
    skin = new G4Material("Skin", 1.10*g/cm3, 4);
    skin->AddElement(elH, 10.0*perCent);
    skin->AddElement(elC, 23.0*perCent);
    skin->AddElement(elN, 4.6*perCent);
    skin->AddElement(elO, 62.4*perCent);

    // Define skull tissue
    // https://physics.nist.gov/cgi-bin/Star/compos.pl?refer=ap&matno=120
    skull = new G4Material("Skull", 1.85*g/cm3, 6);
    skull->AddElement(elH, 4.7*perCent);
    skull->AddElement(elC, 14.4*perCent);
    skull->AddElement(elN, 4.2*perCent);
    skull->AddElement(elO, 44.6*perCent);
    skull->AddElement(elP, 10.5*perCent);
    skull->AddElement(elCa, 21.6*perCent);

    // Define brain tissue
    // https://physics.nist.gov/cgi-bin/Star/compos.pl?matno=123
    brain = new G4Material("Brain", 1.03*g/cm3, 4);
    brain->AddElement(elH, 11.0*perCent);
    brain->AddElement(elC, 12.5*perCent);
    brain->AddElement(elN, 1.3*perCent);
    brain->AddElement(elO, 75.2*perCent);

    tumor = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Define materials
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    G4Element *C = nist->FindOrBuildElement("C");

    G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    Aerogel->AddElement(C, 0.1*perCent);
    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H2O, 37.4*perCent);

    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    G4Material *wordMat = nist->FindOrBuildMaterial("G4_AIR");

    G4MaterialPropertiesTable *mptWord = new G4MaterialPropertiesTable();
    mptWord->AddProperty("RINDEX", energy, rindexWorld, 2);

    wordMat->SetMaterialPropertiesTable(mptWord);

    G4Box *solidWord = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWord, wordMat, "logicWorld");

    G4VPhysicalVolume *physWord = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);


    G4double startPhi = 0.0 * deg;
    G4double deltaPhi = 360.0 * deg;
    G4double startTheta = 0.0 * deg;
    G4double deltaTheta = 180.0 * deg;  // Full sphere (180 degrees for theta)

    G4double innerRadiusTumor = 0.0*mm;
    G4double outerRadiusTumor = 10.0*mm;

    G4Sphere *solidTumor = new G4Sphere("solidTumor", innerRadiusTumor, outerRadiusTumor, startPhi, deltaPhi, startTheta, deltaTheta);
    logicTumor = new G4LogicalVolume(solidTumor, tumor, "logicTumor");
    
    G4VisAttributes *tumorVisAtt = new G4VisAttributes(G4Colour(8.0, 8.0, 8.0, 1.0));
    tumorVisAtt->SetForceSolid(true);

    logicTumor->SetVisAttributes(tumorVisAtt);
    // G4VPhysicalVolume *physTumor = new G4PVPlacement(0, G4ThreeVector(0., 0., -300.), logicTumor, "physTumor", logicWorld, false, 0, true);
    // G4VPhysicalVolume *physTumor = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTumor, "physTumor", logicWorld, false, 0, true);
    //

    G4double innerRadiusBrain = 10.0*mm;
    G4double outerRadiusBrain = 100.0*mm;

    G4Sphere *solidBrain = new G4Sphere("solidBrain", innerRadiusBrain, outerRadiusBrain, startPhi, deltaPhi, startTheta, deltaTheta);
    logicBrain = new G4LogicalVolume(solidBrain, brain, "logicBrain");
    
    G4VisAttributes *brainVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.8));
    brainVisAtt->SetForceSolid(true);

    logicBrain->SetVisAttributes(brainVisAtt);
    G4VPhysicalVolume *physBrain = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicBrain, "physBrain", logicWorld, false, 0, true);

    G4double innerRadiusSkull = 100.0*mm;
    G4double outerRadiusSkull = 108.0*mm;

    G4Sphere *solidSkull = new G4Sphere("solidSkull", innerRadiusSkull, outerRadiusSkull, startPhi, deltaPhi, startTheta, deltaTheta);
    logicSkull = new G4LogicalVolume(solidSkull, skull, "logicSkull");

    G4VisAttributes *skullVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.5));
    skullVisAtt->SetForceSolid(true);

    logicSkull->SetVisAttributes(skullVisAtt);
    G4VPhysicalVolume *physSkull = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicSkull, "physSkull", logicWorld, false, 0, true);

    G4double innerRadiusSkin = 108.0*mm;
    G4double outerRadiusSkin = 113.0*mm;

    G4Sphere *solidSkin = new G4Sphere("solidSkin", innerRadiusSkin, outerRadiusSkin, startPhi, deltaPhi, startTheta, deltaTheta);
    logicSkin = new G4LogicalVolume(solidSkin, skin, "logicSkin");

    G4VisAttributes *skinVisAtt = new G4VisAttributes(G4Colour(0.8, 0.6, 0.4, 0.3));
    skinVisAtt->SetForceSolid(true);

    logicSkin->SetVisAttributes(skinVisAtt);
    G4VPhysicalVolume *physSkin = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicSkin, "physSkin", logicWorld, false, 0, true);


    return physWord;
}

void DetectorConstruction::ConstructSDandField(){
    // SensitiveDetector *sensitiveDetector = new SensitiveDetector("SensitiveDetector");
    
    // logicBrain->SetSensitiveDetector(sensitiveDetector);
    SensitiveDetector *sensitiveDetector = new SensitiveDetector("SensitiveDetector");
    
    // Asociar el detector sensible a los tres tejidos
    logicTumor->SetSensitiveDetector(sensitiveDetector);
    logicBrain->SetSensitiveDetector(sensitiveDetector);
    logicSkull->SetSensitiveDetector(sensitiveDetector);
    logicSkin->SetSensitiveDetector(sensitiveDetector);
}