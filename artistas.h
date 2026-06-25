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
int BuscarArtistaPorId(
    Artista arreglo[],
    int validos,
    int id);

void ModificarArtista(
    Artista arreglo[],
    int validos);

int BajaArtista(
    Artista arreglo[],
    int validos);
int LeerArtistasDesdeArchivo(Artista arreglo[], int dimension);
void OrdenarArtista(Artista arreglo[], int validos);
#endif