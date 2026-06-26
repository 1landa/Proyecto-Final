#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "presentaciones.h"
#include "artistas.h"
#include "escenarios.h"

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
        d.horas=horas;
        d.minutos=minutos;
        d.esValido=1;
    }else{
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
void CambiaArchivoPresentaciones(Presentacion arreglo[], int validos) {
    FILE *archi = fopen("presentaciones.dat", "wb");
    if (archi != NULL) {
        fwrite(arreglo, sizeof(Presentacion), validos, archi);
        fclose(archi);
    } else {
        printf("No se pudo abrir el archivo\n");
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
    }
    return 0;
}
Presentacion cargarUnaPresentacion(int idAsignado) {
    Presentacion nuevo;
    nuevo.id = idAsignado;
    printf("Ingrese el id del artista\n");
    scanf("%d", &nuevo.idArtista);
    while (getchar() != '\n');
    printf("Ingrese el id del escenario\n");
    scanf("%d", &nuevo.idEscenario);
    while (getchar() != '\n');
    printf("Ingrese la hora de inicio\n");
    scanf("%d", &nuevo.horario.hora);
    while (getchar() != '\n');
    printf("Indique los minutos de inicio\n");
    scanf("%d", &nuevo.horario.minutos);
    while (getchar() != '\n');
    printf("Ingrese la duracion en horas\n");
    scanf("%d", &nuevo.duracion.horas);
    while (getchar() != '\n');
    printf("Una vez ingresada la hora, indique los minutos\n");
    scanf("%d", &nuevo.duracion.minutos);
    while (getchar() != '\n');
    return nuevo;
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
        system("cls");
        int id;
        printf("Ingrese el id de la presentacion\n");
        scanf("%d", &id);
        while (getchar() != '\n');
        
        Presentacion nuevo = cargarUnaPresentacion(id);
        
        fwrite(&nuevo, sizeof(Presentacion), 1, archivo);
        fclose(archivo);
        arreglo[validos] = nuevo;       
        return CargaPresentacion(arreglo, validos + 1, dimension);
    }
    return validos;
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
        scanf("%d %d", &arreglo[pos].horario.hora, &arreglo[pos].horario.minutos);
        printf("Nueva duracion\n ");
        scanf("%d %d", &arreglo[pos].duracion.horas, &arreglo[pos].duracion.minutos);
        CambiaArchivoPresentaciones(arreglo, validos);
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
        printf("Presentacion eliminada \n");
        CambiaArchivoPresentaciones(arreglo, validos);
    }
    else
    {
        printf("No existe una presentacion con ese ID\n");
    }
    return validos;
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

void MostrarUnaPresentacion(Presentacion p, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    int posArt = BuscarArtistaPorId(artistas, validosArtistas, p.idArtista);
    int posEsc = BuscarEscenarioPorId(escenarios, validosEscenarios, p.idEscenario);
    
    printf("+=================================+\n");
    printf("+ ID Presentacion:             | %d\n", p.id);
    printf("+=================================+\n");
    if (posArt != -1) {
        printf("+ Artista (ID %d):            | %s\n", p.idArtista, artistas[posArt].nombre);
        printf("+ Genero:                     | %s\n", artistas[posArt].genero);
    } else {
        printf("+ ID Artista (No encontrado) | %d\n", p.idArtista);
    }
    printf("+=======================================+\n");
    if (posEsc != -1) {
        printf("+ Escenario (ID %d):           | %s\n", p.idEscenario, escenarios[posEsc].nombre);
    } else {
        printf("+ ID Escenario (No encontrado):| %d\n", p.idEscenario);
    }
    printf("+================================+\n");
    printf("+ Horario:                    | %02d:%02d\n", p.horario.hora, p.horario.minutos);
    printf("+ Duracion:                   | %02d:%02d\n", p.duracion.horas, p.duracion.minutos);
    printf("+================================+\n\n");
}

void MostrarPresentacion(Presentacion arreglo[], int validos, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    if (validos == 0) {
        printf("No hay presentaciones para mostrar\n");
        return;
    }
    system("cls");
    printf("Listado de presentaciones\n");
    for(int i = 0; i < validos; i++) {
        MostrarUnaPresentacion(arreglo[i], artistas, validosArtistas, escenarios, validosEscenarios);
    }
}

void MostrarPresentacionesPorArtista(Presentacion arreglo[], int validos, int idArtista, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    int encontrado = 0;
    for(int i = 0; i < validos; i++) {
        if(arreglo[i].idArtista == idArtista) {
            MostrarUnaPresentacion(arreglo[i], artistas, validosArtistas, escenarios, validosEscenarios);
            encontrado = 1;
        }
    }
    if(!encontrado) {
        printf("No se encontraron presentaciones para el artista con ID %d\n", idArtista);
    }
}

void MostrarPresentacionesPorEscenario(Presentacion arreglo[], int validos, int idEscenario, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    int encontrado = 0;
    for(int i = 0; i < validos; i++) {
        if(arreglo[i].idEscenario == idEscenario) {
            MostrarUnaPresentacion(arreglo[i], artistas, validosArtistas, escenarios, validosEscenarios);
            encontrado = 1;
        }
    }
    if(!encontrado) {
        printf("No se encontraron presentaciones para el escenario con ID %d\n", idEscenario);
    }
}

void menuPresentaciones(Presentacion presentaciones[], int *validosPresentaciones, int dimension, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    int opcion;
    do {
        printf("+==============================+\n");
        printf("+    GESTION PRESENTACIONES    |\n");
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
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                system("cls");
                *validosPresentaciones = CargaPresentacion(presentaciones, *validosPresentaciones, dimension);
                break;
            case 2:
                system("cls");
                ModificarPresentacion(presentaciones, *validosPresentaciones);
                break;
            case 3:
                system("cls");
                *validosPresentaciones = BajaPresentacion(presentaciones, *validosPresentaciones);
                break;
            case 4:
                system("cls");
                MostrarPresentacion(presentaciones, *validosPresentaciones, artistas, validosArtistas, escenarios, validosEscenarios);
                break;
            case 0:
                system("cls");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while (opcion != 0);
}