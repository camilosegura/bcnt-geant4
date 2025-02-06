#ifndef RunDetector__hh
#define RunDetector__hh

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"

class RunDetector : public G4UserRunAction
{
private:
    /* data */
public:
    RunDetector(/* args */);
    ~RunDetector();

    virtual void BeginOfRunAction(const G4Run *);
    virtual void EndOfRunAction(const G4Run *);
};


#endif