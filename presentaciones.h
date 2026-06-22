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
#endif