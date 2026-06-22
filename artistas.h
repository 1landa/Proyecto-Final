#ifndef ARTISTAS_H
#define ARTISTAS_H
typedef struct {
    int id;
    char nombre[50];
    char genero[30];
} Artista;
int CargaArtista(Artista arreglo[], int validos, int dimension);
void MostrarArtista(Artista arreglo[], int validos);
void OrdenarArtista(Artista arreglo[], int validos);
#endif