import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 1. Leer datos
df = pd.read_csv("resultados_p2.csv")

# 2. Tabla: tamano de input vs. tiempo
print("\nTabla: tamano de input vs. tiempo\n")
print(df.to_string(index=False))
df.to_csv("tabla_final.csv", index=False)

# 3. Curva teorica n^2 * (log2(n) + 1), escalada para coincidir con el ultimo punto
n = df["n"].to_numpy(dtype=float)
t = df["tiempo_s"].to_numpy()

def teorica(x):
    return x ** 2 * (np.log2(x) + 1)

c = t[-1] / teorica(n[-1])  # constante de escala

# 4. Grafica log-log
plt.figure(figsize=(8, 5))
plt.loglog(n, t, "o-", label="Tiempo medido", linewidth=2)
plt.loglog(n, c * teorica(n), "--", label=r"Teorica $O(n^2 \log n)$ (escalada)")
plt.xlabel("Tamano de input (n)")
plt.ylabel("Tiempo de ejecucion (s)")
plt.title("Tamano de input vs. tiempo de ejecucion")
plt.grid(True, which="both", alpha=0.3)
plt.legend()
plt.tight_layout()
plt.savefig("grafica.png", dpi=200)
plt.show()
