#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"

#include "CalorimeterSD.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // =========================
    // Materials
    // =========================
    G4NistManager* nist = G4NistManager::Instance();

    G4Material* worldMat     = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* absorberMat  = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* activeMat    = nist->FindOrBuildMaterial("G4_Si");

    // =========================
    // World
    // =========================
    G4double worldSize = 1.0*m;

    auto solidWorld = new G4Box(
        "World",
        worldSize/2,
        worldSize/2,
        worldSize/2
    );

    auto logicWorld = new G4LogicalVolume(
        solidWorld,
        worldMat,
        "World"
    );

    auto physWorld = new G4PVPlacement(
        nullptr,
        G4ThreeVector(),
        logicWorld,
        "World",
        nullptr,
        false,
        0,
        true
    );

    // =========================
    // Calorimeter parameters
    // =========================
    G4int    nLayers = 30;
    G4double absorberThickness = 5.0*mm;
    G4double activeThickness   = 3.0*mm;

    G4double layerThickness =
        absorberThickness + activeThickness;

    G4double caloSizeXY = 20.0*cm;
    G4double caloSizeZ  = nLayers * layerThickness;

    // =========================
    // Calorimeter container
    // =========================
    auto solidCalo = new G4Box(
        "Calorimeter",
        caloSizeXY/2,
        caloSizeXY/2,
        caloSizeZ/2
    );

    auto logicCalo = new G4LogicalVolume(
        solidCalo,
        worldMat,
        "Calorimeter"
    );

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 20*cm),
        logicCalo,
        "Calorimeter",
        logicWorld,
        false,
        0,
        true
    );

    // =========================
    // Layer
    // =========================
    auto solidLayer = new G4Box(
        "Layer",
        caloSizeXY/2,
        caloSizeXY/2,
        layerThickness/2
    );

    auto logicLayer = new G4LogicalVolume(
        solidLayer,
        worldMat,
        "Layer"
    );

    for (G4int i = 0; i < nLayers; i++) {
        G4double zpos =
            -caloSizeZ/2 + (i + 0.5)*layerThickness;

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(0, 0, zpos),
            logicLayer,
            "Layer",
            logicCalo,
            false,
            i,
            true
        );
    }

    // =========================
    // Absorber (Pb)
    // =========================
    auto solidAbsorber = new G4Box(
        "Absorber",
        caloSizeXY/2,
        caloSizeXY/2,
        absorberThickness/2
    );

    auto logicAbsorber = new G4LogicalVolume(
        solidAbsorber,
        absorberMat,
        "Absorber"
    );

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(
            0, 0,
            -layerThickness/2 + absorberThickness/2
        ),
        logicAbsorber,
        "Absorber",
        logicLayer,
        false,
        0,
        true
    );

    // =========================
    // Active layer (Si)
    // =========================
    auto solidActive = new G4Box(
        "Active",
        caloSizeXY/2,
        caloSizeXY/2,
        activeThickness/2
    );

    auto logicActive = new G4LogicalVolume(
        solidActive,
        activeMat,
        "Active"
    );

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(
            0, 0,
            +layerThickness/2 - activeThickness/2
        ),
        logicActive,
        "Active",
        logicLayer,
        false,
        0,
        true
    );

    // =========================
    // Sensitive Detector
    // =========================
    auto sdManager = G4SDManager::GetSDMpointer();

    auto caloSD = new CalorimeterSD("CalorimeterSD");

    sdManager->AddNewDetector(caloSD);
    logicActive->SetSensitiveDetector(caloSD);

    // =========================
    // Visualization
    // =========================
    logicWorld->SetVisAttributes(new G4VisAttributes(false));

    auto visCalo = new G4VisAttributes(G4Colour(0.8,0.8,0.8));
    visCalo->SetForceWireframe(true);
    logicCalo->SetVisAttributes(visCalo);

    auto visAbs = new G4VisAttributes(G4Colour(0.3,0.3,0.8));
    logicAbsorber->SetVisAttributes(visAbs);

    auto visAct = new G4VisAttributes(G4Colour(0.9,0.2,0.2));
    logicActive->SetVisAttributes(visAct);

    return physWorld;
}

