#ifndef PRESENTACIONES_H
#define PRESENTACIONES_H
#include "artistas.h"
#include "escenarios.h"

typedef struct 
{
    int hora;
    int minutos;
    int esValido; 
} Horario;

typedef struct 
{
    int horas;
    int minutos;
    int esValido;
} Duracion;

typedef struct 
{
    int id;
    int idArtista;
    int idEscenario;
    Horario horario;
    Duracion duracion;
} Presentacion;

Horario crearHorario(int horas, int minutos);
Duracion crearDuracion(int horas, int minutos);
Presentacion cargarUnaPresentacion(int idAsignado);
int CargaPresentacion(Presentacion arreglo[], int validos, int dimension);
void ModificarPresentacion(Presentacion arreglo[], int validos);
int BajaPresentacion(Presentacion arreglo[], int validos);
int ComprobarSolapamiento(Presentacion actuales[], int validos, Presentacion nueva);
void OrdenaPresentacion(Presentacion arreglo[], int validos, Artista artistas[], int validosArtistas);
void CambiaArchivoPresentaciones(Presentacion arreglo[], int validos);
int LeerPresentacionesDesdeArchivo(Presentacion arreglo[], int dimension);
void MostrarUnaPresentacion(Presentacion p, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios);
void MostrarPresentacion(Presentacion arreglo[], int validos, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios);
void MostrarPresentacionesPorArtista(Presentacion arreglo[], int validos, int idArtista, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios);
void MostrarPresentacionesPorEscenario(Presentacion arreglo[], int validos, int idEscenario, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios);
void menuPresentaciones(Presentacion presentaciones[], int *validosPresentaciones, int dimension, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios);
void ExportarPresentacionesATexto(Presentacion arreglo[], int validos, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios, char nombreArchivo[]);
void BuscarPresentacionPorNombreArtista(Presentacion presentaciones[], int validosPres, Artista artistas[], int validosArt, Escenario escenarios[], int validosEsc);
void BuscarPresentacionPorNombreEscenario(Presentacion presentaciones[], int validosPres, Artista artistas[], int validosArt, Escenario escenarios[], int validosEsc);
#endif