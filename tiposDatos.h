#ifndef TIPOSDATOS_H
#define TIPOSDATOS_H

typedef enum {
    LIBRO,
    USUARIO
} TipoNodo;

typedef struct Prestamo {
    int id;
    int id_libro;
    int id_usuario;
} Prestamo;

typedef struct Devolucion {
    int id;
    int id_prestamo;
    int id_libro;
} Devolucion;

typedef struct Nodo {
    int id;
    char nombre[100];
    TipoNodo tipo;
    int stock;
    struct ListaAristas *aristas;
    struct Nodo *siguiente;
} Nodo;

typedef struct Arista {
    union {
        Prestamo prestamo;
        Devolucion devolucion;
    } data;
    int tipo;
    struct Arista *siguiente;
} Arista;

typedef struct ListaAristas {
    Arista *primera;
} ListaAristas;

#endif /* TIPOSDATOS_H */
