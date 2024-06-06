#ifndef TEMPLATE_RUNACT_HH
#define TEMPLATE_RUNACT_HH
#include "DetGeometry.hh"
#include <G4UserRunAction.hh>
#include <G4SystemOfUnits.hh>
#include "EventAct.hh"
#include <map>
#include "CommandMessenger.hh"
#include <vector>

using namespace std;
class DetGeometry;
class G4Run;
class PrimaryGen;
class RunActMessenger;

class RunAct : public G4UserRunAction {

public:
    RunAct(DetGeometry*det,PrimaryGen*gen);
    ~RunAct();

    void BeginOfRunAction(const G4Run *aRun);
    void EndOfRunAction(const G4Run *aRun);

    void AddEvent(G4double energy);

    int n_of_Bins = 5000;
    G4double Emax = 1.5*MeV;

    void SetNewResPath(G4String newPath);
    G4String foldername = "../res/New_Name Of_The_Output_File.txt";

private:
    std::map <G4double, G4int> *result;
    RunActMessenger*runactMessenger;
    PrimaryGen*fGen;
    DetGeometry*fDetector;
};

#endif //TEMPLATE_RUNACT_HH
