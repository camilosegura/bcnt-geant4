#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    particleGun = new G4ParticleGun(1); // Número de partículas por evento

    // Configura la partícula como neutrón
    G4ParticleDefinition* particle = G4Neutron::NeutronDefinition();
    particleGun->SetParticleDefinition(particle);

    // Configura la energía en el rango epitérmico
    // particleGun->SetParticleEnergy(1.0*keV); 
    // Configura la energía en el rango rápidos
    // particleGun->SetParticleEnergy(0.025*eV);
    particleGun->SetParticleEnergy(500.0*eV); 
    // particleGun->SetParticleEnergy(0.1*eV);  
    // particleGun->SetParticleEnergy(0.5*eV); 
    // particleGun->SetParticleEnergy(1.0*eV); 

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