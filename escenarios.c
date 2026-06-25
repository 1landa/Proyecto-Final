#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escenarios.h"

int LeerEscenariosDesdeArchivo(Escenario arreglo[], int dimension) {
    int validos = 0;
    FILE *archivo = fopen("escenarios.dat", "rb");
    if (archivo != NULL) {
        while (fread(&arreglo[validos], sizeof(Escenario), 1, archivo) == 1) {
            validos++;
        }
        fclose(archivo);
    }
    return validos;
}
void CambiaArchivoEscenarios(Escenario arreglo[], int validos) {
    FILE *archi = fopen("escenarios.dat", "wb");
    if (archi != NULL) {
        fwrite(arreglo, sizeof(Escenario), validos, archi);
        fclose(archi);
    } else {
        printf("Error al actualizar el archivo\n");
    }
}

int CargaEscenario(Escenario arreglo[], int validos, int dimension) {
    if (validos == dimension) {
        printf("Limite maximo\n");
        return validos;
    }
    int continuar;
    printf("Desea ingresar un escenario? 1 si 2 no\n");
    scanf("%d", &continuar);
    while (getchar() != '\n');
    if (continuar == 0) {
        return validos;
    }
    FILE *archivo = fopen("escenarios.dat", "ab");
    if (archivo != NULL) {
        Escenario nuevo;
        printf("Ingrese la ID del escenario nuevo: \n ");
        scanf("%d", &nuevo.id);
        while (getchar() != '\n');
        printf("Ingrese el nombre: ");
        fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
        nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
        fwrite(&nuevo, sizeof(Escenario), 1, archivo);
        fclose(archivo);
        arreglo[validos] = nuevo;       
        return CargaEscenario(arreglo, validos + 1, dimension);
    }
    return validos;
}
void OrdenarEscenario(Escenario arreglo[], int validos) {
    for (int i = 0; i < validos - 1; i++) {
        for (int j = 0; j < validos - i - 1; j++) {
            if (strcasecmp(arreglo[j].nombre, arreglo[j+1].nombre) > 0) {
                Escenario temp = arreglo[j];
                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = temp;
            }
        }
    }
}
void MostrarEscenario(Escenario arreglo[], int validos) {
    if (validos == 0) {
        printf("No hay escenarios para mostrar\n");
        return;
    }
    OrdenarEscenario(arreglo, validos);
    printf("Listado de escenarios\n");
    for (int i = 0; i < validos; i++) {
        printf("ID: %d\n", arreglo[i].id);
        printf("Nombre: %s\n", arreglo[i].nombre);
    }
}

int BuscarEscenarioPorId(Escenario arreglo[], int validos, int id) {
    for (int i = 0; i < validos; i++) {
        if (arreglo[i].id == id) {
            return i;
        }
    }
    return -1;
}
void ModificarEscenario(Escenario arreglo[], int validos) {
    int id;
    int pos;
    system("cls");
    printf("Ingrese el ID del escenario a modificar: \n ");
    scanf("%d", &id);
    while (getchar() != '\n');
    pos = BuscarEscenarioPorId(arreglo, validos, id);
    if (pos != -1) {
        system("cls");
        printf("Ingrese el nuevo nombre: ");
        fgets(arreglo[pos].nombre, sizeof(arreglo[pos].nombre), stdin);
        arreglo[pos].nombre[strcspn(arreglo[pos].nombre, "\n")] = '\0';
        CambiaArchivoEscenarios(arreglo, validos);
        system("cls");
        printf("El escenario modificado\n");
        CambiaArchivoEscenarios(escenarios, validos);
        
    } else {
        printf("Con ese ID no existe un escenario\n");
    }
}

int BajaEscenario(Escenario arreglo[], int validos) {
    int id;
    int pos;
    system("cls");
    printf("Ingrese el ID del escenario a eliminar \n");
    scanf("%d", &id);
    pos = BuscarEscenarioPorId(arreglo, validos, id);
    if (pos != -1) {
        for (int i = pos; i < validos - 1; i++) {
            arreglo[i] = arreglo[i + 1];
        }
        validos--;
        CambiaArchivoEscenarios(arreglo, validos);
        system("cls");
        printf("El escenario ha sido eliminado \n");
    } else {
        printf("Con ese ID no existe un escenario\n");
    }
    CambiaArchivoEscenarios(escenarios, validos);
    return validos;
}
void CambiaArchivoEscenarios(Escenario arreglo[], int validos){
    FILE *archi=fopen("escenarios.dat", "wb");
    if (archi !=NULL){
        fwrite(arreglo,sizeof(Escenario),validos,archi);
        fclose(archi);
    }else{
        printf("No se pudo abrir el archivo");
    }
}