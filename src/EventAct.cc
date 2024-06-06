#include "EventAct.hh"

EventAct::EventAct(RunAct *runAct):run(runAct)
{

}

EventAct::~EventAct()
{

}

void EventAct::BeginOfEventAction(const G4Event *anEvent)
{
    EnergyDep = 0;
}

void EventAct::EndOfEventAction(const G4Event *anEvent)
{
//    run->AddEvent(EnergyDep);
}


void EventAct::AddEnDep(G4double en)
{
    EnergyDep = en;
    if (EnergyDep>0)
        run->AddEvent(EnergyDep);
}

