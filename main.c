#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "artistas.h"
#include "escenarios.h"
#include "presentaciones.h"
#define DIM 100
int main()
{
    setlocale(LC_ALL, "");
    Artista artistas[DIM];
    Escenario escenarios[DIM];
    Presentacion presentaciones[DIM];
    void menuusuarionormal(Presentacion presentaciones[], int validosPresentaciones, Artista artistas[], int validosArtistas, Escenario escenarios[], int validosEscenarios);
void menuadmin(Presentacion presentaciones[], int *validosPresentaciones, Artista artistas[], int *validosArtistas, Escenario escenarios[], int *validosEscenarios);
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
    int Identificacion;
    int opcion;
    do
    {
        printf("+=========================================+\n");
        printf("| 1 Mostrar Presentaciones                |\n");
        printf("+=========================================+\n");
        printf("| 2 Mostrar Presentaciones por Artista    |\n");
        printf("+=========================================+\n");
        printf("| 3 Mostrar Presentaciones por Escenario  |\n");
        printf("+=========================================+\n");
        printf("| 0 Menu Principal                        |\n");
        printf("+=========================================+\n");
        printf("Seleccione una opcion\n");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1:
            system("cls");
                printf("\n >>LISTADO DE PRESENTACIONES <<\n");
                OrdenaPresentacion(presentaciones, validosPresentaciones);
                MostrarPresentacion(presentaciones, validosPresentaciones);
                break;
            case 2:
            system("cls");
                printf("\n>>Ingrese el ID del artista<<");
                scanf("%d", &Identificacion);
            MostrarPresentacionesPorArtista(presentaciones, validosPresentaciones, Identificacion);
                break;
            case 3:
            system("cls");
             printf("\n>>Ingrese el ID del escenario<<");
        scanf("%d", &Identificacion);
            MostrarPresentacionesPorEscenario(presentaciones, validosPresentaciones, Identificacion);
                break;
            case 0:
            system("cls");
                printf("n>>Volviendo al menú principal<<\n");
                break;
            default:
            printf("Opcion invalida\n");
                break;
        }
    } while(opcion != 0);
}
void menuadmin(Presentacion presentaciones[], int *validosPresentaciones, Artista artistas[], int *validosArtistas, Escenario escenarios[], int *validosEscenarios){
    int opcion;
    do
    {
        printf("+=========================================+\n");
        printf("| 1 Agregar Presentacion                  |\n");
        printf("+=========================================+\n");
        printf("| 2 Modificar Presentacion                |\n");
        printf("+=========================================+\n");
        printf("| 3 Eliminar Presentacion                 |\n");
        printf("+=========================================+\n");
        printf("| 0 Menu Principal                        |\n");
        printf("+=========================================+\n");
        printf("Seleccione una opcion\n");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1:
                system("cls");
                *validosPresentaciones = CargaPresentacion(presentaciones, *validosPresentaciones, DIM);

                break;
            case 2:
            system("cls");
                ModificarPresentacion(presentaciones, *validosPresentaciones);
                break;
            case 3:
            system("cls");
                *validosPresentaciones = BajaPresentacion(presentaciones, *validosPresentaciones);
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