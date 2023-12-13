#ifndef OPERACIONESESTRUCTURAS_H
#define OPERACIONESESTRUCTURAS_H
#include "tiposDatos.h"
#include "otrasFunciones.h"
#include <stdio.h>
#include <stdlib.h>
// Definición de variables globales para contar los IDs
int idPrestamo = 1000;
int idDevolucion = 10000;
int idLibro = 1;
int idUsuario = 100;
int generarIdPrestamo()
{
    return idPrestamo++;
}
int generarIdDevolucion()
{
    return idDevolucion++;
}
int generarIdLibro()
{
    return idLibro++;
}
int generarIdUsuario()
{
    return idUsuario++;
}
void agregarArista(Nodo *nodo, Arista *nuevaArista)
{
    if (nodo->aristas == NULL)
    {
        nodo->aristas = (ListaAristas *)malloc(sizeof(ListaAristas));
        nodo->aristas->primera = nuevaArista;
    }
    else
    {
        nuevaArista->siguiente = nodo->aristas->primera;
        nodo->aristas->primera = nuevaArista;
    }
}
void agregarPrestamo(Nodo *libro, Nodo *usuario, Prestamo prestamo)
{
    if (libro->stock > 0)
    {
        Arista *nuevaArista = (Arista *)malloc(sizeof(Arista));
        nuevaArista->data.prestamo = prestamo;
        nuevaArista->tipo = 0;
        nuevaArista->siguiente = NULL;
        // Agregar arista al usuario
        agregarArista(usuario, nuevaArista);
        // Crear una nueva arista para el libro (para evitar compartir aristas entre nodos)
        Arista *nuevaAristaLibro = (Arista *)malloc(sizeof(Arista));
        nuevaAristaLibro->data.prestamo = prestamo;
        nuevaAristaLibro->tipo = 0;
        nuevaAristaLibro->siguiente = NULL;
        // Agregar arista al libro
        agregarArista(libro, nuevaAristaLibro);
        libro->stock--;
        printf("Pr%cstamo registrado con %cxito. Stock actualizado.\n", 130, 130);
    }
    else
    {
        printf("Error: No hay libros disponibles para pr%cstamo.\n", 130);
    }
}
void imprimirAristas(Nodo *nodo)
{
    printf("Aristas del nodo %d [ %s ]", nodo->id, nodo->nombre);
    if (nodo->tipo == LIBRO)
    {
        printf(" - Stock: %d", nodo->stock);
    }
    printf(" - Tipo: %s:\n", (nodo->tipo == LIBRO) ? "Libro" : "Usuario");
    if (nodo->aristas != NULL)
    {
        Arista *actual = nodo->aristas->primera;
        while (actual != NULL)
        {
            if (actual->tipo == 0)
            {
                printf("  Pr%cstamo ID: %d, Libro ID: %d, Usuario ID: %d\n", 130,
                       actual->data.prestamo.id, actual->data.prestamo.id_libro, actual->data.prestamo.id_usuario);
            }
            else
            {
                printf("  Devoluci%cn ID: %d, Pr%cstamo ID: %d, Libro ID: %d\n", 162,
                       actual->data.devolucion.id, 130, actual->data.devolucion.id_prestamo, actual->data.devolucion.id_libro);
            }
            actual = actual->siguiente;
        }
    }
    else
    {
        printf("Ninguna arista registrada.\n");
    }
    printf("\n");
}
void liberarAristas(Arista *aristas)
{
    while (aristas != NULL)
    {
        Arista *siguiente = aristas->siguiente;
        free(aristas);
        aristas = siguiente;
    }
}
void liberarNodo(Nodo *nodo)
{
    free(nodo->aristas);
    free(nodo);
}
void liberarLista(Nodo *lista)
{
    while (lista != NULL)
    {
        Nodo *siguiente = lista->siguiente;
        liberarAristas(lista->aristas);
        liberarNodo(lista);
        lista = siguiente;
    }
}
Nodo *ingresarNodoLibro()
{
    Nodo *libro = (Nodo *)malloc(sizeof(Nodo));
    if (libro == NULL)
    {
        perror("Error al asignar memoria para el libro");
        exit(EXIT_FAILURE);
    }
    libro->id = generarIdLibro();
    libro->nombre = leerCadena("Ingrese el titulo del libro: ");
    libro->stock = leerNum("Ingrese el stock del libro: ");
    libro->tipo = LIBRO;
    libro->aristas = NULL;
    libro->siguiente = NULL;
    printf("Libro registrado exitosamente.");
    return libro;
}
Nodo *ingresarNodoUsuario()
{
    Nodo *usuario = (Nodo *)malloc(sizeof(Nodo));
    if (usuario == NULL)
    {
        perror("Error al asignar memoria para el usuario");
        exit(EXIT_FAILURE);
    }
    usuario->id = generarIdUsuario();
    usuario->nombre = leerCadena("Ingrese el nombre del usuario: ");
    usuario->tipo = USUARIO;
    usuario->aristas = NULL;
    usuario->siguiente = NULL;
    return usuario;
}
void realizarPrestamo(Nodo *listaLibros, Nodo *listaUsuarios)
{
    int idLibro, idUsuario;
    idLibro = leerNum("Ingrese el ID del libro a prestar: ");
    Nodo *libro = listaLibros;
    while (libro != NULL)
    {
        if (libro->id == idLibro && libro->stock > 0)
        {
            break;
        }
        libro = libro->siguiente;
    }
    if (libro == NULL || libro->stock <= 0)
    {
        printf("Error: No se encontr%c el libro o no hay stock disponible.\n", 162);
        return;
    }

    idUsuario = leerNum("Ingrese el ID del usuario: ");
    Nodo *usuario = listaUsuarios;
    while (usuario != NULL)
    {
        if (usuario->id == idUsuario)
        {
            break;
        }
        usuario = usuario->siguiente;
    }
    if (usuario == NULL)
    {
        printf("Error: No se encontr%c el usuario.\n", 162);
        return;
    }
    Prestamo prestamo;
    // Solicitar información del pr%cstamo al usuario
    prestamo.id_libro = libro->id;
    prestamo.id_usuario = usuario->id;
    prestamo.id = generarIdPrestamo();
    agregarPrestamo(libro, usuario, prestamo);
}
void agregarDevolucion(Nodo *usuario, Nodo *libro)
{
    // Verificar si el usuario tiene un préstamo correspondiente
    if (usuario->aristas != NULL)
    {
        Arista *prestamoUsuario = usuario->aristas->primera;
        Arista *prevPrestamoUsuario = NULL;
        while (prestamoUsuario != NULL)
        {
            if (prestamoUsuario->tipo == 0 && prestamoUsuario->data.prestamo.id_libro == libro->id)
            {
                // Usuario tiene un préstamo correspondiente al libro
                // Crear una nueva arista para la devolución del usuario
                Arista *nuevaAristaUsuario = (Arista *)malloc(sizeof(Arista));
                nuevaAristaUsuario->data.devolucion.id = generarIdDevolucion();
                nuevaAristaUsuario->data.devolucion.id_prestamo = prestamoUsuario->data.prestamo.id;
                nuevaAristaUsuario->data.devolucion.id_libro = libro->id;
                nuevaAristaUsuario->tipo = 1;
                nuevaAristaUsuario->siguiente = NULL;
                // Agregar arista al usuario
                agregarArista(usuario, nuevaAristaUsuario);
                // Eliminar la arista de préstamo del usuario
                if (prevPrestamoUsuario == NULL)
                {
                    // La arista de préstamo es la primera en la lista
                    usuario->aristas->primera = prestamoUsuario->siguiente;
                }
                else
                {
                    prevPrestamoUsuario->siguiente = prestamoUsuario->siguiente;
                }

                // Liberar la memoria de la arista de préstamo
                free(prestamoUsuario);
                // Crear una nueva arista para la devolución del libro
                Arista *nuevaAristaLibro = (Arista *)malloc(sizeof(Arista));
                nuevaAristaLibro->data.devolucion = nuevaAristaUsuario->data.devolucion;
                nuevaAristaLibro->tipo = 1;
                nuevaAristaLibro->siguiente = NULL;
                // Agregar arista al libro
                agregarArista(libro, nuevaAristaLibro);
                libro->stock++;
                printf("Devoluci%cn registrada con %cxito. Stock actualizado.\n", 162, 130);
                return;
            }
            prevPrestamoUsuario = prestamoUsuario;
            prestamoUsuario = prestamoUsuario->siguiente;
        }
    }
    // Si llegamos aquí, el usuario no tiene un préstamo correspondiente al libro
    printf("Error: El usuario no tiene un préstamo correspondiente al libro.\n");
}
void realizarDevolucion(Nodo *listaUsuarios, Nodo *listaLibros)
{
    int idUsuario, idLibro;
    idUsuario = leerNum("Ingrese el ID del usuario : ");
    Nodo *usuario = listaUsuarios;
    while (usuario != NULL)
    {
        if (usuario->id == idUsuario)
        {
            break;
        }
        usuario = usuario->siguiente;
    }
    if (usuario == NULL)
    {
        printf("Error: No se encontr%c el usuario.\n", 162);
        return;
    }

    idLibro = leerNum("Ingrese el ID del libro a devolver: ");
    Nodo *libro = listaLibros;
    while (libro != NULL)
    {
        if (libro->id == idLibro)
        {
            break;
        }
        libro = libro->siguiente;
    }
    if (libro == NULL)
    {
        printf("Error: No se encontr%c el libro.\n", 162);
        return;
    }
    agregarDevolucion(usuario, libro);
}
#endif