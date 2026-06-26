#ifndef ESCENARIOS_H
#define ESCENARIOS_H

typedef struct {
    int id;
    char nombre[50];
} Escenario;

int CargaEscenario(Escenario arreglo[], int validos, int dimension);
void OrdenarEscenario(Escenario arreglo[], int validos);
void MostrarEscenario(Escenario arreglo[], int validos);
int BuscarEscenarioPorId(Escenario arreglo[], int validos, int id);
void ModificarEscenario(Escenario arreglo[], int validos);
int BajaEscenario(Escenario arreglo[], int validos);
int LeerEscenariosDesdeArchivo(Escenario arreglo[], int dimension);
void CambiaArchivoEscenarios(Escenario arreglo[], int validos);
void menuEscenarios(Escenario escenarios[], int *validosEscenarios, int dimension);
#endif