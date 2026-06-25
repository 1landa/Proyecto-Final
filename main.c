#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artistas.h"
#include "escenarios.h"
#include "presentaciones.h"
#define DIM 100
int main()
{
    int opcion;
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
        printf("╔════════════════════════════════╗\n");
        printf("║ ① Usuario General              ║\n");
        printf("╠════════════════════════════════╣\n");
        printf("║ ② Panel de Administrado        ║\n");
        printf("╠════════════════════════════════╣\n");
        printf("║ ⓪ Salir                        ║\n");
        printf("╚════════════════════════════════╝\n");
        printf("Seleccione una opcion");
        scanf("%d", &opcionusuario);
        switch(opcionusuario)
        {
            case 1:
                menuusuarionormal(presentaciones, validosPresentaciones, artistas, validosArtistas, escenarios, validosEscenarios);
                break;
            case 2:
            printf("Ingrese la contrasenia de admin");
            scanf("%s", contrasenia);
            if(strcmp(contrasenia, "admin") == 0){

                menuadmin(presentaciones, &validosPresentaciones, artistas, &validosArtistas, escenarios, &validosEscenarios);
            }else {
                    printf("Contrasenia incorrecta\n");
                    printf("Regresando al menu principal        \n");
                }
                break;
            case 0:
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
        printf("╔═════════════════════════════════════════╗\n");
        printf("║ ① Mostrar Presentaciones                ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ ② Mostrar Presentaciones por Artista    ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ ③ Mostrar Presentaciones por Escenario  ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ ⓪ Menu Principal                        ║\n");
        printf("╚═════════════════════════════════════════╝\n");
        printf("Seleccione una opcion");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1:
                printf("\n»»» LISTADO DE PRESENTACIONES «««\n");
                OrdenaPresentacion(presentaciones, validosPresentaciones);
                MostrarPresentacion(presentaciones, validosPresentaciones);
                break;
            case 2:
                printf("\n»»»Ingrese el ID del artista«««");
                scanf("%d", &Identificacion);
            MostrarPresentacionesPorArtista(presentaciones, validosPresentaciones, Identificacion);
                break;
            case 3:
             printf("\n»»»Ingrese el ID del escenario«««");
        scanf("%d", &Identificacion);
            MostrarPresentacionesPorEscenario(presentaciones, validosPresentaciones, Identificacion);
                break;
            case 0:
                printf("n»»»Volviendo al menú principal«««\n");
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
        printf("╔═════════════════════════════════════════╗\n");
        printf("║ ① Agregar Presentacion                  ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ ② Modificar Presentacion                ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ ③ Eliminar Presentacion                 ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ ⓪ Menu Principal                        ║\n");
        printf("╚═════════════════════════════════════════╝\n");
        printf("Seleccione una opcion");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1:
                if(*validosPresentaciones < DIM)
                {
                    *validosPresentaciones =        CargaPresentacion(presentaciones, *validosPresentaciones, DIM);
                }
                else
                {
                    printf("Limite maximo\n");
                }
                break;
            case 2:
                ModificarPresentacion(presentaciones, *validosPresentaciones);
                break;
            case 3:
*validosPresentaciones = BajaPresentacion(presentaciones, *validosPresentaciones);
                break;
            case 0:
                printf("Volviendo al menu principal\n");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while(opcion != 0);
}