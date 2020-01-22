Semana 1
===========

Esta semana vamos a introducir el curso y a realizar una prueba diagnóstica.

Procedimiento
---------------

Vamos a realizar una evaluación formativa para diagnosticar el nivel de
programación que trae cada uno.

NOTA: en este ejercicio no debemos utilizar funciones del tipo delay
(use la función millis). Lo anterior es porque la función delay puede
bloquear, en algunas plataformas, al microcontrolador (?).

¿Y cuál es el problema con esto?

Se debe realizar una calculadora interactiva, usando la terminal de arduino.
Debe solicitar al usuario:

* Ingresar la operación: suma, resta, multiplicación, división, módulo.
* Ingresar el operando uno. El usuario puede ingresar un número entero
  de 1,2 o 3 dígitos.
* Ingresar el operando dos. El usuario puede ingresar un número entero
  de 1,2 o 3 dígitos.
* Si el usuario tarda más de 7 segundos para ingresar los datos anteriores,
  se debe solicitar de nuevo la operación e ignorar la información
  anterior.
* NO utilice métodos o funciones que bloqueen el microcontrolador, por ejemplo,
  la función delay.

