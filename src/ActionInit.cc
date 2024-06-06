#include "ActionInit.hh"

ActionInit::ActionInit(DetGeometry*detector):G4VUserActionInitialization(), fDetector(detector)
{ }

ActionInit::~ActionInit()
{ }

void ActionInit::Build() const
{
    PrimaryGen*primary = new PrimaryGen(fDetector);
    SetUserAction(primary);
    RunAct* runAct = new RunAct(fDetector, primary);
    SetUserAction(runAct);
    EventAct* eventAct = new EventAct(runAct);
    SetUserAction(eventAct);

    SetUserAction(new StepAct (fDetector, eventAct));

}

void ActionInit::BuildForMaster() const
{
    PrimaryGen*primary = new PrimaryGen(fDetector);
    RunAct* runAct = new RunAct(fDetector, primary);
    SetUserAction(runAct);
}

