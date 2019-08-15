Semana 5
===========

Esta semana vamos a revisar la implementación que cada uno realizó de la bomba. Adicionalmente, 
vamos a introducir algunas técnicas de programación del puerto serial.

Material de referencia
-----------------------
En el siguiente `enlace <https://www.gammon.com.au/serial>`__ se puede encontrar un material de 
referencia que sirve para complementar los ejercicios de esta semana.

Ejercicio 
------------
Vamos a retomar el problema de la calculadora:

* Se debe ingresar en la terminal de arduino una cadena de caracteres así: XXXX operación YYYY. Donde 
  XXXX y YYYY son números enteros de 1 a 4 dígitos y operación puede ser suma, resta, división, multiplicación 
  o módulo.

* Resolver el ejercicio utilizando máquinas de estado, defina un estado para esperar el primer operando 
  y un estado para esperar el segundo operando. ¿Cómo se detecta que se recibió el primer operando? ¿Cómo 
  se detecta que recibió el último operando?

* Repita el ejercicio anterior, pero esta vez almacenando en un buffer<la cadena completa introducida por 
  el usuario. Luego procese la cadena de caracteres identificando los operadores y el operando.

* Por último repita el ejercicio, pero esta vez utilizando métodos de la clase String de arduino. No 
  confundir con string (con mayúscula) son dos cosas diferentes.

NOTA: no utilice la función parseInt. 

