#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "artistas.h"
#include "escenarios.h"
#include "presentaciones.h"
#define DIM 100

void menuArtistas(Artista artistas[], int *validosArtistas, int dimension);
void menuEscenarios(Escenario escenarios[], int *validosEscenarios, int dimension);
void menuPresentaciones(Presentacion presentaciones[], int *validosPresentaciones, int dimension, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios);
void menuusuarionormal(Presentacion presentaciones[], int validosPresentaciones, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios);
void menuadmin(Presentacion presentaciones[], int *validosPresentaciones, Artista artistas[], int *validosArtistas, Escenario escenarios[], int *validosEscenarios);

int main()
{
    setlocale(LC_ALL, "");
    Artista artistas[DIM];
    Escenario escenarios[DIM];
    Presentacion presentaciones[DIM];
    
    int validosArtistas = LeerArtistasDesdeArchivo(artistas, DIM);
    int validosEscenarios = LeerEscenariosDesdeArchivo(escenarios, DIM);
    int validosPresentaciones = LeerPresentacionesDesdeArchivo(presentaciones, DIM);
    int opcionusuario;
    char contrasenia[20];
    
    do
    {
        printf("+================================+\n");
        printf("| 1 Usuario General              |\n");
        printf("+================================+\n");
        printf("| 2 Panel de Administrador       |\n");
        printf("+================================+\n");
        printf("| 0 Salir                        |\n");
        printf("+================================+\n");
        printf("Seleccione una opcion\n");
        scanf("%d", &opcionusuario);
        
        switch(opcionusuario)
        {
            case 1:
                system("cls");
                menuusuarionormal(presentaciones, validosPresentaciones, artistas, validosArtistas, escenarios, validosEscenarios);
                break;
            case 2:
                system("cls");
                printf("Ingrese la contrasenia de admin\n");
                scanf("%s", contrasenia);
                if(strcmp(contrasenia, "admin") == 0){
                    system("cls");
                    menuadmin(presentaciones, &validosPresentaciones, artistas, &validosArtistas, escenarios, &validosEscenarios);
                }else {
                    printf("Contrasenia incorrecta\n");
                }
                break;
            case 0:
                system("cls");
                printf("Saliendo\n");
                break;
            default:
                printf("Seleccione una opcion valida \n");
                break;
        }   
    } while(opcionusuario != 0);
    
    return 0;
}

void menuusuarionormal(Presentacion presentaciones[], int validosPresentaciones, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios)
{
    int opcion;
    do
    {
        printf("+=========================================+\n");
        printf("|              MENU USUARIO               |\n");
        printf("+=========================================+\n");
        printf("| 1 Cronograma Completo                   |\n");
        printf("+=========================================+\n");
        printf("| 2 Presentaciones por Artista            |\n");
        printf("+=========================================+\n");
        printf("| 3 Presentaciones por Escenario          |\n");
        printf("+=========================================+\n");
        printf("| 4 Ver Listado Completo de Artistas      |\n");
        printf("+=========================================+\n");
        printf("| 5 Ver Listado Completo de Escenarios    |\n");
        printf("+=========================================+\n");
        printf("| 0 Salir al Menu Principal               |\n");
        printf("+=========================================+\n");
        printf("Seleccione una opcion\n");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                system("cls");
                OrdenaPresentacion(presentaciones, validosPresentaciones, artistas, validosArtistas);
                MostrarPresentacion(presentaciones, validosPresentaciones, artistas, validosArtistas, escenarios, validosEscenarios);
                break;
            case 2:
                system("cls");
                int idArtista;
                printf("Ingrese el ID del artista: ");
                scanf("%d", &idArtista);
                MostrarPresentacionesPorArtista(presentaciones, validosPresentaciones, idArtista, artistas, validosArtistas, escenarios, validosEscenarios);
                break;
            case 3:
                system("cls");
                int idEscenario;
                printf("Ingrese el ID del escenario: ");
                scanf("%d", &idEscenario);
                MostrarPresentacionesPorEscenario(presentaciones, validosPresentaciones, idEscenario, artistas, validosArtistas, escenarios, validosEscenarios);
                break;
            case 4:
                system("cls");
                OrdenarArtista(artistas, validosArtistas);
                MostrarArtista(artistas, validosArtistas);
                break;
            case 5:
                system("cls");
                OrdenarEscenario(escenarios, validosEscenarios);
                MostrarEscenario(escenarios, validosEscenarios);
                break;
            case 0:
                system("cls");
                printf("Volviendo al menu principal...\n");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while(opcion != 0);
}

void menuadmin(Presentacion presentaciones[], int *validosPresentaciones, Artista artistas[], int *validosArtistas, Escenario escenarios[], int *validosEscenarios)
{
    int opcion;
    do
    {
        printf("+=========================================+\n");
        printf("|            PANEL ADMINISTRADOR          |\n");
        printf("+=========================================+\n");
        printf("| 1 - Gestionar Artistas                  |\n");
        printf("+=========================================+\n");
        printf("| 2 - Gestionar Escenarios                |\n");
        printf("+=========================================+\n");
        printf("| 3 - Gestionar Presentaciones            |\n");
        printf("+=========================================+\n");
        printf("| 0 - Menu Principal                      |\n");
        printf("+=========================================+\n");
        printf("Seleccione una opcion\n");
        scanf("%d", &opcion);
        
        switch(opcion)
        {
            case 1:
                system("cls");
                menuArtistas(artistas, validosArtistas, DIM);
                break;
            case 2:
                system("cls");
                menuEscenarios(escenarios, validosEscenarios, DIM);
                break;
            case 3:
                system("cls");
                menuPresentaciones(presentaciones, validosPresentaciones, DIM, artistas, *validosArtistas, escenarios, *validosEscenarios);
                break;
            case 0:
                system("cls");
                printf("Volviendo al menu principal\n");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while(opcion != 0);
}