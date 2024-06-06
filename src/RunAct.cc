#include "RunAct.hh"
#include "iostream"
#include "map"
#include "CommandMessenger.hh"
#include "DetGeometry.hh"
#include <fstream>
#include <cstring>

using namespace std;


RunAct::RunAct(DetGeometry*det,PrimaryGen*gen):G4UserRunAction(),fGen(gen),fDetector(det)

{
    result = new std::map<G4double, G4int>;
    runactMessenger = new RunActMessenger(this);
}

RunAct::~RunAct()
{
    delete result;
    delete runactMessenger;
}

void RunAct::BeginOfRunAction(const G4Run *aRun)
{

/*сетка из файла mesh02*/
//    int i = 0;
//    double arr[2001];
//
//    ifstream file("../mesh/mesh02.txt");
//
//    result->clear();
//
//    for (int c = 0; c < 2001; ++c)
//    {
//        file >> arr[c];
//        result->insert(std::pair<G4double, G4int> (arr[c], 0));
//    }

/*прошлое рабочее на сетке Geant4*/
    result->clear();
    for (int i=0; i <n_of_Bins; i++)
    result->insert(std::pair<G4double, G4int> (i *Emax / n_of_Bins, 0));
}

// для однопоточного режима

//void RunAct::EndOfRunAction(const G4Run *aRun)
//{
//    fstream fout("../res/Deposited Energy.txt", ios::out);
//    for (auto it: *result)
//        fout << it.first << '\t' << it.second << '\n';
//    fout.close();
//}

// для многопоточного вывода
void RunAct::EndOfRunAction(const G4Run *aRun)
{
    if(!isMaster)
    {
        stringstream new_out;
        new_out<<"../res/Deposited Energy from Thread Number "<<G4Threading::G4GetThreadId()<<".txt";
        fstream fout(new_out.str(), ios::out);
        for (auto it: *result)
            fout << it.first << '\t' << it.second << '\n';
        fout.close();
    }
}


void RunAct::AddEvent(G4double energy)
{
    auto it = result->lower_bound(energy);
    it->second++;
}

void RunAct::SetNewResPath(G4String newPath) {

    foldername = newPath;

}

