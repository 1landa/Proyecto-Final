#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "presentaciones.h"

Horario crearHorario(int horas, int minutos){
    Horario h;
    if(horas>=0 && horas <24 && minutos >= 0 && minutos <60){
        h.hora=horas;
        h.minutos=minutos;
        h.esValido=1;
    }else{
        h.hora=0;
        h.minutos=0;
        h.esValido=0;
    }
    return h;
}
Duracion crearDuracion(int horas, int minutos) {
    Duracion d;
    if(horas>=0 && minutos >=0 && minutos <60){
        d.horas=0;
        d.minutos=0;
        d.esValido=0;
    }
    return d;
}
int LeerPresentacionesDesdeArchivo(Presentacion arreglo[], int dimension) {
    int validos = 0;
    FILE *archivo = fopen("presentaciones.dat", "rb");
    if (archivo != NULL) {
        while (fread(&arreglo[validos], sizeof(Presentacion), 1, archivo) == 1) {
            validos++;
        }
        fclose(archivo);
    }
    return validos;
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
int CargaPresentacion(Presentacion arreglo[], int validos, int dimension) {
    if (validos == dimension) {
        printf("Limite maximo\n");
        return validos;
    }

    int continuar;
    system("cls");
    printf("Desea ingresar una presentacion? 1 si 0 no: \n");
    scanf("%d", &continuar);
    while (getchar() != '\n');
    if (continuar == 0) {
        return validos;
    }

    FILE *archivo = fopen("presentaciones.dat", "ab");
    if (archivo != NULL) {
        Presentacion nuevo;
        system("cls");
    printf("Ingrese el id de la presentacion\n");
    scanf("%d", &nuevo.id);
        while (getchar() != '\n');
            printf("Ingrese el id del artista\n");
            scanf("%d", &nuevo.idArtista);
        while (getchar() != '\n');
        printf("Ingrese el id del escenario\n");
        scanf("%d", &nuevo.idEscenario);
        while (getchar() != '\n');
         printf("Ingrese la duracion en horas\n");
        scanf("%d", &nuevo.duracion.horas);
        while (getchar() != '\n');
        printf ("Una vez ingresada la hora, indique los minutos\n");
        scanf ("%d", &nuevo.duracion.minutos);
        while (getchar() != '\n');
        printf("Ingrese la duracion en horas\n");
        scanf("%d", &nuevo.duracion.horas);
        while (getchar() != '\n');
        printf("Una vez ingresada la hora, indique los minutos\n");
        scanf("%d", &nuevo.duracion.minutos);
        while (getchar() != '\n');
        fwrite(&nuevo, sizeof(Presentacion), 1, archivo);
        fclose(archivo);
        arreglo[validos] = nuevo;       
        return CargaPresentacion(arreglo, validos + 1, dimension);
    }
    return validos;
}
void MostrarPresentacion(Presentacion arreglo[], int validos) 
{
    if (validos == 0) 
    {
        printf("No hay presentaciones para mostrar\n");
        return;
    }
    system("cls");
    printf("Listado de presentaciones\n");
    for (int i=0; i<validos; i++) 
    {
        printf("+==============================+\n");
        printf("+ID:                           |%d\n", arreglo[i].id);
        printf("+==============================+\n");
        printf("+ID Artista:                   |%d\n", arreglo[i].idArtista);
        printf("+==============================+\n");
        printf("+ID Escenario:                 |%d\n", arreglo[i].idEscenario); 
        printf("+==============================+\n");
        printf("+Horario:                      |%02d:%02d\n", arreglo[i].horario.hora, arreglo[i].horario.minutos);
        printf("+==============================+\n");
        printf("+Duracion:                     |%02d:%02d\n", arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
        printf("+==============================+\n");
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
    printf("Ingrese el ID de la presentacion a modificar:\n");
    scanf("%d", &id);
    pos = BuscarPresentacionPorId(arreglo, validos, id);
    if(pos != -1)
    {
        printf("Nuevo ID de artista:\n");
        scanf("%d", &arreglo[pos].idArtista);
        printf("Nuevo ID de escenario:\n ");
        scanf("%d", &arreglo[pos].idEscenario);
        printf("Nueva hora y minutos de inicio:\n ");
        scanf("%d %d",
        &arreglo[pos].horario.hora,
        &arreglo[pos].horario.minutos);
        printf("Nueva duracion\n ");
        scanf("%d %d",
        &arreglo[pos].duracion.horas,
        &arreglo[pos].duracion.minutos);
        CambiaArchivoPresentaciones(arreglo, validos);
        CambiaArchivoPresentaciones(presentaciones, validos);
        printf("Presentacion modificada\n");
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
    printf("Ingrese el ID de la presentacion a eliminar\n");
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
        CambiaArchivoPresentaciones(presentaciones, validos);
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
            printf("+==============================+\n");
            printf("+ID:                           |%d\n", arreglo[i].id);
            printf("+==============================+\n");
            printf("+Escenario:                    |%d\n", arreglo[i].idEscenario); 
            printf("+==============================+\n");
            printf("+Horario:                      |%02d:%02d\n", arreglo[i].horario.hora, arreglo[i].horario.minutos);
            printf("+==============================+\n");
            printf("+Duracion:                     |%02d:%02d\n", arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
            printf("+==============================+\n");
            encontrado = 1;
        }
    }
    if(!encontrado)
    {
    printf("No hay presentaciones para ese artista\n");
    }
}
void OrdenaPresentacion(Presentacion arreglo[], int validos, Artista artistas[], int validosArtistas) {
    for (int i = 0; i < validos - 1; i++) {
        for (int j = 0; j < validos - i - 1; j++) {
            char nombreJ[50] = "";
            int posArtJ = BuscarArtistaPorId(artistas, validosArtistas, arreglo[j].idArtista);
            if (posArtJ != -1) {
                strcpy(nombreJ, artistas[posArtJ].nombre);
            }
            char nombreSig[50] = "";
            int posArtSig = BuscarArtistaPorId(artistas, validosArtistas, arreglo[j+1].idArtista);
            if (posArtSig != -1) {
                strcpy(nombreSig, artistas[posArtSig].nombre);
            }
            if (strcasecmp(nombreJ, nombreSig) > 0) {
                Presentacion temp = arreglo[j];
                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = temp;
            }
        }
    }
}
void MostrarPresentacionesPorEscenario(Presentacion arreglo[], int validos, int idEscenario) {
    int encontrado = 0;
    for(int i = 0; i < validos; i++) {
        if(arreglo[i].idEscenario == idEscenario) {
        printf("+==============================+\n");
        printf("+ID:                           |%d\n", arreglo[i].id);
        printf("+==============================+\n");
        printf("+Artista:                      |%d\n", arreglo[i].idArtista);
        printf("+==============================+\n");
        printf("+Horario:                      |%02d:%02d\n", arreglo[i].horario.hora, arreglo[i].horario.minutos);
        printf("+==============================+\n");
            encontrado = 1;
        }
    }
}
void CambiaArchivoPresentaciones(Presentacion arreglo[], int validos) {
    FILE *archivo=fopen("presentaciones.dat","wb");
    if (archivo!=NULL) {
    fwrite(arreglo, sizeof(Presentacion), validos, archivo);
    fclose(archivo);
    }
}
void CambiaArchivoPresentaciones(Presentacion arreglo[], int validos) {
    FILE *archi = fopen("presentaciones.dat", "wb");
    if (archi != NULL) {
        fwrite(arreglo,sizeof(Presentacion))
        fcloe(archi);
    }else{
        printf("No se pudo abrir el archivo");
    }
}