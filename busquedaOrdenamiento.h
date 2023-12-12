#include <stdio.h>
#include <stdlib.h>
#include "tiposDatos.h"
#include <string.h>
// Función para dividir la lista en dos mitades
void splitLista(Nodo *lista, Nodo **listaIzquierda, Nodo **listaDerecha)
{
    Nodo *rapido;
    Nodo *lento;
    if (lista == NULL || lista->siguiente == NULL)
    {
        *listaIzquierda = lista;
        *listaDerecha = NULL;
    }
    else
    {
        lento = lista;
        rapido = lista->siguiente;
        while (rapido != NULL)
        {
            rapido = rapido->siguiente;
            if (rapido != NULL)
            {
                lento = lento->siguiente;
                rapido = rapido->siguiente;
            }
        }

        *listaIzquierda = lista;
        *listaDerecha = lento->siguiente;
        lento->siguiente = NULL;
    }
}
// Función de comparación para ordenar los libros por título
int compararLibros(const void *a, const void *b)
{
    Nodo *libroA = *(Nodo **)a;
    Nodo *libroB = *(Nodo **)b;
    return strcmp(libroA->nombre, libroB->nombre);
}

// Función para mezclar dos listas ordenadas
Nodo *mergeListas(Nodo *listaIzquierda, Nodo *listaDerecha)
{
    if (listaIzquierda == NULL)
        return listaDerecha;
    if (listaDerecha == NULL)
        return listaIzquierda;

    Nodo *resultado = NULL;

    if (compararLibros(&listaIzquierda, &listaDerecha) <= 0)
    {
        resultado = listaIzquierda;
        resultado->siguiente = mergeListas(listaIzquierda->siguiente, listaDerecha);
    }
    else
    {
        resultado = listaDerecha;
        resultado->siguiente = mergeListas(listaIzquierda, listaDerecha->siguiente);
    }

    return resultado;
}
// Función para ordenar la lista de libros usando Merge Sort
void mergeSort(Nodo **listaLibros)
{
    if (*listaLibros == NULL || (*listaLibros)->siguiente == NULL)
    {
        return; // La lista ya está ordenada o vacía
    }

    Nodo *listaIzquierda = NULL;
    Nodo *listaDerecha = NULL;
    splitLista(*listaLibros, &listaIzquierda, &listaDerecha);

    mergeSort(&listaIzquierda);
    mergeSort(&listaDerecha);

    *listaLibros = mergeListas(listaIzquierda, listaDerecha);
}

Nodo *busquedaBinariaPorNombre(Nodo *listaLibros, char *nombreBuscado)
{
    Nodo *izquierda = listaLibros;
    Nodo *derecha = NULL;

    while (izquierda != NULL)
    {
        // Encontrar el final de la lista
        derecha = izquierda;
        while (derecha->siguiente != NULL)
        {
            derecha = derecha->siguiente;
        }

        Nodo *mitad = izquierda;
        int comparacion = strcmp(mitad->nombre, nombreBuscado);

        if (comparacion == 0)
        {
            return mitad; // Se encontró el libro con el nombre buscado
        }
        else if (comparacion > 0)
        {
            derecha = mitad;
        }
        else
        {
            izquierda = mitad->siguiente;
        }
    }

    return NULL; // No se encontró el libro con el nombre buscado
}

void realizarBusqueda(Nodo *listaLibros)
{
    char nombreBuscado[100];
    printf("Ingrese el nombre a buscar: ");
    scanf("%s", nombreBuscado);

    // Llamar a la función de búsqueda binaria por nombre
    Nodo *libroEncontrado = busquedaBinariaPorNombre(listaLibros, nombreBuscado);

    // Verificar si se encontró el libro
    if (libroEncontrado != NULL)
    {
        printf("Libro encontrado:\n");
        printf("ID: %d\n", libroEncontrado->id);
        printf("Nombre: %s\n", libroEncontrado->nombre);
    }
    else
    {
        printf("Libro no encontrado.\n");
    }
}