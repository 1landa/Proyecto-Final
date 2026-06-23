#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escenarios.h"

int CargaEscenario(Escenario arreglo[], int validos, int dimension) {
    if (validos == dimension){
        printf("Limite maximo ");
        return validos;
    }
    FILE *archivo = fopen("escenarios.dat", "ab");
    if (archivo!=NULL){
        Escenario nuevo;
        printf("Ingrese el ID del nuevo escenario: ");
        scanf("%d",&nuevo.id);

        while (getchar() != '\n');
        printf("Ingrese el nombre del nuevo escenario: ");
        fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
        nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
        fwrite(&nuevo,sizeof(Escenario),1,archivo);
        fclose(archivo);
        printf("Escenario agregado");
        arreglo[validos]=nuevo; 
        validos++;  
        return validos;
    }
}

void OrdenarEscenario(Escenario arreglo[], int validos) {
    if (validos <1){
        printf("No hay escenarios");
        return;
    
    }
    int menor;
    Escenario aux;
for (int i=0; i<validos-1; i++) {
        menor=i;
        for (int j = i + 1; j < validos; j++) {
            if (strcmp(arreglo[j].nombre, arreglo[menor].nombre) < 0) {
                menor = j;
            }
        }
        if (menor != i) {
            aux = arreglo[i];
            arreglo[i] = arreglo[menor];
            arreglo[menor] = aux;
        }
    }
    printf("Escenarios ordenados\n");
}
void MostrarEscenario(Escenario arreglo[], int validos) {
    if (validos == 0) {
        printf("No hay escenarios para mostrar\n");
        return;
    }
    printf("Listado de escenarios\n");
    for (int i=0; i<validos; i++) {
        printf("ID: %d\n", arreglo[i].id);
        printf("Nombre: %s\n", arreglo[i].nombre);
        printf("══════════════════════\n");
    }
}
int BuscarEscenarioPorId(Escenario arreglo[], int validos, int id)
{
    for(int i = 0; i < validos; i++)
    {
        if(arreglo[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

void ModificarEscenario(Escenario arreglo[], int validos)
{
    int id;
    int pos;

    printf("Ingrese el ID del escenario a modificar: ");
    scanf("%d", &id);
    while(getchar() != '\n');

    pos = BuscarEscenarioPorId(arreglo, validos, id);

    if(pos != -1)
    {
        printf("Ingrese el nuevo nombre: ");

        fgets(arreglo[pos].nombre,
              sizeof(arreglo[pos].nombre),
              stdin);

        arreglo[pos].nombre[
            strcspn(arreglo[pos].nombre, "\n")
        ] = '\0';

        printf("Escenario modificado correctamente\n");
    }
    else
    {
        printf("No existe un escenario con ese ID\n");
    }
}

int BajaEscenario(Escenario arreglo[], int validos)
{
    int id;
    int pos;

    printf("Ingrese el ID del escenario a eliminar: ");
    scanf("%d", &id);

    pos = BuscarEscenarioPorId(arreglo, validos, id);

    if(pos != -1)
    {
        for(int i = pos; i < validos - 1; i++)
        {
            arreglo[i] = arreglo[i + 1];
        }

        validos--;

        printf("Escenario eliminado correctamente\n");
    }
    else
    {
        printf("No existe un escenario con ese ID\n");
    }

    return validos;
}