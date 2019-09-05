Semana 8
===========
Esta semana realizaremos la retroalimentación de la evaluación de la semanana pasada. Vamos 
a implementar también un nuevo ejercicio para practicar máquinas de estado y protocolos de 
comunicación.

Material
---------

Un posible modelo del ejercicio de la evaluación es el siguiente:

.. image:: ../_static/SM.jpeg

Ejercicio
----------
Asuma que un arduino UNO tiene conectados varios sensores y actuadores así:

Dos sensores digitales

Dos sensores analógicos: valores de 0 a 1023

Dos actuadores digitales.

Dos actuadores analógicos.

A su vez el arduino se conecta a un computador a través del puerto USB y se comunica 
utilizando la interfaz Serial. Realice un programa que realice las siguientes tareas 
concurrentes:

Recibir comandos a través de la interfaz Serial

Enciende y apaga un LED a una frecuencia de 10 Hz

Enciende y apaga un LED a una frecuencia de 5 Hz.

Los comandos recibidos por el puerto serial serán los siguientes:

read D1. Este comando hace que se envie al PC el valor del sensor digital 1. 
El arduino devuelve la cadena:  D1 estado. Donde estado puede ser 1 o 0.

read D2: enviar al PC el valor del sensor digital 2.  
El arduino devuelve la cadena: D2 estado. Donde estado puede ser 1 o 0.

read A1: enviar el PC el valor del sensor analógico 1.  
El arduino devuelve la cadena A1 valor. Donde valor está entre 0 y 1023.

read A2: enviar el PC el valor del sensor analógico 2. 
El arduino devuelve la cadena A2 valor. Donde valor está entre 0 y 1023.

write O1 estado: donde estado puede ser 1 o 0. 
Activa o desactiva la salida digital 1 

write O2 estado: donde estado puede ser 1 o 0. 
Activa o desactiva la salida digital 2 

write P1 valor: donde valor puede ser de 0 a 255. 
Escribir un valor de PWM igual a valor en el actuador analógico 1. 

write P2 valor: donde valor puede ser de 0 a 255. 
Escribir un valor de PWM igual a valor en el actuador analógico 2.
	
NOTAS:

Para cualquier de los comando write el arduino debe devolver ACK si reconoce el comando y 
NACK si no lo reconoce. Usted debe decidir, dados los requisitos de la aplicación, 
si requiere introducir caracteres de nueva línea y/o retorno de carro. 
TENGA PRESENTE que LOS LEDs deben funcionar SIEMPRE a 5 Hz y 10 HZ como se declaró previamente, 
ese decir, su funcionamiento no puede ser interrumpido por las operaciones del puerto serial
