# TDA ABB

## Algoritmos y programación 2, FIUBA, Curso 03 Méndez

### Autor: Mateo Bulnes
---
## 1. Enunciado

Se pide implementar un Árbol Binario de Búsqueda. Para ello se brindan las firmas de las funciones públicas a implementar
y se deja a criterio del alumno la creación de las funciones privadas del TDA para el correcto funcionamiento
del Árbol cumpliendo con las buenas prácticas de programación.
Adicionalmente se pide la implementación de un iterador interno para la estructura.

## 2. Archivos

El trabajo práctico consiste de los siguientes archivos:

- abb.h
- abb.c
- pa2mm.h
- pruebas_abb.c
- Enunciado_tda_abb.pdf
- README
Aclaración: el archivo pa2mm.h es una biblioteca externa brindada por la catedra para la realización de pruebas

## 3. Compilación y ejecución

El trabajo práctico deberá ser compilado con la siguiente linea: 

`gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype -limits -pedantic -Werror -O0`

Y chequear memoria y ejecución con la siguiente linea:

`valgrind --leak -check=full --track -origins=yes --show -reachable=yes ./abb`

## 4. Ejercitación

Se deberá explicar qué es lo entregado, como compilarlo (línea de compilación), como
ejecutarlo (línea de ejecución) y todo lo que crea necesario aclarar.


<blockquote>
--> Con el abb, se pueden realizar operaciones como buscar, insertar y eliminar un elemento, recorrer el árbol con los distintos recorridos y recorrer el árbol usando un iterador interno

--> A la hora de borrar un nodo con 2 hijos busco el predecesor inorden, yendo 1 nodo a la izquierda y todo lo que se puede hacia la derecha

--> Si el arbol no tiene una funcion comparadora no se pueden realizar las operaciones, mientras que si el arbol no tiene un destructor, las operaciones se realizan con normalidad

--> Para probar el iterador interno use una estructura extra_t que contiene un vector y un contador, donde en el vector voy guardando los elementos que voy recorriendo y el contador		 cuenta cuantas veces se invoco a la función booleana. Como función booleana use 2 funciones, una permite recorrer el árbol entero (devuelve true cuando ya se recorrió todo el árbol),  va guardando los elementos en el vector y aumenta el contador cada vez que entra en la función; La otra función realiza lo mismo que la anterior pero cuando el iterador 		llego a un elemento determinado devuelve true y corta la iteración.

--> Tengo 2 funciones comparadoras ya que tome la convención de que a la hora de insertar un elemento que ya esta en el árbol se inserta a la izquierda del mismo, en cambio en la 			función comparadora de búsqueda tengo los 3 casos (>, <, ==).

--> Para destruir el arbol use un recorrido parecido al recorrido postorden (izquierda, derecha, nodo) y cuando llega al nodo lo libero.

--> Decidí usar elementos de tipo int para simplificar las pruebas, pero se podría usar estructuras mas complejas.
</blockquote>

**a**. Explicar qué es un ABB y cómo se diferencia de un Árbol Binario

<blockquote>
Un árbol binario de búsqueda (ABB) es un árbol binario que cumple la propiedad de que si tomas cualquier nodo del árbol, el subárbol izquierdo del mismo va a contener los nodos con clave menor a la del nodo actual, mientras que el subárbol derecho contiene todos los nodos con clave mayor a la del acutal, donde los subarboles izquierdo y derecho tambien son arboles binarios de búsqueda. Esta propiedad permite realizar inserciones, busquedas y otras operaciones.

La diferencia de un ABB con un árbol binario es que, el árbol binario no tiene mucha utilidad ya que no tiene una regla especificada que le permita insertar elementos o realizar búsquedas. En cambio como el ABB tiene la regla que mencione previamente (menores a izquierda, mayores a derecha), se pueden realizar inserciones, busquedas y eliminaciones.
</blockquote>

**b**. Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario
no tenerla.

<blockquote>
La función de tener el destructor es que, como el tda permite insertar cualquier tipo de elemento (void*), el usuario necesita el destructor para poder eliminar el elemento que pasó, ya que solo el sabe que es lo que insertó. Si el destructor no estuviera, no habría forma de saber como liberar un elemento ya que puede ser que el usuario insertó una estructura compleja que requiere de algo más complejo que un simple free, y el programador no sabría como liberarlo en la implementación.
</blockquote>
