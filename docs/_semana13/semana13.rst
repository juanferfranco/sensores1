Semana 13
===========
Esta semana exploraremos cómo utilizar processing para el desarrollo de aplicaciones móviles. Este ejercicio será la base 
para construir una aplicación que permmita comunicar processing con un sensor y/o actuador remoto mediante bluetooth 
clásico.

Objetivo
----------

1. Introducir el uso de processing para la realización de aplicaciones móviles en Android.
2. Introducir el uso de bluetooth para integrar processing con sensores y actuadores.


Ejercicio 1: soporte de Android para processing
------------------------------------------------
En este `enlace <https://android.processing.org/install.html>`__ se encuentra la documentación oficial de Android for 
processing. Siga los pasos indicados para instalar y configurar el soporte de Android.

Ejercicio 2: integración del dispositivo móvil a processing
------------------------------------------------------------
Ahora es necesario instalar el software development kit (SDK) de Android y conectar el dispositivo móvil al computador. 
Siga los pasos `aquí <https://android.processing.org/install.html>`__. Al finalizar este ejercicio debe tener una aplicación 
móvil funcional corriendo en su dispotivo móvil celular.

Ejercicio 3: soporte bluetooth para processing
-----------------------------------------------
El siguiente paso es instalar la biblioteca `ke:tai <http://ketai.org/>`__. ke:tai permite darle acceso a processing a los 
sensores, cámara y los dispositivos de red del celular, entre ellos el radio bluetooth. Para instalar la biblioteca abra 
el administrador de contribuciones de processing, busque ketai e instale la biblioteca.

Ejercicio 4: acceder al acelerómetro del celular
-------------------------------------------------
Ahora vamos a realizar una `aplicación simple <http://ketai.org/examples/accelerometer/>`__ que permita acceder al 
acelerómetro del celular. 

Ejercicio 5: prueba bluetooth
------------------------------
Una vez instaladas todas las herramientas anteriores es hora de probar el funcionamiento del bluetooth entre processing 
y arduino. Vamos a utilizar el `siguiente <http://ketai.org/examples/bluetoothcursors/>`__ programa de prueba para 
verificar el funcionamiento de la aplicación. Note que el programa tiene algunas dependencias de bibliotecas que se deberán 
instalar, en particular oscP5. Para instalar la biblioteca utilice el manejador de contribuiciones que trae el propio IDE 
de processing.

En esta aplicación solo instalaremos oscP5 para que la aplicación funcione; sin embargo, para realizar las pruebas con 
el arduino vamos a reemplazar OSC por nuestro propio protocolo binario (el que usted quiera para verificar el 
funcionamiento)

Ejercicio 6: LED RGB bluetooth
-------------------------------
Utilizando como base el ejercicio anterior realizar una aplicación para controlar el LED RGB por bluetooth.