#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);

    auto particle =
        G4ParticleTable::GetParticleTable()->FindParticle("gamma");

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(6*MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    fParticleGun->SetParticlePosition(G4ThreeVector(0,0,-1.0*m));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fParticleGun->GeneratePrimaryVertex(event);
}
