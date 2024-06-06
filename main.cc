#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "DetGeometry.hh"
#include "ActionInit.hh"
#include "PrimaryGen.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "iostream"
#include "QGSP_BERT_HP.hh"
#include "QBBC.hh"

using namespace std;

int main(int argc, char** argv) {

    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(time(NULL));

    G4MTRunManager* runManager;
//    G4RunManager* runManager;
    DetGeometry *detGeom;

//    runManager = new G4RunManager;
    runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(4);

//Set mandatory initialization classes
    detGeom = new DetGeometry();
    runManager->SetUserInitialization(detGeom);
    auto Phys = new QBBC;
    runManager->SetUserInitialization(Phys);
    runManager->SetUserInitialization(new ActionInit(detGeom));
    runManager->Initialize();

    // Initialize visualization
    G4VisManager*visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = 0;
    if ( argc == 1 ) {
        ui = new G4UIExecutive(argc, argv);
    }

    if (! ui) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else {
        // interactive mode : define UI session
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
    }

    delete ui;
    delete visManager;
    delete runManager;

    return 0;
}