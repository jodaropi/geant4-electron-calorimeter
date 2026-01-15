cmake_minimum_required(VERSION 3.16)
project(MyFirstG4)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

include_directories(include)

add_executable(MyFirstG4
  src/main.cc
  src/DetectorConstruction.cc
  src/PrimaryGeneratorAction.cc
  src/EventAction.cc
  src/RunAction.cc
  src/CalorimeterSD.cc
)


target_link_libraries(MyFirstG4 ${Geant4_LIBRARIES})

