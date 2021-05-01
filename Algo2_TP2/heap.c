#include "heap.h"

#define ERROR -1
#define EXITO 0

heap_t* crear_heap(heap_comparador comparador, heap_destructor destructor){
	if(!comparador || !destructor)
		return NULL;
	heap_t* heap = calloc(1, sizeof(heap_t));
	if(!heap)
		return NULL;
	heap->comparador = comparador;
	heap->destructor = destructor;
	return heap;
}

size_t pos_padre(size_t n){
	return (n-1)/2;
}

size_t pos_hijo_derecha(size_t n){
	return (2*n)+2;
}

size_t pos_hijo_izquierda(size_t n){
	return (2*n)+1;
}

void* elemento_raiz(heap_t* heap){
	if(heap->tope <= 0)
		return NULL;
	return heap->vector[0];
}
/*
*PRE: Recibe un vector y 2 posiciones
*POST: Intercambia los elementos en las posiciones recibidas
*/
void swap(void** vector, size_t i, size_t j){
	void* aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}
/*
*PRE: Recibe un heap inicializado y una posicion del heap
*POST: Ordena el heap segun el comparador usando la tecnica de sift up
*/
void sift_up(heap_t* heap, size_t n){
	if(n == 0)
		return;
	size_t padre = pos_padre(n);
	int comparacion = (heap->comparador)(heap->vector[n], heap->vector[padre]);
	if(comparacion == 1){ // el elemento insertado es menor que su padre
		swap(heap->vector, n, padre);
		sift_up(heap, padre);
	}
}

int heap_insertar(heap_t* heap, void* elemento){
	void* aux = realloc(heap->vector, sizeof(void*)*(size_t)(heap->tope+1)); //reservo un lugar para insertar el elemento 
	if(!aux)
		return ERROR;

	(heap->tope)++;
	heap->vector = aux;
	size_t indice = heap->tope - 1;
	heap->vector[indice] = elemento;

	sift_up(heap, indice);

	return EXITO;
}
/*
*PRE: Recibe un heap inicializado y una posicion del heap
*POST: Ordena el heap segun el comparador usando la tecnica de sift down
*/
void sift_down(heap_t* heap, size_t n){
	size_t pos_hijo_izq = pos_hijo_izquierda(n);
	size_t pos_hijo_der = pos_hijo_derecha(n);

	if(pos_hijo_izq >= heap->tope)
		return;

	size_t pos_menor;
	int comparacion = (heap->comparador)(heap->vector[pos_hijo_der], heap->vector[pos_hijo_izq]);
	if(comparacion == 1)
		pos_menor = pos_hijo_der;
	else
		pos_menor = pos_hijo_izq;
	comparacion = (heap->comparador)(heap->vector[n], heap->vector[pos_menor]);
	if(comparacion == -1){
		swap(heap->vector, n, pos_menor);
		sift_down(heap, pos_menor);
	}
}

int eliminar_raiz(heap_t* heap){
	if(heap->tope == 0 || !heap)
		return ERROR;

	void* elemento_a_eliminar = heap->vector[0];
	heap->vector[0] = heap->vector[(heap->tope)-1];
	(heap->tope)--;
	if(heap->tope > 0)
		sift_down(heap, 0);
	if(heap->destructor)
		heap->destructor(elemento_a_eliminar);

	return EXITO;

}

/*
*PRE: Recibe un vector, su tope y el destructor del heap
*POST: Libera la memoria reservada para el vector y sus elementos
*/
void destruir_elementos(void** vector, size_t tope, heap_destructor destructor){
	for(int i = 0; i < tope; i++){ // destruyo los elementos a los que apuntan cada puntero dentro del vector
		destructor(vector[i]);	
	}
	free(vector); //libero el vector
}

void heap_destruir(heap_t* heap){
	if(heap->tope > 0)
		destruir_elementos(heap->vector, heap->tope, heap->destructor);
	if(heap->tope == 0)
		free(heap->vector);
	free(heap);
}