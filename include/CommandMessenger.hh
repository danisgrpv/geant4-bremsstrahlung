#ifndef TEMPLATE_COMMANDMESSENGER_HH
#define TEMPLATE_COMMANDMESSENGER_HH

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UImessenger.hh"
#include "RunAct.hh"
#include "PrimaryGen.hh"
#include "DetGeometry.hh"

class RunAct;
class PrimaryGen;
class DetGeometry;

class RunActMessenger : public G4UImessenger
{

public:
    RunActMessenger(RunAct *run);
    ~RunActMessenger();
    void SetNewValue(G4UIcommand*command, G4String newValue);


private:

    RunAct *run;
    G4UIdirectory *my_command;
    G4UIcmdWithAString *newresPath;
};



class PrimaryGenMessenger : public G4UImessenger
{
public:
    PrimaryGenMessenger(PrimaryGen *primarygen);
    ~PrimaryGenMessenger();
    void SetNewValue(G4UIcommand*command, G4String newValue);

private:
    PrimaryGen *primarygen;
    G4UIdirectory *my_command;
    G4UIcmdWithADouble *newpatEn;
};



class GeometryMessenger : public G4UImessenger{

public:
    GeometryMessenger(DetGeometry *det);

    ~GeometryMessenger();

    void SetNewValue(G4UIcommand *command, G4String newValue);


private:

    DetGeometry *det;
    G4UIdirectory *my_command;
    G4UIcmdWithAString *newName;
    G4UIcmdWithADouble *newSize;

};

#endif //TEMPLATE_COMMANDMESSENGER_HH
