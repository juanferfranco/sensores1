COPY FROM WEEK 4



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









Semana 5
===========

Esta semana terminaremos de abordar la técnica de programación
de sistemas embebidos usando máquinas de estado.

Sesión 1
----------

Actividades
^^^^^^^^^^^^
En esta sesión veremos cómo modelar un problema usado máquinas de estado.

Material
^^^^^^^^^

`Presentación <https://drive.google.com/open?id=1yuDi-tbSpLvV9zAu_TTsXWi9PWn9XyZNPq_NEB4AMao>`__
sobre modelado de sistemas embebidos usando máquinas de estado.

Sesión 2
---------

Actividad
^^^^^^^^^^
En esta sesión se propondrá la construcción del modelo para la bomba y luego
solucionaremos el problema entre todos.

`Aquí <https://github.com/juanferfranco/sensores1/tree/master/docs/_semana5/bomb.ino>`__ queda el trabajo realizado entre todos el día de hoy:

.. code-block:: cpp 
   :lineno-start: 1

    uint32_t Timer = 20;

    enum class BOMBEVS {UP, DOWN, EVTIMER, ARM};
    BOMBEVS bombEvs;
    bool bombEvsFlag = false;


    bool timerInitCount = false;
    uint32_t timeOld = 0;

    void setup() {
    Serial.begin(115200);
    }

    void initCount() {
    timerInitCount = true;
    timeOld = millis();
    }

    void stopCount() {
    timerInitCount = false;
    Timer = 20;
    }

    void taskBomb() {
    enum class BombStates {SETTING, COUNTING};
    static BombStates stateVar =  BombStates::SETTING;
    static uint32_t keyInput[5] = {1, 2, 3, 4, 5};
    static uint8_t counter = 0;
    static uint32_t keyCode = 0;

    switch (stateVar) {
        case BombStates::SETTING:
        if (bombEvs == BOMBEVS::UP) {
            if (Timer < 60) {
            Timer++;
            Serial.println(Timer);
            }
        } else if (bombEvs == BOMBEVS::DOWN) {
            if (Timer > 10) {
            Timer--;
            Serial.println(Timer);
            }

        } else if (bombEvs == BOMBEVS::ARM) {
            initCount();
            stateVar = BombStates::COUNTING;
        }
        break;

        case BombStates::COUNTING:
        if (bombEvs == BOMBEVS::EVTIMER) {

            Timer--;

            if (Timer == 0) {
            Serial.println("RIP");
            for (;;);
            }
            else {

            Serial.println(Timer);
            }
        }
        else if (bombEvs == BOMBEVS::UP) {
            if (counter < 5) {
            keyCode = keyCode + 8 * keyInput[counter];
            counter++;
            }
        } else if (bombEvs == BOMBEVS::DOWN) {
            if (counter < 5) {
            keyCode = keyCode + 17 * keyInput[counter];
            counter++;
            }
        } else if (bombEvs == BOMBEVS::ARM) {
            if(keyCode == 165){
                    keyCode = 0;
                    counter = 0;  
                    Serial.println(":)");
                    stopCount();
                    stateVar = BombStates::SETTING;
            }
            else{
                counter = 0;
                keyCode = 0;
            }
        }

        break;

    }
    }

    void taskInputSerial() {
    if (Serial.available()) {
        int dataRx = Serial.read();
        if (dataRx == 'u') {
        bombEvs  = BOMBEVS::UP;
        bombEvsFlag = true;
        }
        else if (dataRx == 'd') {
        bombEvs  = BOMBEVS::DOWN;
        bombEvsFlag = true;
        }
        else if (dataRx == 'a') {
        bombEvs  = BOMBEVS::ARM;
        bombEvsFlag = true;
        }


    }
    }

    void taskTime() {
    if (timerInitCount == true) {
        uint32_t timeNow = millis();
        if ( (timeNow - timeOld) >= 1000 ) {
        timeOld = timeNow;
        bombEvs = BOMBEVS::EVTIMER;
        bombEvsFlag = true;
        }
    }
    }

    void loop() {


    taskInputSerial();

    taskTime();

    if (bombEvsFlag == true) {
        bombEvsFlag = false;
        taskBomb();
    }

    }
    

Material
^^^^^^^^^
Para la evaluación formativa se propone implementar el modelo que muestra en
esta imagen:

.. image:: ../_static/SM.jpeg



