#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    totalEnergyDeposited = 0.;
}

SensitiveDetector::~SensitiveDetector()
{
}

void SensitiveDetector::Initialize(G4HCofThisEvent *)
{
    totalEnergyDeposited = 0.;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    G4cout << "Energía Total depositada " << totalEnergyDeposited << " MeV" << G4endl;

    G4double totalEnergyDeposited_J = totalEnergyDeposited/CLHEP::joule;
    // G4double totalEnergyDeposited_J = totalEnergyDeposited * 1.602e-13;

    G4cout << "Energía Total depositada Juios " << totalEnergyDeposited_J << " J" << G4endl;

    G4double dose = totalEnergyDeposited_J/mass;

    G4cout << "Dosis " << dose << "Gy" << G4endl;
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

   // Obtener la energía depositada
    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    // Obtener información del volumen actual
    const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4String volumeName = touchable->GetVolume()->GetLogicalVolume()->GetName();
    
    G4LogicalVolume* volume = touchable->GetVolume()->GetLogicalVolume();
    
    G4Material* material = volume->GetMaterial();
    
    G4double density = material->GetDensity()/(CLHEP::kg/CLHEP::m3); // Densidad del material (kg/m³)
    
    G4double volumeTotal = volume->GetSolid()->GetCubicVolume()/CLHEP::m3;
    
    mass = (density * volumeTotal); // Masa del volumen en kg
    // Registrar la energía según el tejido
    if (energyDeposit > 0) {
        G4Track *track = aStep->GetTrack();

        // Get the particle definition from the track
        G4ParticleDefinition* particleDef = track->GetDefinition();
        
        // Get the particle's name
        G4String particleName = particleDef->GetParticleName();
        
        // Print the particle name
        G4cout << "Particle name: " << particleName << G4endl;
        
        // Opcional: imprimir información para debug
        G4cout << "Energía depositada en " << volumeName << ": " 
            << energyDeposit  << " MeV" << G4endl;

        totalEnergyDeposited += energyDeposit;
    }

    return true;
}