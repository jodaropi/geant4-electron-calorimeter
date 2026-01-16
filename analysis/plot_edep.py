import numpy as np
import matplotlib.pyplot as plt


data = np.loadtxt("edep_h1_Edep.csv", delimiter=",", skiprows=7)

entries = data[:, 0]
Sw = data[:, 1]
Sxw0 = data[:, 3]


mask = Sw > 0

Ebin = Sxw0[mask] / Sw[mask]
counts = entries[mask]


plt.figure(figsize=(8, 5))
plt.step(Ebin, counts, where="mid", label="Geant4 Simulation")
plt.xlabel("Energy deposition per event [MeV]")
plt.ylabel("Events")
plt.title("Energy deposition distribution in the calorimeter")
plt.grid(True, alpha=0.3)
plt.legend()

plt.savefig("edep_histogram.png", dpi=300)
plt.show()