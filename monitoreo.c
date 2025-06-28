#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monitoreo.h"

void mostrarMenu() {
    printf("\n--- Sistema de Monitoreo de Contaminación ---\n");
    printf("1. Monitorear niveles actuales\n");
    printf("2. Predecir niveles futuros\n");
    printf("3. Generar alertas preventivas\n");
    printf("4. Calcular promedios historicos\n");
    printf("5. Generar recomendaciones\n");
    printf("6. Exportar datos a archivo\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

void cargarDatos(Zona zonas[]) {
    for (int i = 0; i < MAX_ZONAS; i++) {
        sprintf(zonas[i].nombre, "Zona %d", i + 1);
        zonas[i].temperatura = 20.0 + rand() % 10;
        zonas[i].viento = 1.0 + (rand() % 5);
        zonas[i].humedad = 50 + rand() % 20;

        for (int j = 0; j < MAX_DIAS; j++) {
            zonas[i].historialPM25[j] = 10 + rand() % 50;
        }
        zonas[i].actualPM25 = zonas[i].historialPM25[MAX_DIAS - 1];
    }
}

void monitorearActual(Zona zonas[]) {
    printf("\n--- Monitoreo Actual ---\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        printf("%s: PM2.5 = %.2f μg/m³\n", zonas[i].nombre, zonas[i].actualPM25);
    }
}

void predecirContaminacion(Zona zonas[]) {
    printf("\n--- Prediccion para las proximas 24h ---\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        float suma = 0, peso = 0;
        for (int j = 0; j < 5; j++) {
            suma += zonas[i].historialPM25[MAX_DIAS - 1 - j] * (5 - j);
            peso += (5 - j);
        }
        zonas[i].prediccionPM25 = suma / peso;
        printf("%s: Prediccion PM2.5 = %.2f μg/m³\n", zonas[i].nombre, zonas[i].prediccionPM25);
    }
}

void generarAlertas(Zona zonas[]) {
    printf("\n--- Alertas Preventivas ---\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        if (zonas[i].prediccionPM25 > LIMITE_PM25) {
            printf("ALERTA: %s superara el límite permitido (%.2f μg/m³)\n",
                   zonas[i].nombre, zonas[i].prediccionPM25);
        }
    }
}

void calcularPromedios(Zona zonas[]) {
    printf("\n--- Promedios Historicos ---\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        float suma = 0;
        for (int j = 0; j < MAX_DIAS; j++) {
            suma += zonas[i].historialPM25[j];
        }
        float promedio = suma / MAX_DIAS;
        printf("%s: Promedio 30 dias = %.2f μg/m³ (%s)\n", zonas[i].nombre, promedio,
               promedio > LIMITE_PM25 ? "Supera limite OMS" : "Dentro de limite");
    }
}

void generarRecomendaciones(Zona zonas[]) {
    printf("\n--- Recomendaciones ---\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        if (zonas[i].actualPM25 > LIMITE_PM25 || zonas[i].prediccionPM25 > LIMITE_PM25) {
            printf("%s:\n", zonas[i].nombre);
            printf("- Reducir trafico vehicular\n");
            printf("- Restringir actividades al aire libre\n");
            printf("- Supervisar industrias locales\n");
        }
    }
}

void exportarReporte(Zona zonas[]) {
    FILE *f = fopen("reporte_contaminacion.txt", "w");
    if (!f) {
        printf("Error al abrir archivo de reporte.\n");
        return;
    }

    fprintf(f, "REPORTE DE CONTAMINACION\n\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        fprintf(f, "%s\n", zonas[i].nombre);
        fprintf(f, "Actual PM2.5: %.2f\n", zonas[i].actualPM25);
        fprintf(f, "Prediccion PM2.5: %.2f\n\n", zonas[i].prediccionPM25);
    }

    fclose(f);
    printf("Reporte exportado correctamente.\n");
}