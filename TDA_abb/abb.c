#include "abb.h"

#define ERROR -1


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	if(comparador == NULL)
		return NULL;
	abb_t* arbol = malloc(sizeof(abb_t));
	if(arbol == NULL)
		return NULL;
	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->destructor = destructor;

	return arbol;
}

int arbol_insertar(abb_t* arbol, void* elemento){ 
	if(arbol == NULL)
		return ERROR;

	if(arbol->nodo_raiz == NULL){
		arbol->nodo_raiz = calloc(1, sizeof(nodo_abb_t));
		if(arbol->nodo_raiz == NULL) 
			return ERROR;
		arbol->nodo_raiz->elemento = elemento;
		return 0;
	}
	
	nodo_abb_t* aux = arbol->nodo_raiz, *anterior = NULL;
	while(aux != NULL){
		anterior = aux;
		if((arbol->comparador)(elemento, aux->elemento) > 0)
			aux = aux->derecha;
		else
			aux = aux->izquierda;
	}
	nodo_abb_t* nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
	if(nuevo_nodo == NULL)
		return ERROR;
	nuevo_nodo->elemento = elemento;
	if((arbol->comparador)(elemento, anterior->elemento) > 0)
			anterior->derecha = nuevo_nodo;
		else
			anterior->izquierda = nuevo_nodo;
	return 0;
}

nodo_abb_t* buscar_predecesor_inorden(nodo_abb_t* nodo){
	if(!nodo || !nodo->izquierda)
		return NULL;
	nodo_abb_t* predecesor = nodo->izquierda;
	while(predecesor->derecha){
		predecesor = predecesor->derecha;
	}
	return predecesor;
}

nodo_abb_t* borrar_elemento(nodo_abb_t* nodo, abb_comparador comparador, void* elemento, abb_liberar_elemento destructor){
	int comparacion = (comparador)(elemento, nodo->elemento);
	if(comparacion == 0){
		if(!nodo->derecha && !nodo->izquierda){ // Si el nodo no tiene hijos
			if(destructor)
				destructor(nodo->elemento);
			free(nodo);
			return NULL;
		}
		else if(nodo->derecha && nodo->izquierda){ // Si el nodo tiene 2 hijos
			void* elemento_aux = NULL;
			nodo_abb_t* predecesor = buscar_predecesor_inorden(nodo);
			elemento_aux = nodo->elemento;
			nodo->elemento = predecesor->elemento;
			predecesor->elemento = elemento_aux;
			nodo->izquierda = borrar_elemento(nodo->izquierda, comparador, elemento_aux, destructor);
		}
		else{ // Si tiene un solo hijo
			nodo_abb_t* aux = NULL;
			if(nodo->derecha)
				aux = nodo->derecha;
			else
				aux = nodo->izquierda;
			if(destructor)
				destructor(nodo->elemento);
			free(nodo);
			return aux;
		}
	}
	else if(comparacion > 0)
		nodo->derecha = borrar_elemento(nodo->derecha, comparador, elemento, destructor);
	else if(comparacion < 0)
		nodo->izquierda = borrar_elemento(nodo->izquierda, comparador, elemento, destructor);
	return nodo;
}

int arbol_borrar(abb_t* arbol, void* elemento){
	if(arbol_vacio(arbol))
		return ERROR;

	arbol->nodo_raiz = borrar_elemento(arbol->nodo_raiz, arbol->comparador, elemento, arbol->destructor);
	return 0;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	if(arbol == NULL || arbol->nodo_raiz == NULL)
		return NULL;
	nodo_abb_t* aux = arbol->nodo_raiz;
	int comparacion = (arbol->comparador)(elemento, aux->elemento);
	while(comparacion != 0 && aux != NULL){
		if(comparacion > 0)
			aux = aux->derecha;
		else
			aux = aux->izquierda;
		if(aux != NULL)
			comparacion = (arbol->comparador)(elemento, aux->elemento);
	}
	if(aux == NULL)
		return NULL; 
	return aux->elemento;
}

void* arbol_raiz(abb_t* arbol){
	if(arbol == NULL || arbol->nodo_raiz == NULL)
		return NULL;
	return arbol->nodo_raiz->elemento;
}
bool arbol_vacio(abb_t* arbol){
	return(arbol == NULL || arbol->nodo_raiz == NULL);
}

void llenar_array_inorden(nodo_abb_t* nodo, void** array, size_t* cant_elementos, size_t tamanio_max){
	if(nodo == NULL || *cant_elementos >= tamanio_max)
		return;
	if(nodo->izquierda)
		llenar_array_inorden(nodo->izquierda, array, cant_elementos, tamanio_max);
	if(nodo){
		array[*cant_elementos] = nodo->elemento;
		(*cant_elementos)++;
	}
	if(nodo->derecha)
		llenar_array_inorden(nodo->derecha, array, cant_elementos, tamanio_max);
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t cant_elementos = 0;

	if(arbol_vacio(arbol) || array == NULL || tamanio_array == 0)
		return 0;
	llenar_array_inorden(arbol->nodo_raiz, array, &cant_elementos, tamanio_array);
	return cant_elementos;
}
void llenar_array_preorden(nodo_abb_t* nodo, void** array, size_t* cant_elementos, size_t tamanio_max){
	if(!nodo || *cant_elementos >= tamanio_max)
		return;
	if(nodo){
		array[*cant_elementos] = nodo->elemento;
		(*cant_elementos)++;
	}
	if(nodo->izquierda)
		llenar_array_preorden(nodo->izquierda, array, cant_elementos, tamanio_max);
	if(nodo->derecha)
		llenar_array_preorden(nodo->derecha, array, cant_elementos, tamanio_max);
}
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t cant_elementos = 0;

	if(arbol_vacio(arbol) || array == NULL || tamanio_array == 0)
		return 0;
	llenar_array_preorden(arbol->nodo_raiz, array, &cant_elementos, tamanio_array);
	return cant_elementos;
}

void llenar_array_postorden(nodo_abb_t* nodo, void** array, size_t* cant_elementos, size_t tamanio_max){
	if(!nodo || *cant_elementos >= tamanio_max)
		return;
	if(nodo->izquierda)
		llenar_array_postorden(nodo->izquierda, array, cant_elementos, tamanio_max);
	if(nodo->derecha)
		llenar_array_postorden(nodo->derecha, array, cant_elementos, tamanio_max);
	if(nodo && *cant_elementos < tamanio_max){
		array[*cant_elementos] = nodo->elemento;
		(*cant_elementos)++;
	}
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t cant_elementos = 0;

	if(arbol_vacio(arbol) || array == NULL || tamanio_array == 0)
		return 0;
	llenar_array_postorden(arbol->nodo_raiz, array, &cant_elementos, tamanio_array);
	return cant_elementos;
}

void iterar_inorden(nodo_abb_t* nodo, size_t* cant_recorridos, bool (*funcion)(void*, void*), void* extra, bool* terminar_recorrido){
	if(!nodo || *terminar_recorrido) 
		return;
	if(nodo->izquierda)
		iterar_inorden(nodo->izquierda, cant_recorridos, funcion, extra, terminar_recorrido);
	if(nodo && !(*terminar_recorrido)){
		*terminar_recorrido = funcion(nodo->elemento, extra);
		(*cant_recorridos)++;
	}
	if(nodo->derecha && !(*terminar_recorrido))
		iterar_inorden(nodo->derecha, cant_recorridos, funcion, extra, terminar_recorrido);
}
void iterar_preorden(nodo_abb_t* nodo, size_t* cant_recorridos, bool (*funcion)(void*, void*), void* extra, bool* terminar_recorrido){
	if(!nodo || *terminar_recorrido) 
		return;
	if(nodo){
		*terminar_recorrido = funcion(nodo->elemento, extra);
		(*cant_recorridos)++;
	}
	if(nodo->izquierda)
		iterar_preorden(nodo->izquierda, cant_recorridos, funcion, extra, terminar_recorrido);
	if(nodo->derecha)
		iterar_preorden(nodo->derecha, cant_recorridos, funcion, extra, terminar_recorrido);
}
void iterar_postorden(nodo_abb_t* nodo, size_t* cant_recorridos, bool (*funcion)(void*, void*), void* extra, bool* terminar_recorrido){
	if(!nodo || *terminar_recorrido) 
		return;
	if(nodo->izquierda)
		iterar_postorden(nodo->izquierda, cant_recorridos, funcion, extra, terminar_recorrido);
	if(nodo->derecha)
		iterar_postorden(nodo->derecha, cant_recorridos, funcion, extra, terminar_recorrido);
	if(nodo && *terminar_recorrido == false){
		*terminar_recorrido = funcion(nodo->elemento, extra);
		(*cant_recorridos)++;
	}
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(arbol_vacio(arbol) || !funcion)
		return 0;
	size_t cant_recorridos = 0;
	bool terminar_recorrido = false;
	if(recorrido == ABB_RECORRER_INORDEN){
		iterar_inorden(arbol->nodo_raiz, &cant_recorridos, funcion, extra, &terminar_recorrido);
	}
	else if(recorrido == ABB_RECORRER_PREORDEN){
		iterar_preorden(arbol->nodo_raiz, &cant_recorridos, funcion, extra, &terminar_recorrido);
	}
	else{
		iterar_postorden(arbol->nodo_raiz, &cant_recorridos, funcion, extra, &terminar_recorrido);
	}
	return cant_recorridos;
}

void destruir_nodos(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	if(!nodo)
		return;
	if(nodo->izquierda)
		destruir_nodos(nodo->izquierda, destructor);
	if(nodo->derecha)
		destruir_nodos(nodo->derecha, destructor);
	if(nodo){
		if(destructor)
			destructor(nodo->elemento);
		free(nodo);
	}
}

void arbol_destruir(abb_t* arbol){ 
	if(!arbol_vacio(arbol))
		destruir_nodos(arbol->nodo_raiz, arbol->destructor);
	free(arbol);
}