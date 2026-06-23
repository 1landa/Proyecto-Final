#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artistas.h"
#include "escenarios.h"
#include "presentaciones.h"

#define DIM 100gcc main.c artistas.c escenarios.c presentaciones.c -o programa

int main()
{
    int opcion;
    Artista artistas[DIM];
    Escenario escenarios[DIM];
    Presentacion presentaciones[DIM];

    int validosArtistas = 0;
    int validosEscenarios = 0;
    int validosPresentaciones = 0;

    do
    {
        printf("\n===== FESTIVAL =====\n");
        printf("1 - Gestionar Artistas\n");
        printf("2 - Gestionar Escenarios\n");
        printf("3 - Gestionar Presentaciones\n");
        printf("4 - Consultas (Listados)\n");
        printf("5 - Exportar Datos\n");
        printf("0 - Salir\n");
        printf("====================\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                validosArtistas = CargaArtista(artistas, validosArtistas, DIM);
                break;

            case 2:
                validosEscenarios = CargaEscenario(escenarios, validosEscenarios, DIM);
                break;

            case 3:
                validosPresentaciones = CargaPresentacion(presentaciones, validosPresentaciones, DIM);
                break;

            case 4:
                printf("\n--- LISTADO DE ARTISTAS ---\n");
                MostrarArtista(artistas, validosArtistas);

                printf("\n--- LISTADO DE ESCENARIOS ---\n");
                MostrarEscenario(escenarios, validosEscenarios);

                printf("\n--- LISTADO DE PRESENTACIONES ---\n");
                MostrarPresentacion(presentaciones, validosPresentaciones);
                break;

            case 5:
                printf("\nExportacion pendiente...\n");
                // Aqui ira la llamada a la funcion para exportar a .txt
                break;

            case 0:
                printf("\nSaliendo del sistema. ¡Hasta luego!\n");
                break;

            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
                break;
        }
    } while(opcion != 0);

    return 0;
}
