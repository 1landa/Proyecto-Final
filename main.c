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

    int validosArtistas = 0;
    int validosEscenarios = 0;
    int validosPresentaciones = 0;
    do
    {
        printf("╔══════════FESTIVAL════════════╗\n");
        printf("║① Gestionar Artistas          ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║② Gestionar Escenarios        ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║③ Gestionar Presentaciones    ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║④ Consultas (Listados)        ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║⑤ Exportar Datos              ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║⓪ Salir                       ║\n");
        printf("╚══════════════════════════════╝\n");
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
                printf("\n»»» Listado de artistas «««\n");
                MostrarArtista(artistas, validosArtistas);

                printf("\n»»» Listado de escenarios «««\n");
                MostrarEscenario(escenarios, validosEscenarios);

                printf("\n»»» Listado de presentaciones «««\n");
                MostrarPresentacion(presentaciones, validosPresentaciones);
                break;
            case 0:
                printf("\nSaliendo...\n");
                break;
            default:
printf("      \\ \\   / /\n");
printf("       \\ \\ / / \n");
printf("        \\ X /  \n");
printf("       / / \\ \\\n");
printf("      / /   \\ \\\n");
                break;
        }
    } while(opcion != 0);

    return 0;
}
