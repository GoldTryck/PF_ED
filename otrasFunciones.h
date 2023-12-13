#ifndef OTRASFUNCIONES_H
#define OTRASFUNCIONES_H
#define MAX_LEN 60
#define INI_SIZE 15
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// Función para limpiar la pantalla en sistemas POSIX (Linux, macOS)
void limpiarPantallaPOSIX() {
    printf("\033[2J\033[H");
}

// Función para limpiar la pantalla en sistemas Windows
void limpiarPantallaWindows() {
    system("cls");
}

// Función para limpiar la pantalla de manera portable
void limpiarPantalla() {
#if defined(_WIN32) || defined(_WIN64)
    limpiarPantallaWindows();
#else
    limpiarPantallaPOSIX();
#endif
}
char* leerCadena(char* mensaje) {
    char* chain = NULL;
    char c; 
    int i, size;
    while(chain == NULL) {
        i = 0;
        size = INI_SIZE;
        chain = (char*)calloc(1,sizeof(char) * size);
        printf("%s",mensaje);
        while(1){
            if( i == size - 1) {
                size += INI_SIZE;
                chain = (char*)realloc(chain,sizeof(char) * ( size));
            }
            if(i == MAX_LEN) {
                printf("Error: longitud maxima superada.\n");
                free(chain);
                chain = NULL;
                break;
            }
            chain[i] = (c = (char)getchar());
            if(i == 0 && (chain[0] == '\n' || chain[0] == 9 || chain[0] == 32)){
                printf("Error: No ingrese espacios en blanco al inicio de la cadena.\n");
                free(chain);
                chain = NULL;
                break;
            }
            chain[i] = toupper(chain[i]);
            if(chain[i] == 32) chain[i] = 95;
            if(c == '\n') {
                chain[i] = '\0';
                i++;
                break;
            }
            i ++;
        }
    }
    chain = (char*)realloc(chain,sizeof(char) * (i + 1));
    return chain;
}
int leerNum(char* mensaje) {

    int num;
    char* input = NULL;
    while (1) {
        input = leerCadena(mensaje);
        int i = 0;
        while (input[i] != '\0') {
            if (!isdigit(input[i])) {
                printf("Error: Debe ingresar un numero entero.\n");
                free(input);
                break;
            }
            if(i >= 9){
                printf("Error: Intente nuevamente.\n");
                free(input);
                break;
            }
            i++;
        }
        if (input[i] == '\0') {
            num = atoi(input);
            free(input);
            break;
        }
    }
    return num;
}
// Función para imprimir descripciones de las estructuras de datos y operaciones
void imprimirDescripcion() {
    printf(" _____________________________________________________________ \n");
    printf("|                    Estructuras de Datos                     |\n");
    printf("|_____________________________________________________________|\n");
    printf("| - TipoNodo:    Enumeracion que representa el tipo de nodo   |\n");
    printf("|                (LIBRO, USUARIO).                            |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Prestamo:    Estructura que representa un prestamo con    |\n");
    printf("|                campos (id, id_libro, id_usuario).           |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Devolucion:  Estructura que representa una devolucion     |\n");
    printf("|                con campos (id, id_prestamo, id_libro).      |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Nodo:        Estructura que representa un nodo con campos |\n");
    printf("|                (id, nombre, tipo, stock, aristas, siguiente)|\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Arista:      Estructura que representa una arista de grafo|\n");
    printf("|                (Prestamo o Devolucion), tipo y siguiente.   |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| -ListaAristas: Estructura que representa una lista de       |\n");
    printf("|                aristas con un puntero a la primera          |\n");
    printf("|                arista.                                      |\n");
    printf("|_____________________________________________________________|\n\n");

    printf(" _____________________________________________________________ \n");
    printf("|                       Operaciones                           |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Agregar Libro:      Funcion para agregar un nuevo libro   |\n");
    printf("|                       a la lista de libros.                 |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Agregar Usuario:    Funcion para agregar un nuevo usuario |\n");
    printf("|                       a la lista de usuarios.               |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Agregar Prestamo:   Funcion para agregar un prestamo      |\n");
    printf("|                       entre un libro y un usuario.          |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Agregar Devolucion: Funcion para agregar una devolucion   |\n");
    printf("|                       de un libro por parte de un usuario.  |\n");
    printf("|_____________________________________________________________|\n\n");

    printf(" _____________________________________________________________ \n");
    printf("|                        Algoritmos                           |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| - Merge Sort:       Algoritmo de ordenamiento utilizado para|\n");
    printf("|                     ordenar la lista de libros.             |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("|                     Algoritmo de busqueda utilizado para    |\n");
    printf("| - Busqueda Binaria: buscar un libro/usuario por nombre en   |\n");
    printf("|                     en una lista ordenada.                  |\n");
    printf("|_____________________________________________________________|\n");

    while(leerNum("Presione 0  para volver al menu principal...") != 0);
    limpiarPantalla();
}


void imprimirMenu(){
    printf(" _____________________________________________________________ \n");
    printf("|                       Men%c principal                        |\n",163);
    printf("|_____________________________________________________________|\n");
    printf("| Teclee la opci%cn de la acci%cn que desee realizar y pulse    |\n",162,162);
    printf("| la tecla enter para ejecutar.                               |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| 1. Ingresar libro           6. Ordenar usuarios por nombre  |\n");
    printf("| 2. Ingresar usuario         7. Ordenar libros por titulo    |\n");
    printf("| 3. Realizar pr%cstamo        8. Buscar usuario por nombre    |\n",130);
    printf("| 4. Realizar devoluci%cn      9. Buscar libro por titulo      |\n",162);
    printf("| 5. Imprimir aristas        10. Ayuda/Informaci%cn            |\n",162);
    printf("|                             0. Salir                        |\n");
    printf("|_____________________________________________________________|\n");
}

#endif


