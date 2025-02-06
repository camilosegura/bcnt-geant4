#include "Physics.hh"

Physics::Physics(/* args */)
{
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
    
    RegisterPhysics(new G4HadronElasticPhysics());    // Física elástica
    // RegisterPhysics(new G4NeutronHPPhysics());        // Procesos de neutrones de baja energía
    RegisterPhysics(new G4HadronPhysicsQGSP_BERT_HP()); // Física hadrónica general con soporte para alta precisión
}

Physics::~Physics()
{
}