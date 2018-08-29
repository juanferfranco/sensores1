Semana 6
===========

Durante esta semana, mediante la implementación de una lámpara RGB controlada desde el puerto serial, ampliaremos la técnica 
de programación de máquinas de estados introduciendo el uso de buffers de comunicación y el ``checksum`` o suma de chequeo 
para verificar la integridad de los datos recibidos. Adicionalmente, se estructurá el mecanismo de comunicación mediante un 
protocolo ASCII.

Objetivos
---------

1. Comprender el uso de buffers de comunicación al implementar protocolos ASCII.

2. Introducir el uso de mecanismos de verificación de integridad de las tramas enviadas y recibidas.

3. Reconocer la importancia de la verificación de las diferentes partes de la trama para garantizar la confiabilidad de los 
   datos

4. Introducir de manera práctica el concepto de puntero y utilizarlo en la implementación de protocolos de comunicación 
   ASCII.

Procedimiento
---------------

Se propone implementar un programa que permita procesar una trama ASCII para controlar un LED RGB desde la terminal de arduino.
La trama está compuesta por los siguientes campos:

* Encabezado: RGB=
* Datos: RRR,GGG,BBB
* Fin de trama: *
* Checksum: xor de los datos reibidos desde el encabezado hasta el fin de la trama sin incluirla.

Por ejemplo, una trama válida será: RGB=250,23,129*4C. En este caso, la trama indica que se desea encender el LED rojo 
a un duty cycle de 250/255, el LED green a 23/255 y el LED blue a 129/255. Las caracteres 4C indican el resultado de la 
operación XOR de: R^G^B^=^2^5^0^,^2^,^3^,^1^2^9.

Considere el siguiente material de ayuda:

* Se recomienda utilizar una calculadora de 
  `checksum <https://www.scadacore.com/tools/programming-calculators/online-checksum-calculator/>`__ 
  online para facilitar el cálculo.
* `Biblioteca estándar <https://www.nongnu.org/avr-libc/user-manual/modules.html>`__ 
   de C para microcontroladores AVR (CPU core arduino UNO).
* `La referencia <https://www.arduino.cc/reference/en/>`__ del ``framework`` de arduino.
