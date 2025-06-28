#ifndef MONITOREO_H
#define MONITOREO_H

#define MAX_ZONAS 5
#define MAX_DIAS 30
#define LIMITE_PM25 25.0

typedef struct {
    char nombre[50];
    float historialPM25[MAX_DIAS];
    float temperatura;
    float viento;
    float humedad;
    float actualPM25;
    float prediccionPM25;
} Zona;

void mostrarMenu();
void cargarDatos(Zona zonas[]);
void monitorearActual(Zona zonas[]);
void predecirContaminacion(Zona zonas[]);
void generarAlertas(Zona zonas[]);
void calcularPromedios(Zona zonas[]);
void generarRecomendaciones(Zona zonas[]);
void exportarReporte(Zona zonas[]);

#endif