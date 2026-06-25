#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artistas.h"

int LeerArtistasDesdeArchivo(Artista arreglo[], int dimension) {
    int validos = 0;
    FILE *archivo = fopen("artistas.dat", "rb");
    if (archivo != NULL) {
        while (fread(&arreglo[validos], sizeof(Artista), 1, archivo) == 1) {
            validos++;
        }
        fclose(archivo);
    }
    return validos;
}

void CambiaArchivo(Artista arreglo[], int validos) {
    FILE *archivo = fopen("artistas.dat", "wb");
    if (archivo != NULL) {
        fwrite(arreglo, sizeof(Artista), validos, archivo);
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo \n");
    }
}

int CargaArtista(Artista arreglo[], int validos, int dimension) {
    if (validos >= dimension) {
        printf("Limite maximo\n");
        return validos;
    }
    int continuar;
    printf("Desea ingresar un artista? 1 si 2 no \n");
    scanf("%d", &continuar);
    while (getchar() != '\n');
    if (continuar == 0) {
        return validos;
    }
    FILE *archivo = fopen("artistas.dat", "ab");
    if (archivo != NULL) {
        Artista nuevo;
        printf("Ingrese el nuevo ID:\n");
        scanf("%d", &nuevo.id);
        while (getchar() != '\n');
        printf("Ingrese el nombre del artista:\n");
        fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
        nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
        printf("Ingrese el genero musical: ");
        fgets(nuevo.genero, sizeof(nuevo.genero), stdin);
        nuevo.genero[strcspn(nuevo.genero, "\n")] = '\0';
        fwrite(&nuevo, sizeof(Artista), 1, archivo);
        fclose(archivo);
        arreglo[validos] = nuevo;
        return CargaArtista(arreglo, validos + 1, dimension);
    } else {
        printf("No se pudo abrir el archivo\n");
        return validos;
    }
}

void OrdenarArtista(Artista arreglo[], int validos) {
    if (validos < 1) {
        return;
    }
    int menor;
    Artista aux;    
    for (int i = 0; i < validos - 1; i++) {
        menor = i;
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
}

void MostrarArtista(Artista arreglo[], int validos) {
    if (validos == 0) {
        printf("No hay artistas\n");
        return;
    }
    OrdenarArtista(arreglo, validos);
    printf("Listado de artistas\n");
    for (int i = 0; i < validos; i++) {
        printf("+===============+\n");
        printf("+ID:            |%d\n", arreglo[i].id);
        printf("+===============+\n");
        printf("+Nombre:        |%s\n", arreglo[i].nombre);
        printf("+===============+\n");
        printf("+Genero:        |%s\n", arreglo[i].genero);
        printf("+===============+\n");
    }
}
int BuscarArtistaPorId(Artista arreglo[], int validos, int id) {
    for (int i = 0; i < validos; i++) {
        if (arreglo[i].id == id) {
            return i;
        }
    }
    return -1;
}
void ModificarArtista(Artista arreglo[], int validos) {
    int id;
    int pos;
    printf("Ingrese el ID del artista a modificar \n");
    scanf("%d", &id);
    while (getchar() != '\n');
    pos = BuscarArtistaPorId(arreglo, validos, id);
    if (pos != -1) {
        printf("Ingrese el nuevo nombre \n");
        fgets(arreglo[pos].nombre, sizeof(arreglo[pos].nombre), stdin);
        arreglo[pos].nombre[strcspn(arreglo[pos].nombre, "\n")] = '\0';
        printf("Ingrese el nuevo genero: ");
        fgets(arreglo[pos].genero, sizeof(arreglo[pos].genero), stdin);
        arreglo[pos].genero[strcspn(arreglo[pos].genero, "\n")] = '\0';
        printf("Artista modificado\n");
        CambiaArchivo(arreglo, validos);
    } else {
        printf("No existe un artista\n");
    }
}
int BajaArtista(Artista arreglo[], int validos) {
    int id;
    int pos;
    printf("Ingrese el ID del artista a eliminar \n ");
    scanf("%d", &id);
    pos = BuscarArtistaPorId(arreglo, validos, id);
    if (pos != -1) {
        for (int i = pos; i < validos - 1; i++) {
            arreglo[i] = i + 1 < validos ? arreglo[i + 1] : arreglo[i];
        }
        validos--;
        printf("Artista eliminado \n");
        CambiaArchivo(arreglo, validos);
    } else {
        printf("No existe ese artista \n");
    }
    return validos;
}
void menuArtistas(Artista artistas[], int *validosArtistas, int dimension) {
    int opcion;
    do {
        printf("+==============================+\n");
        printf("+ 1-Alta                       |\n");
        printf("+==============================+\n");
        printf("+ 2-Modificar                  |\n");
        printf("+==============================+\n");
        printf("+ 3-Baja                       |\n");
        printf("+==============================+\n");
        printf("+ 4-Mostrar                    |\n");
        printf("+==============================+\n");
        printf("+ 0-Volver                     |\n");
        printf("+==============================+\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
            system("cls");
                *validosArtistas = CargaArtista(artistas, *validosArtistas, dimension);
                break;
            case 2:
            system("cls");
                ModificarArtista(artistas, *validosArtistas);
                break;
            case 3:
            system("cls");
                *validosArtistas = BajaArtista(artistas, *validosArtistas);
                break;
            case 4:
            system("cls");
                MostrarArtista(artistas, *validosArtistas);
                break;
            case 0:
            system("cls");
            default:
            break;

        }
    } while (opcion != 0);
}