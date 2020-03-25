Semana 10
===========

Esta semana continuaremos con el reto defindo la semana semana:

Ejercicio 4: Reto
------------------
Asuma que un arduino tiene conectados varios sensores y actuadores así:

* Dos sensores digitales
* Dos sensores analógicos: valores de 0 a 1023
* Dos actuadores digitales.
* Dos actuadores analógicos.

A su vez el arduino se conecta a un computador a través del puerto USB y se comunica 
utilizando la interfaz Serial. Realice un programa, en el arduino, que realice las siguientes tareas 
concurrentes:

* Recibir comandos a través de la interfaz Serial
* Enciende y apaga un LED a una frecuencia de 10 Hz
* Enciende y apaga un LED a una frecuencia de 5 Hz.

Los comandos recibidos por el puerto serial serán los siguientes:

* read D1. Este comando hace que se envie al PC el valor del sensor digital 1. 
  El arduino devuelve la cadena:  D1 estado. Donde estado puede ser 1 o 0.

* read D2: enviar al PC el valor del sensor digital 2.  
  El arduino devuelve la cadena: D2 estado. Donde estado puede ser 1 o 0.

* read A1: enviar el PC el valor del sensor analógico 1.  
  El arduino devuelve la cadena A1 valor. Donde valor está entre 0 y 1023.

* read A2: enviar el PC el valor del sensor analógico 2. 
  El arduino devuelve la cadena A2 valor. Donde valor está entre 0 y 1023.

* write O1 estado: donde estado puede ser 1 o 0. 
  Activa o desactiva la salida digital 1 

* write O2 estado: donde estado puede ser 1 o 0. 
  Activa o desactiva la salida digital 2 

* write P1 valor: donde valor puede ser de 0 a 255. 
  Escribir un valor de PWM igual a valor en el actuador analógico 1. 

* write P2 valor: donde valor puede ser de 0 a 255. 
  Escribir un valor de PWM igual a valor en el actuador analógico 2.

La aplicación del computador es tipo consola en C# y debe tener:

* Dos hilos.
* Un hilo debe imprimir cada 100 ms el valor de un contador.
* Otro hilo pendiente de los eventos del teclado.
* Asigne una tecla a cada comando que será enviado al arduino.
* Indicar si el arduino entendió o no entendió el comando, es decir,
  mostrar el NACK o el ACK.

NOTAS:

Para cualquier de los comandos write el arduino debe devolver ACK si reconoce el comando y 
NACK si no lo reconoce. Usted debe decidir, dados los requisitos de la aplicación, 
si requiere introducir caracteres de nueva línea y/o retorno de carro. 
TENGA PRESENTE que LOS LEDs deben funcionar SIEMPRE a 5 Hz y 10 HZ como se declaró previamente, 
ese decir, su funcionamiento no puede ser interrumpido por las operaciones del puerto serial.


Evaluación Sumativa 3
----------------------
La evaluación sumativa 3 consiste en entregar el ejercicio 4 funcionando más la sustentación.

Consideraciones:
^^^^^^^^^^^^^^^^^^
* Plazo de entrega, martes 31 de marzo a las 12 de la MEDIA NOCHE
* Cree una carpeta. Incluya en esa carpeta otras dos. Una con el proyecto
  C# y otra con el proyecto Arduino. Adicionalemnte incluya un archivo .pdf con:

    * EL ENLACE, solo el ENLACE a un video que tenga las siguientes secciones:
        
        * Sección 1: mostrar cómo se compila cada proyecto.
        * Sección 2: mostrar cada proyecto corriendo.
        * Sección 3: mostar ambos proyectos funcionando de manera integrada.
        * Sección 4: explicar cómo probó cada proyecto por separado.
        * Sección 5: explicar de manera detallada cuál es la idea de funcionamiento
          general de cada proyecto y luego una explicación muy detallada.
* Comprima la carpeta anterior con SOLO usando .ZIP, no RAR, no 7Z, SOLO .ZIP. NO
  CUMPLIR CON ESTO REBAJARÁ EN UNA UNIDAD AUTOMÁTICAMENTE LA NOTA FINAL.
* El video debe tener buena calidad de audio para poder escuchar claramente su
  sustentación.
* Suba la sustentación aquí: https://www.dropbox.com/request/fLDGeeeQvte5g2Za4UYK

Criterios de evaluación
^^^^^^^^^^^^^^^^^^^^^^^^

Nota_Final = Funcionamiento*sustentación

Donde funcionamiento será una nota de 0 a 5 y sustentación un factor de 0 a 1. ESTO
quiere decir que el funcionamiento puede ser 5, pero si la sustentación es 0, la nota
final final 0.

Para la sustentación:

* 1: se incluyen todas las sesiones. En particular la 5 es correcta, precisa y detallada.
* 0.6: incluye todas las sesiones, pero la sección 5 evidencia algunos problemas conceptuales leves
* 0.4: incluye todas las sesiones, pero la sección 5 evidencia algunos problemas conceptuales graves
* 0: no entregó la sustentación completa o la sustentación no evidencia la realización y entendimiento
  del trabajo.
