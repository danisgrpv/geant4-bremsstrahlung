#ifndef TEMPLATE_STEPACT_HH
#define TEMPLATE_STEPACT_HH

#include <G4UserRunAction.hh>
#include <G4UserSteppingAction.hh>
#include "EventAct.hh"

class DetGeometry;

class StepAct: public G4UserSteppingAction
{
public:
    StepAct (DetGeometry*det,EventAct* eventAct);

    void UserSteppingAction(const G4Step*);

private:

    EventAct* event;
    DetGeometry*fDetector;
};

#endif //TEMPLATE_STEPACT_HH
