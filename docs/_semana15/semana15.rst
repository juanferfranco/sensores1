Semana 15
===========
Durante esta semana continuaremos con los ejercicios preparatorio para el proyecto final.

Ejercicio 5: interfaz serial
-------------------------------------------------
Pruebe el protocolo definido utilizando la interfaz Serial y luego mediante la interfaz Serial1. A esta última 
conectaremos el radio de comunicación inalámbrica; sin embargo, antes de conectar el radio realizaremos pruebas con una 
interfaz serial a USB conectada al computador.

Ejercicio 6: integrar el radio inalámbrico
-------------------------------------------
Ahora integre el radio inalámbrico con la plataforma utilizando la interfaz Serial1 de la plataforma robótica. 
Haga un programa de prueba para el radio que reciba tramas por su interfaz Serial y las reenvíe a la  
interfaz serial conectada a la plataforma robótica.

Para aprender a utilizar los puertos seriales del ESP32 con el framework de Arduino, lea la información del siguiente 
`enlace <https://quadmeup.com/arduino-esp32-and-3-hardware-serial-ports/>`__.

Para integrar sistemas que operan a diferentes voltajes es necesario adaptar sus interfaces. Este `enlace <https://learn.sparkfun.com/tutorials/logic-levels>`__ 
explica cómo funcionan los niveles lógicos y este otro `enlace <https://learn.sparkfun.com/tutorials/bi-directional-logic-level-converter-hookup-guide>`__ 
muestra un circuito simple para realizar las adaptaciones de voltajes entre sistemas.

Ejercicio 7: Bluetooth
-----------------------
Ahora reprograme el ESP32 para recibir las tramas del protocolo por bluetooth. Utilice, para realizar las pruebas, la 
siguiente `aplicación <https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en>`__.

Ejercicio 8: 
--------------
Conecte las baterías y maneje el carro remotamente mediante la aplicación del ejercicio anterior.

Trabajo final
--------------
Finalmente realice una aplicación en processing for Android que le permita controlar el carro remotamente utilizando 
los sensores disponibles en el celular.