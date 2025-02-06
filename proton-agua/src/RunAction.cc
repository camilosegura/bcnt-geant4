#include "RunAction.hh"

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction::Build() const
{
    PrimaryGeneratorAction *primaryGeneratorAction = new PrimaryGeneratorAction();
    SetUserAction(primaryGeneratorAction);

    RunDetector *runDetector = new RunDetector();
    SetUserAction(runDetector);
}
