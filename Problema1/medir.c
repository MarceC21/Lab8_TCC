#include <stdio.h>
#include <time.h>

/* Funcion original, ahora retorna counter (long long para evitar overflow) */
long long function(int n) {
    int i, j, k;
    long long counter = 0;
    for (i = n / 2; i <= n; i++) {
        for (j = 1; j + n / 2 <= n; j++) {
            for (k = 1; k <= n; k = k * 2) {
                counter++;
            }
        }
    }
    return counter;
}

int main(void) {
    int valores[] = {1, 10, 100, 1000, 10000, 100000};
    int total = sizeof(valores) / sizeof(valores[0]);

    FILE *csv = fopen("resultados.csv", "w");
    if (csv == NULL) {
        perror("No se pudo crear resultados.csv");
        return 1;
    }
    fprintf(csv, "n,tiempo_s,counter\n");

    printf("%-10s %-18s %-20s\n", "n", "tiempo (s)", "counter");
    printf("------------------------------------------------\n");

    for (int idx = 0; idx < total; idx++) {
        int n = valores[idx];
        struct timespec inicio, fin;

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        long long resultado = function(n);
        clock_gettime(CLOCK_MONOTONIC, &fin);

        double tiempo = (fin.tv_sec - inicio.tv_sec)
                      + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

        printf("%-10d %-18.9f %-20lld\n", n, tiempo, resultado);
        fprintf(csv, "%d,%.9f,%lld\n", n, tiempo, resultado);
        fflush(stdout);
    }

    fclose(csv);
    printf("\nResultados guardados en resultados.csv\n");
    return 0;
}
