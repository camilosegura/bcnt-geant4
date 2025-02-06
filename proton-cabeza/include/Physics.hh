#ifndef Physics_h
#define Physics_h

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4HadronElasticPhysics.hh"
// #include "G4NeutronHPPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"

class Physics : public G4VModularPhysicsList
{
public:
    Physics(/* args */);
    ~Physics();
};



#endif