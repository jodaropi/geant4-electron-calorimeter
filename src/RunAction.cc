#include "RunAction.hh"

#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

RunAction::RunAction()
 : G4UserRunAction(),
   fEventEnergy(0.)
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFileName("edep.csv");

    
    analysisManager->CreateH1(
        "Edep",
        "Energy deposited per event;Edep (MeV);Events",
        100, 0., 10.*MeV
    );
}

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

    G4cout << ">>> Histogram saved to edep.root" << G4endl;
}

void RunAction::AddEnergy(G4double edep)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(0, edep);

    fEventEnergy = 0.;
}

