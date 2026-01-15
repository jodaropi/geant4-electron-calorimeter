#include "CalorimeterSD.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"

CalorimeterSD::CalorimeterSD(const G4String& name)
    : G4VSensitiveDetector(name),
      fTotalEnergy(0.)
{}

CalorimeterSD::~CalorimeterSD() {}

void CalorimeterSD::Initialize(G4HCofThisEvent*)
{
    
    fTotalEnergy = 0.;
}

G4bool CalorimeterSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4double edep = step->GetTotalEnergyDeposit();

    if (edep <= 0.) return false;

    fTotalEnergy += edep;

    auto particle = step->GetTrack()->GetDefinition()->GetParticleName();

    G4cout << "Particle: " << particle
           << " | Edep: " << edep / MeV << " MeV"
           << G4endl;

    return true;
}

void CalorimeterSD::EndOfEvent(G4HCofThisEvent*)
{
    G4cout << ">>> Calorimeter total energy: "
           << fTotalEnergy / MeV << " MeV"
           << G4endl;
}

