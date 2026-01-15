#ifndef CalorimeterSD_h
#define CalorimeterSD_h

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class CalorimeterSD : public G4VSensitiveDetector
{
public:
    CalorimeterSD(const G4String& name);
    virtual ~CalorimeterSD();

    virtual void Initialize(G4HCofThisEvent*) override;
    virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
    virtual void EndOfEvent(G4HCofThisEvent*) override;

    G4double GetTotalEnergy() const { return fTotalEnergy; }

private:
    G4double fTotalEnergy;
};

#endif

