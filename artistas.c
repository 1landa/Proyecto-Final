#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artistas.h"

int CargaArtista(Artista arreglo[], int validos, int dimension) {
    if (validos == dimension){
        printf("Limite maximo ");
        return validos;
    }
        FILE *archivo = fopen("artistas.dat", "ab");

    if (archivo !=NULL) {
        Artista nuevo;
        printf("Ingrese el ID del nuevo artista");
        scanf("%d",&nuevo.id);
        while (getchar() != '\n');
        printf("Ingrese el nombre del nuevo artista");
        fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
        nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
        printf("Ingrese el genero musical");
        fgets(nuevo.genero, sizeof(nuevo.genero), stdin);
        nuevo.genero[strcspn(nuevo.genero, "\n")] = '\0';
        fwrite(&nuevo,sizeof(Artista),1,archivo);
        fclose(archivo);
        printf("Artista nuevo agregado satisfactoriamente");
        arreglo[validos]=nuevo;
        validos++;

    }
    return validos;
}

void OrdenarArtista(Artista arreglo[], int validos) {
    if (validos<1){
        printf("No hay artistas para ordenar");
        return;
    }
    int menor;
    Artista aux;    
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
    printf("Los artistas fueron ordenados alfabeticamente\n");
}

void MostrarArtista(Artista arreglo[], int validos) {
    if (validos == 0) {
        printf("No hay artistas para mostrar\n");
        return;
    }
    printf("Listado de artistas\n");
    for (int i=0; i<validos; i++) {
        printf("ID: %d\n", arreglo[i].id);
        printf("Nombre: %s\n", arreglo[i].nombre);
        printf("Genero: %s\n", arreglo[i].genero);
        printf("══════════════════════\n");
    }
}
