#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    // fParticleGun = new G4ParticleGun(1);

    // G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    // G4String particleName = "proton";
    // G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

    // G4ThreeVector pos(0., 0., -100.);
    // G4ThreeVector mom(0., 0., 1.);

    // fParticleGun->SetParticlePosition(pos);
    // fParticleGun->SetParticleMomentumDirection(mom);
    // fParticleGun->SetParticleMomentum(100.0*GeV);
    // fParticleGun->SetParticleDefinition(particle);

    particleGun = new G4ParticleGun(1); // Número de partículas por evento

    // Configura la partícula proton
    G4ParticleDefinition* particle = G4Proton::ProtonDefinition();
    particleGun->SetParticleDefinition(particle);

    // Configura la energía en el rango epitérmico
    // particleGun->SetParticleEnergy(1.0*keV); 
    // Configura la energía en el rango rápidos
    // particleGun->SetParticleEnergy(500.0*MeV); 
    particleGun->SetParticleEnergy(230.0*MeV); 

    // Configura la posición de emisión
    particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 500.0));

    // Configura la dirección inicial
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, -1.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
    delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    

    // fParticleGun->GeneratePrimaryVertex(anEvent);
    particleGun->GeneratePrimaryVertex(anEvent);
}