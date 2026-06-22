#ifndef ESCENARIOS_H
#define ESCENARIOS_H

typedef struct {
    int id;
    char nombre[50];
} Escenario;

int CargaEscenario(Escenario arreglo[], int validos, int dimension);
void MostrarEscenario(Escenario arreglo[], int validos);

#endif