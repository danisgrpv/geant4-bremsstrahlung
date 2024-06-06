#include "StepAct.hh"
#include "DetGeometry.hh"


StepAct::StepAct(DetGeometry*det, EventAct *eventAct):event(eventAct), fDetector(det)
{

}

void StepAct::UserSteppingAction(const G4Step *aStep)

{

    if (aStep->GetTrack()->GetVolume()->GetName()=="Body_No_2"
    &&aStep->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()=="gamma"
    &&aStep->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)

    {
        event->AddEnDep(aStep->GetTrack()->GetKineticEnergy());
    };


}

