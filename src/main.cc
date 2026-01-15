#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "FTFP_BERT.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

int main(int argc, char** argv)
{
    auto runManager = new G4RunManager;

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new FTFP_BERT);

    runManager->SetUserAction(new PrimaryGeneratorAction());
    runManager->SetUserAction(new RunAction());
    runManager->SetUserAction(new EventAction());

    runManager->Initialize();

      
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    auto uiManager = G4UImanager::GetUIpointer();

    if (argc == 1)
    {
        
        auto ui = new G4UIExecutive(argc, argv);
        uiManager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }
    else
    {
        
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        uiManager->ApplyCommand(command + fileName);
    }

    delete visManager;
    delete runManager;

    return 0;
}

