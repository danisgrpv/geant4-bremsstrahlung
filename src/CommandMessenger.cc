#include "CommandMessenger.hh"
#include "RunAct.hh"
#include "PrimaryGen.hh"
#include "DetGeometry.hh"

RunActMessenger::RunActMessenger(RunAct *run_1) {
    run = run_1;

    my_command = new G4UIdirectory("/my_command/");
    my_command ->SetGuidance("UI command for changing result file path");

    newresPath = new G4UIcmdWithAString("/my_command/SetNewResPath", this);
    newresPath->SetGuidance("Write new path");
    newresPath->SetParameterName("path", false);
}



PrimaryGenMessenger::PrimaryGenMessenger(PrimaryGen *primarygen_1) {

    primarygen = primarygen_1;

    my_command = new G4UIdirectory("/my_command/");
    my_command->SetGuidance("UI command for changing particle energy");

    newpatEn = new G4UIcmdWithADouble("/my_command/SetNewPatEn", this);
    newpatEn->SetGuidance("Write new pat energy");
    newpatEn->SetParameterName("energy", false);
}


GeometryMessenger::GeometryMessenger(DetGeometry *det_1) {

    det = det_1;
    my_command = new G4UIdirectory("/my_command/");
    my_command->SetGuidance("UI commands specific to this sample");

    newName = new G4UIcmdWithAString("/my_command/SetNewMat", this);
    newName->SetGuidance("change Material Type");
    newName->SetParameterName("material type", false);

    newSize = new G4UIcmdWithADouble("/my_command/SetNewSize", this);
    newSize->SetGuidance("change Tube Radius");
    newSize->SetParameterName("tube radius", false);
}

RunActMessenger::~RunActMessenger()
{

}

PrimaryGenMessenger::~PrimaryGenMessenger()
{

}

GeometryMessenger::~GeometryMessenger()
{

}

void RunActMessenger::SetNewValue(G4UIcommand *command, G4String newValue) {
    if(command == newresPath)
    {
        run ->SetNewResPath(newValue);
    }
}


void PrimaryGenMessenger::SetNewValue(G4UIcommand *command, G4String newValue) {
    if(command == newpatEn)
    {
        primarygen ->SetNewPatEn(newpatEn->GetNewDoubleValue(newValue));
    }
}

void GeometryMessenger::SetNewValue(G4UIcommand *command, G4String newValue) {

    if(command == newName)
    {
        det->SetNewMat(newValue);
    }

    if(command == newSize)
    {
        det->SetNewSize(newSize->GetNewDoubleValue(newValue));
    }

}

