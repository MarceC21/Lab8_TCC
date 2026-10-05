# Laboratorio 8

Análisis de complejidad de tiempo en notación Big-O y medición experimental (profiling) de tres programas.
---

## Estructura del repositorio

```
.
├── README.md
├── Problema 1/
│   ├── medir.c
│   ├── graficar.py
│   ├── resultados.csv
│   ├── tabla_final.csv
│   └── grafica.png
├── Problema 2/
│   ├── medir.c
│   ├── graficar.py
│   ├── resultados.csv
│   ├── tabla_final.csv
│   └── grafica.png
├── Problema 3/
│   ├── medir.c
│   ├── graficar.py
│   ├── resultados.csv
│   ├── tabla_final.csv
│   └── grafica.png
└── Resolución/
    └── (problemas resueltos a mano, en PDF)
```

| Archivo | Descripción |
|---|---|
| `medir.c` | Programa en C que implementa la función del problema, mide el tiempo de ejecución con `clock_gettime(CLOCK_MONOTONIC)` y genera `resultados.csv`. |
| `graficar.py` | Script en Python que lee `resultados.csv`, imprime la tabla (`tabla_final.csv`) y genera la gráfica log-log (`grafica.png`) junto con la curva teórica. |
| `resultados.csv` | Salida cruda del programa en C: `n`, `tiempo_s`, `counter`. |
| `tabla_final.csv` | Tabla de tamaño de input vs. tiempo. |
| `grafica.png` | Gráfica de tamaño de input vs. tiempo (escala log-log). |

La carpeta **Resolución** contiene los procedimientos desarrollados a mano (análisis ciclo por ciclo y cálculo de la complejidad Big-O de cada problema, además de los ejercicios sin código).

---

## Requisitos

Todo se probó en **WSL (Ubuntu)** sobre Windows.

- `gcc`
- Python 3
- Librerías de Python:

```bash
pip install pandas matplotlib numpy
```

---

## Cómo ejecutar

Todos los problemas siguen los mismos pasos: **compilar**, **ejecutar** y **graficar**. Hay que entrar a la carpeta de cada problema (las carpetas tienen espacios, por eso van entre comillas).

> Se compila con `-O0` (sin optimizaciones) para que el compilador no altere los ciclos y se observe el comportamiento real del algoritmo.

### Problema 1

```bash
cd "Problema 1"
gcc -O0 medir.c -o medir
./medir
python3 graficar.py
```

### Problema 2

```bash
cd "Problema 2"
gcc -O0 medir.c -o medir
./medir > /dev/null
python3 graficar.py
```

### Problema 3

```bash
cd "Problema 3"
gcc -O0 medir.c -o medir
./medir > /dev/null
python3 graficar.py
```

**¿Por qué `> /dev/null` en los problemas 2 y 3?** Estas funciones usan `printf("Sequence\n")` dentro de los ciclos. Mostrar millones de líneas en la terminal mediría la velocidad de la consola y no la del algoritmo. Por eso la salida normal se descarta, mientras que la tabla de resultados se imprime por `stderr` y sigue viéndose en pantalla.

---

## Valores de n medidos

Se midió **una sola vez** cada valor de n:

```
n = 1, 10, 100, 1000, 10000, 100000
```

> **Nota:** el enunciado pide también n = 1,000,000, pero ese valor **se omitió en los tres problemas por cuestión de tiempo de ejecución**. Por ejemplo, en el Problema 1 serían ~5 × 10¹² iteraciones y en el Problema 3 ~8.3 × 10¹⁰ impresiones.

---

## Resumen del análisis teórico

| Problema | Programa | Complejidad |
|---|---|---|
| 1 | Tres ciclos anidados (`n/2 + 1` · `n/2` · `log₂n + 1` iteraciones) | **O(n² log n)** |
| 2 | Ciclo exterior de n iteraciones; el ciclo interior hace una sola iteración por el `break` | **O(n)** |
| 3 | Ciclo exterior de `n/3` iteraciones · ciclo interior de `(n+3)/4` iteraciones | **O(n²)** |

El procedimiento completo está en la carpeta **Resolución**.

---

## Resultados

Los resultados (tabla y gráfica) de cada problema están en su carpeta correspondiente:

- `Problema 1/tabla_final.csv` y `Problema 1/grafica.png`
- `Problema 2/tabla_final.csv` y `Problema 2/grafica.png`
- `Problema 3/tabla_final.csv` y `Problema 3/grafica.png`

La columna `counter` de cada tabla permite verificar que el número de iteraciones medido coincide con el análisis teórico.
