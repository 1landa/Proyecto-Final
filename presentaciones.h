#ifndef PRESENTACIONES_H
#define PRESENTACIONES_H

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
void MostrarPresentacion(Presentacion arreglo[], int validos);
void ModificarPresentacion(Presentacion arreglo[], int validos);
int BajaPresentacion(Presentacion arreglo[], int validos);
void MostrarPresentacionesPorArtista(Presentacion arreglo[], int validos, int idArtista);
void MostrarPresentacionesPorEscenario(Presentacion arreglo[], int validos, int idEscenario);
int ComprobarSolapamiento(Presentacion actuales[], int validos, Presentacion nueva);
void OrdenaPresentacion(Presentacion arreglo[], int validos);
void CompruebaSolapamiento(Presentacion actuales[], int validos, Presentacion nueva);
void CambiaArchivoPresentaciones(Presentacion arreglo[], int validos);
#endif