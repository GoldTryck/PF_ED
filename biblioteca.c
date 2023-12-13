#include <stdio.h>
#include <stdlib.h>
#include "busquedaOrdenamiento.h"
#include "tiposDatos.h"
#include "OperacionesEstructuras.h"
#include "otrasFunciones.h"
// Definición de variables globales para contar los IDs
int main()
{
    limpiarPantalla();
    Nodo *listaLibros = NULL;
    Nodo *listaUsuarios = NULL;
    int opcion;
    char busqueda[100];
    do
    {
        printf("\n");
        imprimirMenu();
        opcion = leerNum("> ");
        switch (opcion)
        {
        case 1:
            // Ingresar libro
            {
                limpiarPantalla();
                printf(" _____________________________________________________________ \n");
                printf("|                        Registro de libros                   |\n");
                printf("|_____________________________________________________________|\n\n");
                mergeSort(&listaLibros);
                Nodo *libro = ingresarNodoLibro(listaLibros);
                libro->siguiente = listaLibros;
                listaLibros = libro;
            }
            break;
        case 2:
            // Ingresar usuario
            {
                limpiarPantalla();
                printf(" _____________________________________________________________ \n");
                printf("|                      Registro de usuarios                   |\n");
                printf("|_____________________________________________________________|\n\n");
                mergeSort(&listaUsuarios);
                Nodo *usuario = ingresarNodoUsuario(listaUsuarios);
                usuario->siguiente = listaUsuarios;
                listaUsuarios = usuario;
                    
            }
            break;
        case 3:
            // Realizar pr%cstamo
            limpiarPantalla();
            printf(" _____________________________________________________________ \n");
            printf("|                        Prestamo de libros                   |\n");
            printf("|_____________________________________________________________|\n\n");
            realizarPrestamo(listaLibros, listaUsuarios);
            break;
        case 4:
            // Realizar devolución
            limpiarPantalla();
            printf(" _____________________________________________________________ \n");
            printf("|                     Devolucion de libros                    |\n");
            printf("|_____________________________________________________________|\n\n");
            realizarDevolucion(listaUsuarios, listaLibros);
            break;
        case 5:
            // Imprimir aristas
            {
                limpiarPantalla();
                printf(" _____________________________________________________________ \n");
                printf("|              Prestamos/Devoluciones Libros                  |\n");
                printf("|_____________________________________________________________|\n\n");
                Nodo *libro = listaLibros;
                while (libro != NULL)
                {
                    imprimirAristas(libro);
                    libro = libro->siguiente;
                }
                printf(" _____________________________________________________________ \n");
                printf("|                    Prestamos por Usuario                    |\n");
                printf("|_____________________________________________________________|\n\n");
                Nodo *usuario = listaUsuarios;
                while (usuario != NULL)
                {
                    imprimirAristas(usuario);
                    usuario = usuario->siguiente;
                }
            }
            break;
        case 6:
            //ordenar usuarios
            limpiarPantalla();
            mergeSort(&listaUsuarios);
            printf("Listado de Usuaruios ordenado correctamente.\n\n");
            break;
        case 7:
            limpiarPantalla();
            mergeSort(&listaLibros);
            printf("Listado de Libros ordenado correctamente.\n\n");
            break;
        case 8:
            limpiarPantalla();
            printf(" _____________________________________________________________ \n");
            printf("|                    Busqueda de Usuarios                     |\n");
            printf("|_____________________________________________________________|\n\n");
            mergeSort(&listaUsuarios);
            realizarBusqueda(listaUsuarios);
            break;
        case 9:
            limpiarPantalla();
            printf(" _____________________________________________________________ \n");
            printf("|                    Busqueda de Libros                       |\n");
            printf("|_____________________________________________________________|\n\n");
            mergeSort(&listaLibros);
            realizarBusqueda(listaLibros);
            break;
        case 10:
            limpiarPantalla();
            imprimirDescripcion();
            break;
        case 0:
            // Salir
            break;
        default:
            printf("Opci%cn no válida. Intente de nuevo.\n",162);
        }
    } while (opcion != 0);
    liberarLista(listaLibros);
    liberarLista(listaUsuarios);
    return 0;
}