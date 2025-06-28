#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monitoreo.h"

int main() {
    Zona zonas[MAX_ZONAS];
    cargarDatos(zonas);

    int opcion;
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                monitorearActual(zonas);
                break;
            case 2:
                predecirContaminacion(zonas);
                break;
            case 3:
                generarAlertas(zonas);
                break;
            case 4:
                calcularPromedios(zonas);
                break;
            case 5:
                generarRecomendaciones(zonas);
                break;
            case 6:
                exportarReporte(zonas);
                break;
            case 0:
                printf("\n\nGracias por utilizar el Sistema de Monitoreo de Contaminaci\xA2n del Aire.\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    return 0;
}