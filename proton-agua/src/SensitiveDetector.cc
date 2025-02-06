#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
}

SensitiveDetector::~SensitiveDetector()
{
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    // G4Track *track = aStep->GetTrack();
    // track->SetTrackStatus(fStopAndKill);

    // G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    // G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    // G4ThreeVector posPhoton = preStepPoint->GetPosition();

    // // G4cout << "Photon position: " << posPhoton << G4endl;

    // const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    // G4int copyNo = touchable->GetCopyNumber();

    // // G4cout << "Copy number: " << copyNo << G4endl;

    // G4VPhysicalVolume *physVol = touchable->GetVolume();
    // G4ThreeVector posDetector = physVol->GetObjectTranslation();

    // G4cout << "Detector position: " << posDetector << G4endl;

    // G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    // G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    // G4cout << "Energía depositada: " << energyDeposit / CLHEP::keV << " keV" << G4endl;

    // G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    // analysisManager->FillNtupleIColumn(0, evt);
    // analysisManager->FillNtupleDColumn(1, posDetector[0]);
    // analysisManager->FillNtupleDColumn(2, posDetector[1]);
    // analysisManager->FillNtupleDColumn(3, posDetector[2]);
    // // analysisManager->FillNtupleDColumn(4, energyDeposit);
    // analysisManager->AddNtupleRow(0);
    // analysisManager->FillH1(0, energyDeposit / CLHEP::keV);

    G4Track *track = aStep->GetTrack();

    // Get the particle definition from the track
    G4ParticleDefinition* particleDef = track->GetDefinition();
    
    // Get the particle's name
    G4String particleName = particleDef->GetParticleName();
    
    // Print the particle name
    G4cout << "Particle name: " << particleName << G4endl;
   // Obtener la energía depositada
    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    // Obtener información del volumen actual
    const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4String volumeName = touchable->GetVolume()->GetLogicalVolume()->GetName();
    
    // Obtener el análisis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Registrar la energía según el tejido
    // if (energyDeposit > 0) {
        if (volumeName == "logicBrain") {
            analysisManager->FillH1(0, energyDeposit / CLHEP::keV);
        }
        else if (volumeName == "logicSkull") {
            analysisManager->FillH1(1, energyDeposit / CLHEP::keV);
        }
        else if (volumeName == "logicSkin") {
            analysisManager->FillH1(2, energyDeposit / CLHEP::keV);
        }
        
        // Opcional: imprimir información para debug
        G4cout << "Energía depositada en " << volumeName << ": " 
            << energyDeposit / CLHEP::keV << " keV" << G4endl;
    // }

    return true;
}