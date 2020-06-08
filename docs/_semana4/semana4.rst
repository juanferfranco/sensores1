
COPY FROM Semana 2
===========

Las actividades para esta semana son:

* Analizaremos una solución al problema de la semana anterior
* Veremos cómo funciona el puerto serial desde la capa física.
* Vamos a estudiar cómo se transforma un programa de un arduino
  desde el código de alto nivel hasta grabarlo en la memoria
  del controlador.
* Vamos a realizar modificaciones simples al código fuente del
  framework de arduino.

Material
---------------

En los siguientes enlaces se pueden ver dos soluciones al problema
de la calculadora:

* `Solución 1 <https://github.com/juanferfranco/sensores1/tree/master/Projects/Calculadora>`__.
* `Solución 2 <https://github.com/juanferfranco/sensores1/tree/master/Projects/CalculadoraStrings>`__.
* `Desde el código fuente hasta el código de máquina <https://docs.google.com/presentation/d/1ALFSDo1SPdwFz1l3JuEe_uvgPX0AkpxW5rRN4zhH0ac/edit?usp=sharing>`__


COPY FROM Semana 3
===========

Esta semana realizaremos la evaluación formativa y la evaluación
sumativa.


Actividad 1
---------------
`Evaluación formativa <https://docs.google.com/document/d/1vJIkNux2q-T1-Nd1-GwTw59nfL-lGV8HoDky5HXpFoo/edit?usp=sharing>`__.


Actividad 2
--------------
Solución a la evaluación formativa.

Actividad 3
------------

`Evaluación sumativa <https://docs.google.com/document/d/1c4mcvlxSo4lcY6_5ROeukOfwez9s5J1BbC1tDGNSWVw/edit?usp=sharing>`__.




Semana 4
===========
Esta semana realizaremos las siguientes actividades:

Sesión 1: retroalimentación del parcial 1. La acción
de mejora ya se realizó al dejar continuar el parcial
en la casa.

Sesión 2: estudiaremos cómo modelar e implementar sistemas
embebidos usando máquinas de estado.


Sesión 1
^^^^^^^^^
En `este enlace <https://github.com/juanferfranco/sensores1/tree/master/Projects/parcial1>`__
se presenta una posible solución al problema de la evaluación sumativa.

.. seealso:: 

    En `este sitio <http://www.gammon.com.au/millis>`__ se analiza la técnica que
    hemos venido utilizando para medir tiempos sin bloquear el microcontrolador.

Sesión 2
^^^^^^^^^
Para abordar la técnica de programación usando máquinas de estado vamos a
realizar dos ejercicios.


Ejercicio 1
------------
Una experiencia interactiva posee un sensor que produce ruido eléctrico al
cambiar de estado. La siguiente figura, capturada con un osciloscopio
muestra una captura de la señal del sensor.

.. image:: ../_static/bounce.jpg

En la figura se observa el ruido generado en la transición de la señal que
genera el sensor al pasar del estado alto al estado bajo; sin embargo, el
mismo fenómeno ocurre al cambiar del estado bajo al alto. Note que
además pueden ocurrir falsos positivos en la señal, que se manifiestan
como pulsos de muy corta duración.

Un ingeniero electrónica experto nos indica que podemos considerar un
cambio de estado en el sensor siempre que la señal esté estable por
lo menos durante 100 ms, es decir, sin ruido y sin falsos positivos.

Se debe realizar una aplicación que filtre el comportamiento ruidoso
del sensor y reporte por un puerto serial únicamente los valores
estables de la señal.

Ejercicio 2
------------
Se requiere construir una aplicación para controlar una bomba temporizada.
La siguiente figura ilustra la interfaz de la bomba. El circuito de control
de la bomba está compuesto por tres sensores, en este caso pulsadores,
denominados UP, DOWN, ARM (los simularemos con el PC), un display (LCD) y
una salida para activar la bomba (simularemos la salida con el PC).
Los sensores son digitales al igual que la salida de activación de
la bomba. El display posee una interfaz de comunicación serial.
El controlador funciona así:

.. image:: ../_static/bomb.png

* Inicia en modo de configuración, es decir, no cuenta aún, la bomba está
  ``desarmada``. El valor inicial del conteo regresivo es de 20 segundos.
* En el modo de configuración, los pulsadores UP y DOWN permiten
  aumentar o disminuir el tiempo inicial de la bomba.
* El tiempo se puede programar entre 10 y 60 segundos con cambios de 1 segundo.
* El tiempo de configuración se debe visualizar en el LCD (enviamos el
  valor al PC).
* El pulsador ARM arma la bomba.
* Una vez armada la bomba, comienza la cuenta regresiva que será visualizada
  en el LCD en por medio de una cuenta regresiva en segundos.
* La bomba explotará (se activa la salida de activación de la bomba) cuando
  el tiempo llegue a cero. En este punto el control regresará al modo de
  configuración.
* Una vez la bomba esté armada es posible desactivarla ingresando un código
  de seguridad. El código será la siguiente secuencia de pulsadores
  presionados uno después de otro:  UP, DOWN, DOWN, UP, UP, ARM.
* Si la secuencia se ingresa correctamente el controlador pasará de nuevo
  al modo de configuración de lo contrario continuará la fatal cuenta
  regresiva.
