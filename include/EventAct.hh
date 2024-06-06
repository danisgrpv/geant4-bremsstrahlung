#ifndef TEMPLATE_EVENTACT_HH
#define TEMPLATE_EVENTACT_HH

#include "G4UserEventAction.hh"
#include "G4RunManager.hh"
#include "RunAct.hh"

class RunAct;

class EventAct : public G4UserEventAction
{
public:
    EventAct(RunAct* runAct);
    ~EventAct();
      void BeginOfEventAction(const G4Event* anEvent);
      void EndOfEventAction(const G4Event* anEvent);
      void AddEnDep (G4double en);


private:
      RunAct *run;
      G4double EnergyDep;
};

#endif //TEMPLATE_EVENTACT_HH
