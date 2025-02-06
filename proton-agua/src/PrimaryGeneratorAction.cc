#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    particleGun = new G4ParticleGun(1); // Número de partículas por evento

    // Configura la partícula proton
    G4ParticleDefinition* particle = G4Proton::ProtonDefinition();
    particleGun->SetParticleDefinition(particle);

    // Configura la energía en el rango epitérmico
    particleGun->SetParticleEnergy(230.0*MeV); // Cambiar según la energía deseada

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
    particleGun->GeneratePrimaryVertex(anEvent);
}