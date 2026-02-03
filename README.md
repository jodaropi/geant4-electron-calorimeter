# Geant4 Sampling Calorimeter Simulation

This project implements a simple electromagnetic sampling calorimeter simulation using **Geant4**.  
A primary electron beam is injected into a multilayer Pb–Si detector, and the energy deposited in the active layers is recorded on an event-by-event basis.

The goal of this project is to demonstrate the full workflow of a Geant4 application: detector construction, physics list configuration, primary particle generation, sensitive detectors, and basic data analysis.

---

## Features

- Custom detector geometry with:
  - World volume
  - Sampling calorimeter composed of alternating absorber (Pb) and active (Si) layers
- Primary particle generator for monoenergetic electrons
- Sensitive detector to measure energy deposition in active layers
- Event-level energy accumulation
- Histogram-based analysis using Geant4 AnalysisManager
- CSV output for external analysis and plotting

---

## Physics

- Physics list: **FTFP_BERT**
- Processes included:
  - Electromagnetic interactions
  - Hadronic interactions (via standard Geant4 models)

---

## Output and Analysis

The simulation produces a histogram of the total energy deposited per event in the calorimeter.  
The resulting spectrum shows a strong low-energy peak dominated by ionization losses, followed by a rapid fall-off and a low-statistics high-energy tail, consistent with partial electromagnetic shower development in a thin sampling calorimeter.

Example output:
- `edep_h1_Edep.csv`: energy deposition histogram data
- `edep_histogram.png`: visualization of the energy deposition spectrum



