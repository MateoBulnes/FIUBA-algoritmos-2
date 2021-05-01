#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>


typedef int (*heap_comparador)(void*, void*);

typedef void (*heap_destructor)(void*);

typedef struct heap{
	void** vector;
	size_t tope;
	heap_comparador comparador;
	heap_destructor destructor;
} heap_t;

/*
*PRE: Recibe un comparador y un destructor validos
*POST: Crea el heap y reserva la memoria necesaria para el mismo. Devuelve un puntero al heap inicializado
*/
heap_t* crear_heap(heap_comparador comparador, heap_destructor destructor);
/*
*PRE: Recibe una posicion del heap
*POST: Devuelve la posicion del padre
*/
size_t pos_padre(size_t n);
/*
*PRE: Recibe una posicion del heap
*POST: Devuelve la posicion del hijo derecho
*/
size_t pos_hijo_derecha(size_t n);
/*
*PRE: Recibe una posicion del heap
*POST: Devuelve la posicion del hijo izquierdo
*/
size_t pos_hijo_izquierda(size_t n);
/*
*PRE: Recibe un heap inicializado
*POST: Devuelve un puntero al elemento en la raiz del heap
*/
void* elemento_raiz(heap_t* heap);
/*
*PRE: Recibe un heap inicializado y un elemento a insertar
*POST: Devuelve 0 si pudo insertar el elemento, y -1 si no pudo insertarlo
*/
int heap_insertar(heap_t* heap, void* elemento);
/*
*PRE: Recibe un heap inicializado
*POST: Devuelve 0 si pudo eliminar la raiz del heap, en caso contrario devuelve -1
*/
int eliminar_raiz(heap_t* heap);
/*
*PRE: Recibe un heap inicializado
*POST: Libera toda la memoria reservada para el heap
*/
void heap_destruir(heap_t* heap);



#endif /* HEAP_H */