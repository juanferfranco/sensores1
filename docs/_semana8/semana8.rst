Semana 8
===========
Esta semana realizaremos dos ejercicios de aplicación utilizando parte del código estudiado la semana pasado. Para estos
ejercicios, el código que brinda los servicios de colas y tiempo a la aplicación se ha encapsulado en clases C++. Esto busca 
hacer que el código sea más modular y reutilizable entre proyectos.


¿Cómo utilizar el código?
--------------------------
En `este <https://drive.google.com/open?id=1RNlMkv_AYJ41Ggb2Vbj72aAIBGnUAhvF>`__ enlace se puede encontrar la implementación 
de la máquina de estados de la semana pasada, pero con los cambios previamente señalados.


Ejercicio 1
------------
Una experiencia interactiva posee un sensor que produce mucho ruido eléctrico cuando cambia de estado. La siguiente figura muestra
una transición, capturada con un osciloscopio, donde puede apreciarse el fenómeno.

.. image:: ../_static/bounce.jpg

En la figura se observa el ruido generado en la transición de la señal del estado alto al estado bajo; sin embargo, el mismo 
fenómeno ocurre al cambiar de estado bajo a alto. Note que además pueden ocurrir falsos positivos en la señal que se manifiestan 
como pulsos de muy corta duración.

Un ingeniero electrónica experto informa que podemos considerar que el sensor ha cambiado de estado cuando la señal esté estable
por lo menos durante X ms. El valor de X puede programarse enviando por un puerto serial tres caracteres, ``1``, ``2`` y ``3``, 
correspondiente a tres para X: 100ms, 500ms y 1000ms respectivamente. 

Se debe realizar una aplicación que filtre el comportamiento del sensor y reporte por un puerto serial únicamente los valores 
estables del sensor así: ``1`` cuando el sensor cambie de 0 a 1 y ``0`` cuando cambien de 1 a 0.

Ejercicio 2
------------
Se requiere construir una aplicación para controlar una bomba de tiempo que al explotar genera mucha risa. La siguiente figura 
ilustra la interfaz de la bomba compuesta por tres sensores (botones) y un actuador (LCD). Los sensores son digitales y el 
actuador es un display con interfaz de comunicación serial (lo simularemos con el PC). El controlador funciona así: 

.. image:: ../_static/bomb.png

* Inicia con un valor preconfigurado de 20 segundos.
* Debe iniciar en modo de configuración, es decir, inicialmente desarmado.
* En el modo de configuración, los botones UP y DOWN permiten aumentar o disminuir el timpo inicial de la bomba.
* El tiempo se puede programar entre 1 segundo y 60 segundos.
* Cada que se modifica el tiempo, se debe visualizar el valor en el LCD (enviamos el valor al PC).
* El botón ARM arma la bomba.
* Una vez armada la bomba comienza la cuenta regresiva que será visualizada en el LCD.
* La bomba explotará cuando el tiempo llegue a cero y la aplicación terminará.
* Es posible desactivar la bomba ingresando un código de seguridad. El código será: UP, DOWN, DOWN, UP, UP y ARM.
* Si la secuencia se ingresa correctamente el controlador pasará de nuevo al modo de configuración de lo contrario continuará
  la fatal cuenta regresiva.

En la segunda sesión de esta semana vamos a analizar la biblioteca `ArduinoSerialCommand <https://github.com/scogswell/ArduinoSerialCommand>`__ 
escrita por Steven Cogswell y publicada el 23 de mayo de 2011. En 
`este <https://awtfy.com/2011/05/23/a-minimal-arduino-library-for-processing-serial-commands/>`__ sitio se puede leer la 
documentación inicial del proyecto.

NOTA: el código del ejercicio 1 lo iremos colocando 
`aquí <https://drive.google.com/open?id=1SadUq9lhGqGKTBEKJd1Gm9a81YqlYRVb>`__.


