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
    printf("╔══════════════════════════════╗\n");
    printf("╠ID:                           ║%d\n", arreglo[i].id);
    printf("╠══════════════════════════════╣\n");
    printf("╠Nombre:                       ║%s\n", arreglo[i].nombre);
    printf("╠══════════════════════════════╣\n");
    printf("╠Genero:                       ║%s\n", arreglo[i].genero);
    printf("╚══════════════════════════════╝\n");
    }
}
   int BuscarArtistaPorId(Artista arreglo[], int validos, int id)
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
void ModificarArtista(Artista arreglo[], int validos)
{
    int id;
    int pos;

    printf("Ingrese el ID del artista a modificar: ");
    scanf("%d", &id);
    while(getchar() != '\n');

    pos = BuscarArtistaPorId(arreglo, validos, id);

    if(pos != -1)
    {
        printf("Ingrese el nuevo nombre: ");
        fgets(arreglo[pos].nombre,
              sizeof(arreglo[pos].nombre),
              stdin);

        arreglo[pos].nombre[
            strcspn(arreglo[pos].nombre, "\n")
        ] = '\0';

        printf("Ingrese el nuevo genero: ");
        fgets(arreglo[pos].genero,
              sizeof(arreglo[pos].genero),
              stdin);

        arreglo[pos].genero[
            strcspn(arreglo[pos].genero, "\n")
        ] = '\0';

        printf("Artista modificado correctamente\n");
    }
    else
    {
        printf("No existe un artista con ese ID\n");
    }
}
int BajaArtista(Artista arreglo[], int validos)
{
    int id;
    int pos;
    printf("Ingrese el ID del artista a eliminar: ");
    scanf("%d", &id);
    pos = BuscarArtistaPorId(arreglo, validos, id);
    if(pos != -1)
    {
        for(int i = pos; i < validos - 1; i++)
        {
            arreglo[i] = arreglo[i + 1];
        }
        validos--;
        printf("Artista eliminado correctamente \n");
    }
    else
    {
        printf("No existe un artista con ese ID \n");
    }
    return validos;
}
void menuArtistas(
    Artista artistas[],
    int *validosArtistas,
    int dimension)
{
    int opcion;
    do
    {
        printf("╔══════════════════════════════╗\n");
        printf("╠ 1-Alta                       ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("╠ 2-Modificar                  ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("╠ 3-Baja                       ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("╠ 4-Mostrar                    ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("╠ 0-Volver                     ║\n");
        printf("╚══════════════════════════════╝\n");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                *validosArtistas = CargaArtista(artistas, *validosArtistas, dimension);
                break;
            case 2:
                ModificarArtista(artistas, *validosArtistas);
                break;
            case 3:
                *validosArtistas = BajaArtista(artistas, *validosArtistas);
                break;
            case 4:
                MostrarArtista(artistas, *validosArtistas);
                break;
        }
    }while(opcion != 0);
}