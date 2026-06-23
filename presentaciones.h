#ifndef PRESENTACIONES_H
#define PRESENTACIONES_H

typedef struct {
    int hora;
    int minutos;
} Horario;

typedef struct {
    int horas;
    int minutos;
} Duracion;

typedef struct {
    int id;
    int idArtista;
    int idEscenario;
    Horario horario;
    Duracion duracion;
} Presentacion;

int CargaPresentacion(Presentacion arreglo[], int validos, int dimension);
void MostrarPresentacion(Presentacion arreglo[], int validos);
void ModificarPresentacion(
    Presentacion arreglo[],
    int validos);

int BajaPresentacion(
    Presentacion arreglo[],
    int validos);

void MostrarPresentacionesPorArtista(
    Presentacion arreglo[],
    int validos,
    int idArtista);

void MostrarPresentacionesPorEscenario(
    Presentacion arreglo[],
    int validos,
    int idEscenario);
    void MostrarPresentacionesPorEscenario(
    Presentacion arreglo[],
    int validos,
    int idEscenario);
#endif