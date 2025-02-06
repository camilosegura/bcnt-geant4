#ifndef RunAction_h
#define RunAction_h

#include "G4VUserActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

#include "RunDetector.hh"
class G4Run;

class RunAction : public G4VUserActionInitialization
{
  public:
    RunAction();
    ~RunAction();

    virtual void Build() const;
};

#endif