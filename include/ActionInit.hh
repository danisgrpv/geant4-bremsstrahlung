#ifndef TEMPLATE_ACTIONINIT_HH
#define TEMPLATE_ACTIONINIT_HH

#include "G4VUserActionInitialization.hh"
#include "PrimaryGen.hh"
#include "EventAct.hh"
#include "RunAct.hh"
#include "StepAct.hh"

class DetGeometry;

class ActionInit : public G4VUserActionInitialization{

public:
    ActionInit(DetGeometry*detector);
    virtual ~ActionInit();
    virtual void Build() const;
    virtual void BuildForMaster() const;

private:
    DetGeometry*fDetector;

};


#endif //TEMPLATE_ACTIONINIT_HH
