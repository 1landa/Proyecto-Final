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
    if (archivo!=NULL)
    {
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
        printf("Ingrese la horario de inicio, hora y despues minutos): ");
        scanf("%d", &nuevo.horario.hora);
        scanf("%d", &nuevo.horario.minutos);
        while (getchar() != '\n');
        printf("Ingrese la duracion: ");
        scanf("%d %d", &nuevo.duracion.horas, &nuevo.duracion.minutos);
        while (getchar() != '\n');
        
        fwrite(&nuevo,sizeof(Presentacion),1,archivo);
        fclose(archivo);
        printf("Presentacion agregada\n");
        arreglo[validos]=nuevo;
        validos++;
        return validos;   
    }
}
void MostrarPresentacion(Presentacion arreglo[], int validos) 
{
    if (validos == 0) 
    {
        printf("No hay presentaciones para mostrar\n");
        return;
    }
    printf("Listado de presentaciones\n");
    for (int i=0; i<validos; i++) 
    {
        printf("╔══════════════════════════════╗\n");
        printf("╠ID:                           ║%d\n", arreglo[i].id);
        printf("╠══════════════════════════════╣\n");
        printf("╠ID Artista:                   ║%d\n", arreglo[i].idArtista);
        printf("╠══════════════════════════════╣\n");
        printf("╠ID Escenario:                 ║%d\n", arreglo[i].idEscenario); 
        printf("╠══════════════════════════════╣\n");
        printf("╠Horario:                      ║%02d:%02d\n", arreglo[i].horario.hora, arreglo[i].horario.minutos);
        printf("╠══════════════════════════════╣\n");
        printf("╠Duracion:                     ║%02d:%02d\n", arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
        printf("╚══════════════════════════════╝\n");
    }
}
int BuscarPresentacionPorId(Presentacion arreglo[], int validos, int id)
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
void ModificarPresentacion(Presentacion arreglo[], int validos)
{
    int id;
    int pos;
    printf("Ingrese el ID de la presentacion a modificar: ");
    scanf("%d", &id);
    pos = BuscarPresentacionPorId(arreglo, validos, id);
    if(pos != -1)
    {
        printf("Nuevo ID de artista: ");
        scanf("%d", &arreglo[pos].idArtista);
        printf("Nuevo ID de escenario: ");
        scanf("%d", &arreglo[pos].idEscenario);
        printf("Nueva hora y minutos de inicio: ");
        scanf("%d %d",
        &arreglo[pos].horario.hora,
        &arreglo[pos].horario.minutos);
        printf("Nueva duracion (horas minutos): ");
        scanf("%d %d",
        &arreglo[pos].duracion.horas,
        &arreglo[pos].duracion.minutos);
        CambiaArchivoPresentaciones(arreglo, validos);
    printf("Presentacion modificada correctamente\n");
    }
    else
    {
    printf("No existe una presentacion con ese ID\n");
    }
}
int BajaPresentacion(Presentacion arreglo[], int validos)
{
    int id;
    int pos;
    printf("Ingrese el ID de la presentacion a eliminar");
    scanf("%d", &id);
    pos = BuscarPresentacionPorId(arreglo, validos, id);
    if(pos != -1)
    {
        for(int i = pos; i < validos - 1; i++)
        {
        arreglo[i] = arreglo[i + 1];
        }
        validos--;
        printf("Presentacion eliminada correctamente\n");
        CambiaArchivoPresentaciones(arreglo, validos);
    }
    else
    {
        printf("No existe una presentacion con ese ID\n");
    }
    return validos;
}
void MostrarPresentacionesPorArtista(
    Presentacion arreglo[],
    int validos,
    int idArtista)
{
    int encontrado = 0;
    for(int i = 0; i < validos; i++)
    {
        if(arreglo[i].idArtista == idArtista)
        {
        printf("╔══════════════════════════════╗\n");
        printf("╠ID:                           ║%d\n", arreglo[i].id);
        printf("╠══════════════════════════════╣\n");
        printf("╠Escenario:                    ║%d\n", arreglo[i].idEscenario); 
        printf("╠══════════════════════════════╣\n");
        printf("╠Horario:                      ║%02d:%02d\n", arreglo[i].horario.hora, arreglo[i].horario.minutos);
        printf("╚══════════════════════════════╝\n");
        printf("╠Duracion:                     ║%02d:%02d\n", arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
            encontrado = 1;
        }
    }
    if(!encontrado)
    {
    printf("No hay presentaciones para ese artista\n");
    }
}
void MostrarPresentacionesPorEscenario(Presentacion arreglo[], int validos, int idEscenario) {
    int encontrado = 0;
    for(int i = 0; i < validos; i++) {
        if(arreglo[i].idEscenario == idEscenario) {
        printf("╔══════════════════════════════╗\n");
        printf("╠ID:                           ║%d\n", arreglo[i].id);
        printf("╠══════════════════════════════╣\n");
        printf("╠Artista:                      ║%d\n", arreglo[i].idArtista);
        printf("╠══════════════════════════════╣\n");
        printf("╠Horario:                      ║%02d:%02d\n", arreglo[i].horario.hora, arreglo[i].horario.minutos);
        printf("╚══════════════════════════════╝\n");
            encontrado = 1;
        }
    }
}
void OrdenaPresentacion(Presentacion arreglo[], int validos) {
    for (int i=0; i < validos-1; i++) {
        for (int j=0; j <validos-i-1; j++) {
            int inicioJ=arreglo[j].horario.hora*60+arreglo[j].horario.minutos;
            int inicioSig=arreglo[j+1].horario.hora*60+arreglo[j+1].horario.minutos;
            if (inicioJ > inicioSig) {
            Presentacion temp = arreglo[j];
            arreglo[j] = arreglo[j+1];
            arreglo[j+1] = temp;
            }
        }
    }
}
int ComprobarSolapamiento(Presentacion actuales[], int validos, Presentacion nueva) {
    for (int i = 0; i < validos; i++) {
        if (actuales[i].idEscenario == nueva.idEscenario) {
            int inicioActual=actuales[i].horario.hora*60+actuales[i].horario.minutos;
            int finActual=inicioActual+actuales[i].duracion.horas*60+actuales[i].duracion.minutos;
            int inicioNueva=nueva.horario.hora*60+nueva.horario.minutos;
            int finNueva=inicioNueva+nueva.duracion.horas*60+nueva.duracion.minutos;
            if ((inicioNueva<finActual) && (finNueva>inicioActual)) {
                return 1;
            }
    }

    return 0;
}
}
void CambiaArchivoPresentaciones(Presentacion arreglo[], int validos) {
    FILE *archivo=fopen("presentaciones.dat","wb");
    if (archivo!=NULL) {
    fwrite(arreglo, sizeof(Presentacion), validos, archivo);
    fclose(archivo);
    }
}