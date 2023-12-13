#include <stdio.h>
#include <stdlib.h>
#include "OperacionesEstructuras.h"
#include "tiposDatos.h"
#include "otrasFunciones.h"
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
// Función de comparación para ordenar los NodoB por título
int compararNodos(const void *a, const void *b)
{
    Nodo *NodoA = *(Nodo **)a;
    Nodo *NodoB = *(Nodo **)b;
    return strcmp(NodoA->nombre, NodoB->nombre);
}

// Función para mezclar dos listas ordenadas
Nodo *mergeListas(Nodo *listaIzquierda, Nodo *listaDerecha)
{
    if (listaIzquierda == NULL)
        return listaDerecha;
    if (listaDerecha == NULL)
        return listaIzquierda;

    Nodo *resultado = NULL;

    if (compararNodos(&listaIzquierda, &listaDerecha) <= 0)
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
// Función para ordenar la lista usando Merge Sort
void mergeSort(Nodo **lista)
{
    if (*lista == NULL || (*lista)->siguiente == NULL)
    {
        return; // La lista ya está ordenada o vacía
    }

    Nodo *listaIzquierda = NULL;
    Nodo *listaDerecha = NULL;
    splitLista(*lista, &listaIzquierda, &listaDerecha);

    mergeSort(&listaIzquierda);
    mergeSort(&listaDerecha);

    *lista = mergeListas(listaIzquierda, listaDerecha);
}

Nodo *busquedaBinaria(Nodo *cabeza, const char *valorBuscado)
{
    Nodo *inicio = cabeza;
    Nodo *fin = NULL;

    while (inicio != fin)
    {
        // Encontrar el punto medio
        Nodo *medio = inicio;
        Nodo *rapido = inicio->siguiente;
        while (rapido != fin)
        {
            rapido = rapido->siguiente;
            if (rapido != fin)
            {
                medio = medio->siguiente;
                rapido = rapido->siguiente;
            }
        }

        // Verificar si el valor buscado está en el medio
        if (strcmp(medio->nombre, valorBuscado) == 0)
        {
            return medio; // Se encontró el valor, devuelve el puntero al nodo
        }
        else if (strcmp(medio->nombre, valorBuscado) < 0)
        {
            inicio = medio->siguiente;
        }
        else
        {
            fin = medio;
        }
    }

    return NULL; // No se encontró el valor, devuelve NULL
}

void realizarBusqueda(Nodo *lista)
{
    char *nombreBuscado;
    nombreBuscado = leerCadena("Ingrese el nombre a buscar: ");

    // Llamar a la función de búsqueda binaria
    Nodo *resultado = busquedaBinaria(lista, nombreBuscado);

    // Verificar si se encontró resultado
    if (resultado != NULL)
    {
        imprimirAristas(resultado);
        /*if (resultado->tipo == USUARIO)
        {
            printf("Usuario encontrado:\n");

            //printf("ID    : %d\n", resultado->id);
            //printf("Nombre: %s\n", resultado->nombre);
        }
        else
        {
            printf("Libro encontrado:\n");
            printf("ID    : %d\n", resultado->id);
            printf("Titulo: %s\n", resultado->nombre);
            printf("Stock : %d\n", resultado->stock);
        }*/
    }
    else
    {
        printf("Busqueda sin resultados.\n");
    }
}