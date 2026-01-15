#include "EventAction.hh"

#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include "CalorimeterSD.hh"
#include "RunAction.hh"

EventAction::EventAction()
 : G4UserEventAction()
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
    
}

void EventAction::EndOfEventAction(const G4Event*)
{
    
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();

   
    CalorimeterSD* caloSD = static_cast<CalorimeterSD*>(
        sdManager->FindSensitiveDetector("CalorimeterSD")
    );

    if (!caloSD) {
        G4cerr << "ERROR: CalorimeterSD no encontrado" << G4endl;
        return;
    }

    
    G4double edep = caloSD->GetTotalEnergy();

    
    const RunAction* runActionConst =
      static_cast<const RunAction*>(
        G4RunManager::GetRunManager()->GetUserRunAction()
      );

    RunAction* runAction =
      const_cast<RunAction*>(runActionConst);



    if (!runAction) {
        G4cerr << "ERROR: RunAction no encontrado" << G4endl;
        return;
    }

    
    runAction->AddEnergy(edep);
}

