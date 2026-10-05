#include <stdio.h>
#include <time.h>

/* Funcion original del Problema 2, ahora retorna cuantas veces se imprimio */
long long function(int n) {
    long long counter = 0;
    if (n <= 1) return 0;
    int i, j;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("Sequence\n");
            counter++;
            break;
        }
    }
    return counter;
}

int main(void) {
    int valores[] = {1, 10, 100, 1000, 10000};
    int total = sizeof(valores) / sizeof(valores[0]);

    FILE *csv = fopen("resultados_p2.csv", "w");
    if (csv == NULL) {
        perror("No se pudo crear resultados_p2.csv");
        return 1;
    }
    fprintf(csv, "n,tiempo_s,counter\n");

    /* La tabla va a stderr para que no se mezcle con los printf("Sequence")
       de la funcion (que se redirigen a /dev/null al ejecutar). */
    fprintf(stderr, "%-10s %-18s %-20s\n", "n", "tiempo (s)", "counter");
    fprintf(stderr, "------------------------------------------------\n");

    for (int idx = 0; idx < total; idx++) {
        int n = valores[idx];
        struct timespec inicio, fin;

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        long long resultado = function(n);
        clock_gettime(CLOCK_MONOTONIC, &fin);

        double tiempo = (fin.tv_sec - inicio.tv_sec)
                      + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

        fprintf(stderr, "%-10d %-18.9f %-20lld\n", n, tiempo, resultado);
        fprintf(csv, "%d,%.9f,%lld\n", n, tiempo, resultado);
    }

    fclose(csv);
    fprintf(stderr, "\nResultados guardados en resultados_p2.csv\n");
    return 0;
}
