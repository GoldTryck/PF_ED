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
                Nodo *libro = ingresarNodoLibro();
                libro->siguiente = listaLibros;
                listaLibros = libro;
            }
            break;
        case 2:
            // Ingresar usuario
            {
                limpiarPantalla();
                Nodo *usuario = ingresarNodoUsuario();
                usuario->siguiente = listaUsuarios;
                listaUsuarios = usuario;
            }
            break;
        case 3:
            // Realizar pr%cstamo
            limpiarPantalla();
            realizarPrestamo(listaLibros, listaUsuarios);
            break;
        case 4:
            // Realizar devolución
            limpiarPantalla();
            realizarDevolucion(listaUsuarios, listaLibros);
            break;
        case 5:
            // Imprimir aristas
            {
                limpiarPantalla();
                Nodo *libro = listaLibros;
                while (libro != NULL)
                {
                    imprimirAristas(libro);
                    libro = libro->siguiente;
                }
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
            break;
        case 7:
            limpiarPantalla();
            mergeSort(&listaLibros);
            break;
        case 8:
            limpiarPantalla();
            mergeSort(&listaUsuarios);
            realizarBusqueda(listaUsuarios);
            break;
        case 9:
        limpiarPantalla();
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