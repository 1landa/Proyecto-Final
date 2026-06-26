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
    FILE *archivo = fopen("presentaciones.dat", "wb");
    if (archivo != NULL) {
        fwrite(arreglo, sizeof(Presentacion), validos, archivo);
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo\n");
    }
}
int ComprobarSolapamiento(Presentacion actuales[], int validos, Presentacion nueva) {
    int inicioNueva = nueva.horario.hora * 60 + nueva.horario.minutos;
    int finNueva = inicioNueva + (nueva.duracion.horas * 60 + nueva.duracion.minutos);

    for (int i = 0; i < validos; i++) {
        if (actuales[i].id != nueva.id) {
            int inicioActual = actuales[i].horario.hora * 60 + actuales[i].horario.minutos;
            int finActual = inicioActual + (actuales[i].duracion.horas * 60 + actuales[i].duracion.minutos);

            if (inicioNueva < finActual && inicioActual < finNueva) {
                if (actuales[i].idEscenario == nueva.idEscenario) {
                    return 1;
                }
                if (actuales[i].idArtista == nueva.idArtista) {
                    return 2;
                }
            }
        }
    }
    return 0;
}
Presentacion cargarUnaPresentacion(int idAsignado) {
    Presentacion p;
    p.id = idAsignado;
    
    printf("Ingrese ID del Artista: ");
    scanf("%d", &p.idArtista);
    printf("Ingrese ID del Escenario: ");
    scanf("%d", &p.idEscenario);
    
    int h, m;
    do {
        printf("Ingrese hora de inicio (0-23): ");
        scanf("%d", &h);
        printf("Ingrese minutos de inicio (0-59): ");
        scanf("%d", &m);
        p.horario = crearHorario(h, m);
    } while(!p.horario.esValido);

    do {
        printf("Ingrese duracion (horas): ");
        scanf("%d", &h);
        printf("Ingrese duracion (minutos): ");
        scanf("%d", &m);
        p.duracion = crearDuracion(h, m);
    } while(!p.duracion.esValido);

    return p;
}
int CargaPresentacion(Presentacion arreglo[], int validos, int dimension) {
    if (validos >= dimension) {
        printf("Limite maximo\n");
        return validos;
    }
    int continuar;
    printf("Desea ingresar una presentacion? 1 si 2 no\n");
    scanf("%d", &continuar);
    
    while(continuar == 1 && validos < dimension) {
        int proxId = (validos == 0) ? 1 : arreglo[validos - 1].id + 1;
        Presentacion nueva = cargarUnaPresentacion(proxId);
        
        int solapamiento = ComprobarSolapamiento(arreglo, validos, nueva);
        if (solapamiento == 1) {
            printf("Solapamiento de horarios en el mismo escenario.\n");
        } else if (solapamiento == 2) {
            printf("El artista ya tiene otra presentacion en ese horario.\n");
        } else {
            arreglo[validos] = nueva;
            validos++;
            CambiaArchivoPresentaciones(arreglo, validos);
        }
        
        if(validos < dimension) {
            printf("Desea ingresar otra presentacion? 1 si 2 no\n");
            scanf("%d", &continuar);
        }
    }
    return validos;
}
void ModificarPresentacion(Presentacion arreglo[], int validos) {
    int idBuscado;
    printf("Ingrese ID de presentacion a modificar: ");
    scanf("%d", &idBuscado);
    
    int indice = -1;
    for(int i = 0; i < validos; i++) {
        if(arreglo[i].id == idBuscado) {
            indice = i;
            break;
        }
    }
    
    if(indice != -1) {
        Presentacion copia = cargarUnaPresentacion(idBuscado);
        int solapamiento = ComprobarSolapamiento(arreglo, validos, copia);
        if (solapamiento == 1) {
            printf("Error: Solapamiento detectado en el escenario.\n");
        } else if (solapamiento == 2) {
            printf("Error: Solapamiento detectado para el artista.\n");
        } else {
            arreglo[indice] = copia;
            CambiaArchivoPresentaciones(arreglo, validos);
            printf("Modificado correctamente.\n");
        }
    } else {
        printf("ID no encontrado.\n");
    }
}
int BajaPresentacion(Presentacion arreglo[], int validos) {
    int idBuscado;
    printf("Ingrese ID de presentacion a eliminar: ");
    scanf("%d", &idBuscado);
    
    int indice = -1;
    for(int i = 0; i < validos; i++) {
        if(arreglo[i].id == idBuscado) {
            indice = i;
            break;
        }
    }
    
    if(indice != -1) {
        for(int i = indice; i < validos - 1; i++) {
            arreglo[i] = arreglo[i + 1];
        }
        validos--;
        CambiaArchivoPresentaciones(arreglo, validos);
        printf("Presentacion eliminada.\n");
    } else {
        printf("ID no encontrado.\n");
    }
    return validos;
}
void OrdenaPresentacion(Presentacion arreglo[], int validos, Artista artistas[], int validosArtistas) {
    for (int i = 0; i < validos - 1; i++) {
        for (int j = i + 1; j < validos; j++) {
            char nombreI[50] = "";
            char nombreJ[50] = "";
            
            for (int k = 0; k < validosArtistas; k++) {
                if (artistas[k].id == arreglo[i].idArtista) strcpy(nombreI, artistas[k].nombre);
                if (artistas[k].id == arreglo[j].idArtista) strcpy(nombreJ, artistas[k].nombre);
            }
            
            if (strcmp(nombreI, nombreJ) > 0) {
                Presentacion aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }
}
void MostrarUnaPresentacion(Presentacion p, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    char nombreArt[50] = "No Encontrado";
    char nombreEsc[50] = "No Encontrado";
    
    for(int i = 0; i < validosArtistas; i++) {
        if(artistas[i].id == p.idArtista) {
            strcpy(nombreArt, artistas[i].nombre);
            break;
        }
    }
    for(int i = 0; i < validosEscenarios; i++) {
        if(escenarios[i].id == p.idEscenario) {
            strcpy(nombreEsc, escenarios[i].nombre);
            break;
        }
    }
    printf("ID: %d | Artista: %s | Escenario: %s | Horario: %02d:%02d | Duracion: %02d:%02d\n", 
           p.id, nombreArt, nombreEsc, p.horario.hora, p.horario.minutos, p.duracion.horas, p.duracion.minutos);
}
void MostrarPresentacion(Presentacion arreglo[], int validos, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    printf("%-5s | %-12s | %-20s | %-20s\n", "ID", "ID Artista", "Artista", "Escenario");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < validos; i++) {
        char nombreArtista[50] = "No encontrado";
        for (int j = 0; j < validosArtistas; j++) {
            if (artistas[j].id == arreglo[i].idArtista) {
                strcpy(nombreArtista, artistas[j].nombre);
                break;
            }
        }

        char nombreEscenario[50] = "No encontrado";
        for (int k = 0; k < validosEscenarios; k++) {
            if (escenarios[k].id == arreglo[i].idEscenario) {
                strcpy(nombreEscenario, escenarios[k].nombre);
                break;
            }
        }

        printf("%-5d | %-12d | %-20s | %-20s\n", arreglo[i].id, arreglo[i].idArtista, nombreArtista, nombreEscenario);
    }
}
void MostrarPresentacionesPorArtista(Presentacion arreglo[], int validos, int idArtista, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    for(int i = 0; i < validos; i++) {
        if(arreglo[i].idArtista == idArtista) {
            MostrarUnaPresentacion(arreglo[i], artistas, validosArtistas, escenarios, validosEscenarios);
        }
    }
}
void MostrarPresentacionesPorEscenario(Presentacion arreglo[], int validos, int idEscenario, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
    for(int i = 0; i < validos; i++) {
        if(arreglo[i].idEscenario == idEscenario) {
            MostrarUnaPresentacion(arreglo[i], artistas, validosArtistas, escenarios, validosEscenarios);
        }
    }
}
void ExportarPresentacionesATexto(Presentacion arreglo[], int validos, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios, char nombreArchivo[]) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo != NULL) {
        for (int i = 0; i < validos; i++) {
            char nombreArt[50] = "No Encontrado";
            char nombreEsc[50] = "No Encontrado";
            for(int k = 0; k < validosArtistas; k++) {
                if(artistas[k].id == arreglo[i].idArtista) strcpy(nombreArt, artistas[k].nombre);
            }
            for(int k = 0; k < validosEscenarios; k++) {
                if(escenarios[k].id == arreglo[i].idEscenario) strcpy(nombreEsc, escenarios[k].nombre);
            }
            fprintf(archivo, "ID: %d | Artista: %s | Escenario: %s | Horario: %02d:%02d | Duracion: %02d:%02d\n",
                    arreglo[i].id, nombreArt, nombreEsc, arreglo[i].horario.hora, arreglo[i].horario.minutos, arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
        }
        fclose(archivo);
    }
}
void menuPresentaciones(Presentacion presentaciones[], int *validosPresentaciones, int dimension, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios) {
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
        printf("+ 5-Exportar a Texto           |\n");
        printf("+==============================+\n");
        printf("+ 0-Volver                     |\n");
        printf("+==============================+\n");
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
                OrdenaPresentacion(presentaciones, *validosPresentaciones, artistas, validosArtistas);
                MostrarPresentacion(presentaciones, *validosPresentaciones, artistas, validosArtistas, escenarios, validosEscenarios);
                system("pause");
                break;
            case 5:
                system("cls");
                ExportarPresentacionesATexto(presentaciones, *validosPresentaciones, artistas, validosArtistas, escenarios, validosEscenarios, "Presentaciones.txt");
                printf("Archivo generado\n");
                system("pause");
                break;
            case 0:
                system("cls");
            default:
                break;
        }
    } while (opcion != 0);
}