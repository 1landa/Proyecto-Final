#ifndef ARTISTAS_H
#define ARTISTAS_H
typedef struct {
    int id;
    char nombre[50];
    char genero[30];
} Artista;

void CargaArtista();
void MostrarArtista();
void OrdenarArtista();
#endif