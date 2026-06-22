#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "presentaciones.h"

int CargaPresentacion(Presentacion arreglo[], int validos, int dimension) {
    if (validos == dimension){
        printf("Limite maximo ");
        return validos;
    }
    FILE *archivo = fopen("presentaciones.dat", "ab");
    if (archivo!=NULL){
        Presentacion nuevo;
        printf("Ingrese el ID de la nueva presentacion: ");
        scanf("%d",&nuevo.id);
        while (getchar() != '\n');
        printf("Ingrese el ID del artista: ");
        scanf("%d",&nuevo.idArtista);
        while (getchar() != '\n');
        printf("Ingrese el ID del escenario: ");
        scanf("%d",&nuevo.idEscenario);
        while (getchar() != '\n');
        printf("Ingrese la hora de inicio, hora y despues minutos): ");
        scanf("%d %d", &nuevo.horario.hora, &nuevo.horario.minutos);
        while (getchar() != '\n');
        printf("Ingrese la duracion: ");
        scanf("%d %d", &nuevo.duracion.horas, &nuevo.duracion.minutos);
        while (getchar() != '\n');
        
        fwrite(&nuevo,sizeof(Presentacion),1,archivo);
        fclose(archivo);
        printf("Presentacion agregada\n");
        arreglo[validos]=nuevo;   
    }
    return validos + 1;
}

void MostrarPresentacion(Presentacion arreglo[], int validos) {
    if (validos == 0) {
        printf("No hay presentaciones para mostrar\n");
        return;
    }
    printf("Listado de presentaciones\n");
    for (int i=0; i<validos; i++) {
        printf("ID: %d\n", arreglo[i].id);
        printf("ID Artista: %d\n", arreglo[i].idArtista);
        printf("ID Escenario: %d\n", arreglo[i].idEscenario);
        printf("Horario: %02d:%02d\n", arreglo[i].horario.hora, arreglo[i].horario.minutos);
        printf("Duracion: %02d:%02d\n", arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
        printf("══════════════════════\n");
    }
}
