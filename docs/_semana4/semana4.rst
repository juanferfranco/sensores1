Semana 4
===========

Propósitos de aprendizaje
--------------------------

Modelar el software del controlador, mediante el uso de máquinas
de estado, para poder establecer escenarios que permitan
documentar y verificar su funcionamiento.

Implementar el software del controlador mediante las técnicas de
programación adecuadas que permitan sacarle el máximo provecho a
dicho controlador. 

Verificar el software del controlador por medio de la
contrastación de resultados de funcionamiento con los posibles
escenarios o vectores de prueba definidos en el modelado.

Actividad de aprendizaje
-------------------------
Se realizará las SEMANA 4, 5 y 6 (semana julio 13 a la semana
de agosto 10).

Lee con detenimiento el código de honor y luego los pasos que
debes seguir para evidenciar esta actividad.

Código de honor
^^^^^^^^^^^^^^^^^
Para realizar este reto se espera que hagas lo siguiente:

* Colabora con tus compañeros cuando así se indique.
* Trabaja de manera individual cuando la actividad así te lo
  proponga.
* Usa solo la documentación oficial del framework del controlador
  y .NET de Microsoft.
* NO DEBES utilizar sitios en Internet con soluciones o ideas para
  abordar el problema.
* NO DEBES hacer uso de foros.
* ¿Entonces qué hacer si no me funciona algo? Te propongo que
  experimentes,
  crea hipótesis, experimenta de nuevo, observa y concluye.
* NO OLVIDES, este curso se trata de pensar y experimentar NO de
  BUSCAR soluciones en Internet.

Enunciado
^^^^^^^^^^^^^^^^^

En una experiencia interactiva se requiere comunicar un controlador
con una aplicación interactiva (AI). El controlador maneja varios
sensores y varios actuadores.

En este RETO no vas a implementar la AI, te vas a concentrar en
el software del controlador. Entonces la AI será simulada.

Para simular la AI utiliza `ScriptCommunicator <https://sourceforge.net/projects/scriptcommunicator/>`__.
Este software es necesario para poder controlar de manera precisa el
byte que queremos transmitir. Recuerda que al usar una terminal como
la de arduino, todos los bytes que transmites están codificados en
ASCII y por tanto cuando escribes el carácter '1' realmente estás
transmitiendo el byte 31 en base 16, es decir, la codificación ASCII
del '1'.

Cuando estés probando la aplicación de tu controlador ten presente
que la AI siempre iniciará la comunicación.

Los PASOS para realizar la comunicación:

La AI inicia una transacción enviando el byte 3E.
El controlador deberá responder con el byte 4A.
La AI no podrá continuar hasta no recibir la respuesta del controlador.
Una vez el controlador responda, la AI enviará una secuencia
de bytes, cada uno con la siguiente función:

Byte 1: longitud
Byte 2: Dirección
Byte 3: Comando
Byte 4 a n: Datos
Byte n+1: verificación

El byte longitud indicará la cantidad de bytes que la AI le enviará
al controlador a partir del byte 2 hasta byte n + 1.

El byte de verificación será calculado así: 

Byte1 XOR Byte2 XOR … XOR Byten.

Recuerda que en lenguaje C el operador XOR es este: ^

Si la AI se demora más de un 1 segundo en enviar la secuencia,
el controlador enviará a la AI el byte 3D y la AI deberá iniciar
de nuevo la secuencia de comunicación desde el paso 1.

El controlador deberá calcular el byte de verificación y esté
deberá coincidir con el cálculo de la AI. Si el byte de verificación 
no corresponde, el controlador enviará el byte 3F y la AI deberá
reenviar el paquete.

Si el controlador recibe bien el paquete deberá responder a la AI con
el byte 4A y luego enviar la siguiente secuencia de bytes:

Byte 1: longitud
Byte 2: Byte4 recibido
Byte m: Byten recibido
Byte m+1: verificación

La verificación será calculada desde el Byte 1 hasta el byte m.

Si la AI recibe correctamente el paquete deberá responder con el byte 4A.

El controlador quedará preparado para volver al paso 1,
es decir, iniciar una nueva transacción.

Si ha pasado 1 segundo y el controlador no recibe el 4A, entonces deberá
retransmitir el paquete a la AI. Este comportamiento solo se detendrá hasta
que la AI envié el 4A.


¿Qué debes entregar?
^^^^^^^^^^^^^^^^^^^^^

* Crea una carpeta principal. Guarda allí el proyecto para el controlador.
* En la carpeta principal guarda una copia de la rúbrica con tu autoevaluación.
* En la carpeta principal guarda un archivo .pdf donde colocarás cuatro cosas:
  
  * La versión del software para programar el controlador.
  * UN ENLACE a tu ONE DRIVE donde estará alojado el video de sustentación.
  * Una tabla de contenidos que indique el instante de tiempo en el cual se
    pueden encontrar cada una de las secciones solicitadas en el video.
* Comprime la carpeta principal en formato .ZIP
* Entrega el archivo .ZIP `aquí <>`__.

¿Qué deberá tener el video de sustentación?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Máximo 20 minutos: debes planear el video tal como aprendiste en segundo semestre
  en tu curso de narrativa audiovisual.
* Cuida la calidad del audio y del video.
* Sección 1: introducción, donde dirás tu nombre y si realizaste el RETO
  completo. Si no terminaste indica claramente qué te faltó y por qué.
* Sección 2: muestra que tu programa compila correctamente y sin errores
  o advertencias problemáticas.
* Sección 3: Realiza una demostración del funcionamiento donde ilustres todos los
  escenarios.
* Define un conjuntos de vectores de prueba donde indiques los datos de entrada y el
  resultado esperado.
* Aplica los vectores de prueba y muestra que si producen los valores esperados.
* Sección 4: explica la arquitectura de las aplicaciones. Utiliza una
  aplicación de `WhiteBoard <https://www.microsoft.com/en-us/microsoft-365/microsoft-whiteboard/digital-whiteboard-app>`__
  para esto.
* Tus explicaciones deben ser claras, precisas y completas. No olvides planear 
  bien tu video de sustentación.
* Debes explicar las partes de la aplicación, la función que realiza cada parte y
  sus propiedades.
* Debes explicar las relaciones entre las partes, cómo funcionan esas relaciones y
  sus propiedades
* Sección 5: protocolo de integración entre las aplicaciones.
* Debes explicar claramente cómo se comunicarán tus aplicaciones.
* Muestra de manera detallada los pasos que deben realizar cada una de las aplicaciones.
  Te recomiendo utilizar un `diagrama de secuencias <https://en.wikipedia.org/wiki/Sequence_diagram#:~:text=A%20sequence%20diagram%20shows%20object,the%20functionality%20of%20the%20scenario.>`__.



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
