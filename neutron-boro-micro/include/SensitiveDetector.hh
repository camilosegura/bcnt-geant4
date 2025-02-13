#ifndef SensitiveDetector__hh
#define SensitiveDetector__hh

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(G4String name);
    ~SensitiveDetector();
private:
    G4double totalEnergyDeposited;
    G4double mass;

    virtual void Initialize(G4HCofThisEvent *);
    virtual void EndOfEvent(G4HCofThisEvent *);
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);

    G4int fHistogramID;
};
#endif