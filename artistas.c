#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artistas.h"

void CargaArtista() {
    FILE *archivo = fopen("artistas.dat", "ab");
    if (archivo !=NULL) {
        Artista nuevo;
        printf("Ingrese el ID del nuevo artista");
        scanf("%d",&nuevo.id);
        while (getchar() != '\n');
        printf("Ingrese el nombre del nuevo artista");
        fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);        printf("Ingrese el genero musical");
        printf("Ingrese el genero musical");
        fgets(nuevo.genero, sizeof(nuevo.genero), stdin);
        fwrite(&nuevo,sizeof(Artista),1,archivo);
        fclose(archivo);
        printf("Artista nuevo agregado satisfactoriamente");

    } 
}
void MostrarArtista() {
    FILE *archivo = fopen("artistas.dat", "rb");
    if (archivo != NULL) {
        Artista artista;
        printf("Listado de artistas:\n");
        while (fread(&artista, sizeof(Artista),1,archivo)==1){
            printf("ID:%d | Artista: %s | Genero: %s\n", artista.id,artista.nombre,artista.genero);

        }
    fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo de artistas.\n");
    }
}
void OrdenarArtista() {
    FILE *archivo=fopen("artistas.dat","rb");
    if (archivo !=NULL){
        Artista lista[100];
        int cantidad=0;
        while (fread(&lista[cantidad],sizeof(Artista),1,archivo)==1){
            cantidad++;
        }
        fclose(archivo);
        if (cantidad>0){
            int menor;
            Artista aux;
            for (int i=0; i<cantidad-1;i++){
                menor=i;
                for (int j=i+1; j<cantidad; j++){
                    if (strcmp(lista[j].nombre,lista[menor].nombre)<0){
                        menor=j;
                    }
                }
                aux=lista[i];
                lista[i]=lista[menor];
                lista[menor]=aux;
            }


printf("Artistas ordenados por nombre:\n");
    for (int i=0; i< cantidad; i++){
        printf("ID:%d | Artista: %s | Genero: %s\n", lista[i].id, lista[i].nombre, lista[i].genero);        }
    }
    
    }
}

