# TDA LISTA

## Algoritmos y programación 2, FIUBA, Curso 03 Méndez

### Autor: Mateo Bulnes

## 1. Enunciado
Se pide implementar una Lista simplemente enlazada. Para ello se brindan las firmas de las funciones públicas a implementar
y se deja a criterio del alumno la creación de las funciones privadas del TDA para el correcto funcionamiento de
la Lista cumpliendo con las buenas prácticas de programación.
Dentro de este TDA, se pide incluir también la implementación de las funciones básicas de los TDAs Pila y Cola, cumpliendo
así que este satisfaga el comportamiento de las tres estructuras.
Adicionalmente se pide la creación de un iterador interno y uno externo para la lista.

## 2. Archivos
El trabajo práctico consiste de los siguientes archivos: 

- lista.h
- lista.c
- pa2mm.h 
- pruebas.c
- Tda_lista.pdf
- README
Aclaración: el archivo pa2mm.h es una biblioteca externa brindada por la catedra para realizar las pruebas del TP.

## 3. Resultado esperado

El TDA entregado deberá compilar y pasar las pruebas dispuestas por la cátedra sin errores, adicionalmente estas pruebas
deberán ser ejecutadas sin pérdida de memoria.

### Linea de compilación:
`gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype -limits -pedantic -Werror -O0`

### Linea de ejecución y chequeo de memoria:
`valgrind --leak -check=full --track -origins=yes --show -reachable=yes ./lista_se`

## 4. Ejercitación

Deberá explicar qué es lo entregado y el funcionamiento particular de la implementación elegida(no es necesario detallar función por función, solamente explicar como funciona el código) y por qué se eligió
dicha implementación.

<blockquote>El funcionamiento consiste en implementar una lista simplemente enlazada mediante el uso de nodos, a la que se le realizan pruebas de inserción, eliminación, etc. 
Además, esta implementación de lista tambien va a ser probada como PILA y como COLA, y también se le agregaron las funcionalidades de iterador externo e interno.</blockquote>

**a**. ¿Qué es lo que entendés por una lista? ¿Cuáles son las diferencias entre ser simple o doblemente enlazada?
<blockquote>
  Por una lista entiendo que es una estructura de datos que agrupa elementos uno atras de otro sin ningun tipo de criterio a la hora de eliminarlos o agregarlos a la misma.
			Definido mas técnicamente, es un tipo de dato abstracto basado en nodos enlazados, los cuales apuntan a su siguiente, de esta forma quedan conectados como una cadena; el final 
			de la lista se determina cuando el ultimo nodo apunta a NULL.
			La diferencia entre una lista simplemente enlazada y una lista doblemente enlazada es que, en la simplemente enlazada cada nodo solo apunta al nodo que le sigue, por lo tanto solo se puede recorrer la lista en un sentido; en cambio en la doblemente enlazada cada nodo apunta al nodo que le sigue y a su anterior, de esta forma se puede recorrer la lista en ambos sentidos (se puede ir para adelante y volver si es necesario).
  
</blockquote>

**b**. ¿Cuáles son las características fundamentales de las Pilas? ¿Y de las Colas?
<blockquote>
  La característica fundamental de la pila es que tiene un criterio de entrada y salida de datos llamado LIFO (last in, first out), es decir que el último elemento que fue apilado va a ser el primer elemento en ser desapilado, este criterio se debe respetar siempre que se desapile.
	
  La cola también tiene un criterio de entrada y salida de datos llamado FIFO (first in, first out), es decir que el primer elemento encolado va a ser el primer elemento en ser desencolado.
</blockquote>

**c**. ¿Qué es un iterador? ¿Cuál es su función?
<blockquote>
Un iterador es un TDA auxiliar que nos ayuda a recorrer la lista de manera secuencial, es decir que me evita volver a recorrer los elementos que ya recorrí a medida que voy recorriendo, ya que el iterador va apuntando al nodo en el que estoy mientras voy recorriendo. Al hacer esto con el iterador se logra reducir la complejidad cuando se recorre
			la lista, ya que puedo acceder directamente al elemento en el que me quede en lugar de recorrer desde el principio cada vez
</blockquote>

**d**. ¿En qué se diferencia un iterador interno de uno externo?
<blockquote>
La diferencia entre iterador externo e interno es que, en el externo, se usan las propias funciones primitivas del iterador para recorrer la lista, donde se puede pensar que el iterador va apuntando desde afuera a cada elemento de la lista y cuando queremos pasar al siguiente elemento simplemente le pedimos que de un paso hacia adelante (apuntando al nodo que sigue), en este caso nosotros controlamos la iteración (por ejemplo con un while).

En cambio el iterador interno puede recorrer todos los elementos de la lista sin que nosotros controlemos el ciclo de iteración, es decir que se ejecuta la función del iterador interno y al salir ya recorrió toda la lista, ademas a cada elemento de la lista le aplica una función que recibe por parametro que puede tener muchos usos, por ejemplo imprimir los elementos a medida que se van recorriendo.
</blockquote>
