import pandas as pd
import matplotlib.pyplot as plt

dane = pd.read_csv("./wyniki/przebieg.csv")

# Wykres wysokości
plt.figure(figsize=(10, 5))
plt.plot(dane["czas_s"], dane["wysokosc_m"])
plt.xlabel("Czas [s]")
plt.ylabel("Wysokość [m]")
plt.title("Wysokość lądownika w funkcji czasu")
plt.grid(True)
plt.tight_layout()
plt.savefig("./wyniki/wykres_wysokosci.png")
plt.show()

# Wykres prędkości
plt.figure(figsize=(10, 5))
plt.plot(dane["czas_s"], dane["predkosc_ms"])
plt.xlabel("Czas [s]")
plt.ylabel("Prędkość [m/s]")
plt.title("Prędkość lądownika w funkcji czasu")
plt.grid(True)
plt.tight_layout()
plt.savefig("./wyniki/wykres_predkosci.png")
plt.show()

# Wykres poziomu paliwa
plt.figure(figsize=(10, 5))
plt.plot(dane["czas_s"], dane["paliwo"])
plt.xlabel("Czas [s]")
plt.ylabel("Pozostałe paliwo")
plt.title("Zużycie paliwa lądownika w funkcji czasu")
plt.grid(True)
plt.tight_layout()
plt.savefig("./wyniki/wykres_paliwa.png")
plt.show()

