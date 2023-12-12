#include <stdio.h>
#include <stdlib.h>
#include "busquedaOrdenamiento.h"
#include "tiposDatos.h"
#include "OperacionesEstructuras.h"
// Definición de variables globales para contar los IDs
int main()
{
    //system("cls");
    Nodo *listaLibros = NULL;
    Nodo *listaUsuarios = NULL;
    int opcion;
    char busqueda[100];
    do
    {
        printf("\n--- Men%c ---\n",163);
        printf("1. Ingresar libro\n");
        printf("2. Ingresar usuario\n");
        printf("3. Realizar pr%cstamo\n",130);
        printf("4. Realizar devoluci%cn\n",162);
        printf("5. Imprimir aristas\n");
        printf("6. Ordenar usuarios por nombre\n");
        printf("7. Ordenar libros por titulo\n");
        printf("8. Buscar usuario por nombre\n");
        printf("9. Buscar libro por titulo\n");
        printf("0. Salir\n");
        printf("Ingrese su opci%cn: ",162);
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            // Ingresar libro
            {
                Nodo *libro = ingresarNodoLibro();
                libro->siguiente = listaLibros;
                listaLibros = libro;
            }
            break;
        case 2:
            // Ingresar usuario
            {
                Nodo *usuario = ingresarNodoUsuario();
                usuario->siguiente = listaUsuarios;
                listaUsuarios = usuario;
            }
            break;
        case 3:
            // Realizar pr%cstamo
            realizarPrestamo(listaLibros, listaUsuarios);
            break;
        case 4:
            // Realizar devolución
            realizarDevolucion(listaUsuarios, listaLibros);
            break;
        case 5:
            // Imprimir aristas
            {
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
            mergeSort(&listaUsuarios);
            break;
        case 7:
            mergeSort(&listaLibros);
            break;
        case 8:
            mergeSort(&listaUsuarios);
            realizarBusqueda(listaUsuarios);
            break;
        case 9:
            mergeSort(&listaLibros);
            realizarBusqueda(listaLibros);
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