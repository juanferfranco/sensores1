Unidad 1. Software para sistemas embebido
==============================================

Introducción
--------------

En esta unidad vamos a aprender técnicas para programar 
los sistemas embebidos que permitirán capturar o producir información 
del mundo exterior.

Propósito de aprendizaje
^^^^^^^^^^^^^^^^^^^^^^^^^^

Analizar la plataforma de hardware y software del controlador que se empleará
como interfaz entre los sensores-actuadores y las plataformas de software
interactivas a utilizar en el curso.

Construir aplicaciones simples para el controlador con el fin de explorar algunas
posibilidades y características de su plataforma de software.

Modelar el software del controlador, mediante el uso de máquinas
de estado, para poder establecer escenarios que permitan
documentar y verificar su funcionamiento.

Implementar el software del controlador mediante las técnicas de
programación adecuadas que permitan sacarle el máximo provecho a
dicho controlador. 

Verificar el software del controlador por medio de la
comparación de resultados de funcionamiento con los posibles
escenarios o vectores de prueba definidos en el modelado.


Temas
^^^^^^

* Herramientas del framework de arduino: toolchain, bootloader.
* Código fuente del framework de arduino: estructura y modificaciones
  simples.
* Introducción a la programación NO BLOQUEANTE.
* Técnicas de programación: encapsulamiento mediante tareas, programación
  concurrente.
* Framework de arduino: uso de clases en C++ en un ambiente de programación
  para sistemas embebidos.
* Introducción a los punteros.
* Modelamiento y programación utilizando máquinas de estado.
* Manejo del puerto serial, medidas de tiempo y retardos
  utilizando técnicas de programación no bloqueantes.

Trayecto de acciones
-----------------------


PROYECTO 1
^^^^^^^^^^^^^^^^^^^

Este primer ejercicio será de diagnóstico y autoevaluación 
para que veamos cómo están tus conocimientos de programación 
de sistemas embebidos y en programación y diseño orientado a 
objetos.
 
Se trata de una calculadora interactiva

* Debes crear dos aplicaciones: una para el PC y otra para un controlador.
* La aplicación del PC la debes realizar usando C# y será 
  del tipo Consola con .NET framework.
* La aplicación del PC y del controlador interactuarán por medio de un modelo
  cliente servidor. La aplicación del PC será el cliente y la del controlador el servidor.
* En el PC debes solicitar al usuario tres datos: operando 1, operando 2
  (serán enteros positivos de 16 bits) y operador: suma o resta.
* UNA VEZ, y solo UNA VEZ tengas los tres datos, el PC deberá enviar la información
  al controlador.
* El controlador realizará el cálculo y devolverá el resultado al PC para visualizarlo.
* El PC preguntará si se deseas continuar con más cálculos o terminar la aplicación.


Ejercicio 1
^^^^^^^^^^^^^^

Revisa `este <https://docs.google.com/presentation/d/1KGtjm8v-BUcXMhfFBSAfXOtJ8RtVSL0e90qEHsblnMc/edit?usp=sharing>`__
material donde se explican los fundamentos conceptuales de la plataforma de software
utilizada para la construcción de los programas del controlador.

En este curso vamos a utilizar el controlador ESP32. Que puede conseguir 
`aquí <https://www.didacticaselectronicas.com/index.php/comunicaciones/bluetooth/tarjeta-de-desarrollo-esp32-wroom-32d-tarjetas-modulos-de-desarrollo-con-de-wifi-y-bluetooth-esp32u-con-conector-u-fl-tarjeta-comunicaci%C3%B3n-wi-fi-bluetooth-esp32u-iot-esp32-nodemcu-d0wd-detail>`__

Ejercicio 2: explorando la carpeta de arduino
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Descarga una versión .zip del IDE de Arduino.
* Descomprime el archivo.
* En la carpeta donde está el ejecutable de arduino crea 
  la carpeta portable.
* Si estás trabajando con el ESP32 debes instalar el soporte para esta plataforma 
  en el IDE de arduino como indica `este <https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md>`__ 
  sitio.
* Abre la carpeta y explore la estructura de directorios
* ¿Qué contiene la carpeta drivers? ¿Para qué sirve?
* ¿Qué contiene la carpeta examples y cuál es la relación con los ejemplos del IDE de arduino.
* ¿Qué contiene la carpeta libraries?
* Abre la carpeta hardware/arduino/avr
* ¿Qué contiene esta carpeta?
* Abre la carpeta hardware/arduino/avr/cores/arduino
* ¿Qué contiene esta carpeta?

Ejercicio 3: modificar el código fuente de arduino
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Tomando con referencia el ejercicio anterior:

* Busca el archivo main.cpp. Si trabajas con un arduino uno, 
  el archivo está en hardware-arduino-avr-cores-arduino. Si trabajas
  con el ESP32 busca en la carpeta portable-packages-esp32-hardware... 
  sigue hasta encontrar la carpeta cores.
* GUARDA UNA COPIA DE ESTE ARCHIVO porque lo vamos a modificar 
  pero luego debemos dejarlo como estaba para no dañar el código 
  del framework de arduino.
* Modifica este archivo de tal manera que antes y después de llamar
  la función loop se envíe por  el puerto serial el valor que devuelve
  la función millis().
* Salva el archivo main.cpp con los cambios.
* Abre el IDE de arduino y carga el ejemplo Blink.
* Abre la consola.
* ¿Qué puedes concluir?

Ejercicio 4 
^^^^^^^^^^^^^

* ¿Recuerdas el ejemplo BlinkWithoutDelay?
* Busca de nuevo el ejemplo.
* Programa el arduino.
* Abre la consola.
* Compara con el ejercicio anterior.
* ¿Qué puedes concluir con respecto a la función delay?

Ejercicio 5
^^^^^^^^^^^^^

* ¿Recuerdas el ejemplo BlinkWithoutDelay?
* Busca de nuevo el ejemplo.
* Programa el arduino.
* Abre la consola.
* Compara con el ejercicio anterior.
* ¿Qué puedes concluir con respecto a la función delay?
* Una vez termines, no olvides dejar el archivo main.cpp como
  estaba originalmente.

Ejercicio 6
^^^^^^^^^^^^^^

Analiza el siguiente código:

.. code-block:: cpp
   :lineno-start: 1

    void setup() {
      Serial.begin(115200);
    }

    void loop() {
      uint8_t counter = 20;
      counter++;
      Serial.println(counter);
      delay(100);
    }

Compara el código anterior con este:

.. code-block:: cpp
   :lineno-start: 1

    void setup() {
       Serial.begin(115200);
    }

    void loop() {
      static uint8_t counter = 20;
      counter++;
      Serial.println(counter);
      delay(100);
    }

Ahora compara con este otro código:

.. code-block:: cpp
   :lineno-start: 1

    uint8_t counter = 5;

    void setup() {
       Serial.begin(115200);
    }
    void incCounter() {
      static uint8_t counter = 10;
      counter++;
      Serial.print("Counter in incCounter: ");
      Serial.println(counter);
    }

    void loop() {
      static uint8_t counter = 20;
      counter++;
	    Serial.print("Counter in loop: ");
      Serial.println(counter);
      incCounter();
      Serial.print("Counter outside loop: ");
      Serial.println(::counter);
      ::counter++;
      delay(500);
    }

¿Qué puedes concluir?

Ejercicio 7
^^^^^^^^^^^^^

Analiza el siguiente ejemplo:

.. code-block:: cpp
   :lineno-start: 1

    const uint8_t ledPin =  3;
    uint8_t ledState = LOW;
    uint32_t previousMillis = 0;
    const uint32_t interval = 1000;

    void setup() {
      // set the digital pin as output:
      pinMode(ledPin, OUTPUT);
    }
    
    void loop() {
      uint32_t currentMillis = millis();
    
      if (currentMillis - previousMillis >= interval) 
      {
        previousMillis = currentMillis;
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
        digital(ledPin, ledState);     
      }
    }

Utilizando como referencia el código anterior crea un programa que
encienda y apague tres LEDs a 1 Hz, 5 Hz y 7 Hz respectivamente.

Ejercicio 8
^^^^^^^^^^^^^^

Vamos a analizar uno de los ejemplos que vienen con el
SDK de arduino. Este ejemplo nos permite ver cómo podemos
hacer uso de los arreglos para manipular varios LEDs:

.. code-block:: cpp
   :lineno-start: 1    
    
    int timer = 100;           // The higher the number, the slower the timing.
    int ledPins[] = {
      2, 7, 4, 6, 5, 3
    };       // an array of pin numbers to which LEDs are attached
    int pinCount = 6;           // the number of pins (i.e. the length of the array)
    
    void setup() {
      // the array elements are numbered from 0 to (pinCount - 1).
      // use a for loop to initialize each pin as an output:
      for (int thisPin = 0; thisPin < pinCount; thisPin++) {
        pinMode(ledPins[thisPin], OUTPUT);
      }
    }
    
    void loop() {
      // loop from the lowest pin to the highest:
      for (int thisPin = 0; thisPin < pinCount; thisPin++) {
        // turn the pin on:
        digitalWrite(ledPins[thisPin], HIGH);
        delay(timer);
        // turn the pin off:
        digitalWrite(ledPins[thisPin], LOW);
    
      }
    
      // loop from the highest pin to the lowest:
      for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
        // turn the pin on:
        digitalWrite(ledPins[thisPin], HIGH);
        delay(timer);
        // turn the pin off:
        digitalWrite(ledPins[thisPin], LOW);
      }
    }


Ejercicio 9
^^^^^^^^^^^^

El siguiente código muestra cómo puedes encapsular completamente
el código del ejercicio 6 en tareas.

.. code-block:: cpp
   :lineno-start: 1    

	  void setup() {
	    task1();
	    task2();
	  }

	  void task1(){
	    static uint32_t previousMillis = 0;
	    static const uint32_t interval = 1250;
	    static bool taskInit = false;
	    static const uint8_t ledPin =  3;
	    static uint8_t ledState = LOW;
	  
	    if(taskInit == false){
	  	  pinMode(ledPin, OUTPUT);	
	      taskInit = true;
	  }
	  
	  uint32_t currentMillis = millis();	
	    if ( (currentMillis - previousMillis) >= interval) {
	      previousMillis = currentMillis;
	      if (ledState == LOW) {
	        ledState = HIGH;
	      } else {
	        ledState = LOW;
	      }
	      digitalWrite(ledPin, ledState);
	   }
	  }

	  void task2(){
	    static uint32_t previousMillis = 0;
	    static const uint32_t interval = 370;
	    static bool taskInit = false;
	    static const uint8_t ledPin =  5;
	    static uint8_t ledState = LOW;
	  
	    if(taskInit == false){
	  	  pinMode(ledPin, OUTPUT);	
	      taskInit = true;
	    }
	  
	    uint32_t currentMillis = millis();	
	    if ( (currentMillis - previousMillis) >= interval) {
	      previousMillis = currentMillis;
	      if (ledState == LOW) {
	        ledState = HIGH;
	      } else {
	        ledState = LOW;
	      }
	      digitalWrite(ledPin, ledState);
	    }
	  }

	  void loop() {
	    task1();
	    task2();
	  }

Una de las ventajas del código anterior es que favorece el trabajo
en equipo. Nota que se puede entregar a cada persona del equipo una
tarea. Finalmente, uno de los miembros del equipo podrá integrar
todas las tareas así:

.. code-block:: cpp
   :lineno-start: 1 

    void task1(){
    // CODE
    }
    
    void task2(){
    // CODE
    }

    void task3(){
    // CODE
    }

    void setup() {
      task1();
      task2();
      task3();
	  }

	  void loop() {
      task1();
	    task2();
      task3();
	  }

Analiza detenidamente el código anterior. Experimenta y asegurate de entenderlo
perfectamente antes de continuar.

Ejercicio 10
^^^^^^^^^^^^^^^

Observa detenidamente el código de las siguientes tareas. ¿Es muy similar, verdad?
En este ejercicio veremos una construcción interesante de
C++ que permite reutilizar código. Nota que el código de las tareas
1 y 2 es prácticamente el mismo, solo que está actuando sobre diferentes datos. 

¿Cómo así? ¿Recuerdas tu curso de programación orientado a objetos?

Analiza por partes. Primero, la inicialización de la tarea:

Para la tarea 1 (task1):

.. code-block:: cpp
   :lineno-start: 1 

    if(taskInit == false){
      pinMode(ledPin, OUTPUT);	
      taskInit = true;
	  }

Para la tarea 2 (task2):

.. code-block:: cpp
   :lineno-start: 1 

    if(taskInit == false){
      pinMode(ledPin, OUTPUT);	
      taskInit = true;
	  }


En el código anterior cada tarea tiene una variable que permite
activar el código solo un vez, es decir, cuando taskInit es false.
Esto se hace así para poder inicializar el puerto de salida donde
estará el LED conectado. Recuerde que esto se hace solo una vez 
cuando llamemos taskX() (X es 1 o 2) en la función
setup().

El código que se llamará repetidamente en la función loop:

Para la tarea 1:

.. code-block:: cpp
   :lineno-start: 1 

	   if ( (currentMillis - previousMillis) >= interval) {
	     previousMillis = currentMillis;
	     if (ledState == LOW) {
	       ledState = HIGH;
	     } else {
	       ledState = LOW;
	     }
	     digitalWrite(ledPin, ledState);
	   }


Para la tarea 2:

.. code-block:: cpp
   :lineno-start: 1 

    uint32_t currentMillis = millis();	
	  if ( (currentMillis - previousMillis) >= interval) {
	    previousMillis = currentMillis;
	    if (ledState == LOW) {
	      ledState = HIGH;
	    } else {
	      ledState = LOW;
	    }
	    digitalWrite(ledPin, ledState);
	  }

Nota que los datos sobre los que actúa cada código, aunque
tienen el mismo nombre son datos distintos:

Para la tarea 1:

.. code-block:: cpp
   :lineno-start: 1 

	 static uint32_t previousMillis = 0;
	 static const uint32_t interval = 1250;
	 static bool taskInit = false;
	 static const uint8_t ledPin =  3;
	 static uint8_t ledState = LOW;

Para la tarea 2:

.. code-block:: cpp
   :lineno-start: 1 

	 static uint32_t previousMillis = 0;
	 static const uint32_t interval = 370;
	 static bool taskInit = false;
	 static const uint8_t ledPin =  5;
	 static uint8_t ledState = LOW;

Pero ¿Por qué son distintos? porque estamos declarando las variables
como estáticas dentro de cada tarea.
Esto implica que las variables son privadas a cada función pero
se almacenan en memoria como si fueran variables globales.

¿Entendiste? No avances si esto no está claro.

Esto introduce la siguiente pregunta: ¿Qué tal si pudiéramos tener
el mismo código, pero cada vez que lo llamemos indicarle sobre
que datos debe actuar? Pues lo anterior es posible en C++ usando
una construcción conocida como clase.

La clase nos permite definir un nuevo tipo dato y los algoritmos
que se pueden aplicar a ese nuevo tipo de dato. En este caso,
necesitamos que cada tarea pueda tener sus propias variables para
previousMillis, interval, ledPin, ledState.

.. code-block:: cpp
   :lineno-start: 1    

    class LED{
        private:
        uint32_t previousMillis;
        const uint32_t interval;
        const uint8_t ledPin;
        uint8_t ledState = LOW;
	  };

De esta manera en cada tarea podremos crear un nuevo LED así:

.. code-block:: cpp
   :lineno-start: 1

    void task1(){
        static LED led;
    }

.. code-block:: cpp
   :lineno-start: 1

    void task2(){
        static LED led;
    }

A cada nuevo LED se le conoce como un objeto. led es
la variable por medio de las cuales podremos acceder a cada
uno de los objetos creados en task1 y task2.

Notas:

* Cada objeto es independiente, es decir, cada objeto tiene su propia
  copia de cada variable definida en la clase.
  ¿Cuál es el contenido de cada objetos? el contenido es un uint32_t,
  un const uint32_t, un const uint8_t y uint8_t a los cuales les
  hemos dado nombres: previousMillis, interval, ledPin y ledState
  respectivamente.

* Las variables led definidas en task1 y task2 NO SON OBJETOS,
  son variables de tipo LED que permiten acceder al contenido de cada objeto. 

* led es una variable propia de cada tarea.
* Note que las variables definidas en LED son privadas (private). Esto
  quiere decir que no vamos a acceder a ellas directamente. Ya veremos
  más abajo cómo modificar sus valores.

Nuestro nuevo tipo LED tiene un problema y es que no permite definir para cada
LED creado el intervalo y el puerto donde se conectará.Para ello,
se introduce el concepto de constructor de la clase. El constructor,
permite definir los valores iniciales de cada objeto.

.. code-block:: cpp
   :lineno-start: 1    

    class LED{
        private:
        uint32_t previousMillis;
        const uint32_t interval;
        const uint8_t ledPin;
        uint8_t ledState = LOW;

        public:
          LED(uint8_t _ledpin, uint32_t _interval): ledPin(_ledpin), interval(_interval) {
          pinMode(_ledpin, OUTPUT);
          previousMillis = 0;
        }
	  };

El constructor de la clase es un método que recibe los valores
iniciales del objeto y no devuelve nada.

Ahora si podemos definir cada objeto:

.. code-block:: cpp
   :lineno-start: 1

    void task1(){
        static LED led(3,725);
    }

.. code-block:: cpp
   :lineno-start: 1

    void task2(){
      static LED led(5, 1360);

.. code-block:: cpp
   :lineno-start: 1

    class LED{

    private:
      uint32_t previousMillis;
      const uint32_t interval;
      const uint8_t ledPin;
      uint8_t ledState = LOW;

    public:
      LED(uint8_t _ledpin, uint32_t _interval): ledPin(_ledpin), interval(_interval) {
       pinMode(_ledpin, OUTPUT);
       previousMillis = 0;
      }

      void toggleLED(){
       uint32_t currentMillis = millis();	
       if ( (currentMillis - previousMillis) >= interval) {
         previousMillis = currentMillis;
         if (ledState == LOW) {
           ledState = HIGH;
         } else {
           ledState = LOW;
         }
         digitalWrite(ledPin, ledState);
       }
      }
    };   


Finalmente, al llamar toggleLED debemos indicar sobre qué objeto
deberá actuar:

.. code-block:: cpp
   :lineno-start: 1

    void task1(){
        static LED led(3,725);

        led.toggleLED();
    }

.. code-block:: cpp
   :lineno-start: 1

    void task2(){
        static LED led(5, 1360);
        led.toggleLED();
    }

La versión final del código será:

.. code-block:: cpp
   :lineno-start: 1

	  class LED{
	    private:
	
            uint32_t previousMillis;
            const uint32_t interval;
            bool taskInit = false;
            const uint8_t ledPin;
            uint8_t ledState = LOW;
    
        public:
	
            LED(uint8_t _ledpin, uint32_t _interval): ledPin(_ledpin), interval(_interval) {
                pinMode(_ledpin, OUTPUT);
                previousMillis = 0;
            }
	  
            void toggleLED(){
                uint32_t currentMillis = millis();	
                if ( (currentMillis - previousMillis) >= interval) {
                    previousMillis = currentMillis;
                    if (ledState == LOW) {
                        ledState = HIGH;
                    } else {
                        ledState = LOW;
                    }
                    digitalWrite(ledPin, ledState);
                }
            }
	  };

	  void setup() {
	    task1();
	    task2();
	  }

    void task1(){
	    static LED led(3,1250);
	    led.toggleLED();
	  }

	  void task2(){
	    static LED led(5,375);
	    led.toggleLED();
	  }

	  void loop() {
	    task1();
	    task2();
	  }

Ejercicio 11
^^^^^^^^^^^^^

Podemos llevar un paso más allá el ejercicio anterior si añadimos
el concepto de arreglo. ¿Para qué? Observa que el código de
task1 y task2 es muy similar. Tal vez podamos resolver el problema
usando únicamente una tarea:

.. code-block:: cpp
   :lineno-start: 1    

    class LED{

    private:
      uint32_t previousMillis;
      const uint32_t interval;
      const uint8_t ledPin;
      uint8_t ledState = LOW;

    public:
      LED(uint8_t _ledpin, uint32_t _interval): ledPin(_ledpin), interval(_interval) {
       pinMode(_ledpin, OUTPUT);
       previousMillis = 0;
      }

      void toggleLED(){
       uint32_t currentMillis = millis();	
       if ( (currentMillis - previousMillis) >= interval) {
         previousMillis = currentMillis;
         if (ledState == LOW) {
           ledState = HIGH;
         } else {
           ledState = LOW;
         }
         digitalWrite(ledPin, ledState);
       }
      }

    };

    void setup() {

    }

    void task(){
      static LED leds[2] = {{3,725},{5,1300}};

      for(int i= 0; i < 2; i++){
        leds[i].toggleLED();
      }

    }

    void loop() {
        task();
    }

De nuevo, analiza el código anterior. Experimenta. ¿Está todo claro?

Ejercicio 12: miniRETO
^^^^^^^^^^^^^^^^^^^^^^^

¿Qué son los punteros? para entenderlos te propongo un mini RETO. Analiza
en detalle el siguiente código

.. code-block:: cpp
   :lineno-start: 1    

    void setup(){
        Serial.begin(115200);
    }


    void processData(uint8_t *pData, uint8_t size, uint8_t *res){
      uint8_t sum = 0;

      for(int i= 0; i< size; i++){
        sum = sum + *(pData+i) - 0x30;
      }
      *res =  sum;
    }

    void loop(void){
      static uint8_t rxData[10];
      static uint8_t dataCounter = 0;  

      if(Serial.available() > 0){
          rxData[dataCounter] = Serial.read();
          dataCounter++;
        if(dataCounter == 5){
           uint8_t result = 0;
           processData(rxData, dataCounter, &result);
           dataCounter = 0;
           Serial.println(result);
        }
      }
    }

En la función loop se define un arreglo de enteros de 8
bits sin signo (uint8_t). A la función processData le estamos
pasando la dirección del primer elemento
del arreglo, la cantidad de datos almacenados en el arreglo
y la dirección de la variable result, definida también en loop,
donde se almacenará el resultado de processData. Nota que
processData no retorna un valor y sin embargo, produce un
resultado que puede guardarse en la variable result.

Las variables pData y res son punteros. Nota que al llamar 
processData estamos almacenando en esas variables la dirección
del primer elemento del arreglo y la dirección de la variable
result.

* ¿Qué crees entonces que son los punteros? 
* ¿Para qué sirven los punteros?


PROYECTO 2
^^^^^^^^^^^^^

Debes controlar el funcionamiento algunos sensores, actuadores y tareas desde el computador.

* Debes crear dos aplicaciones: una para el PC y otra para tu controlador.
* La aplicación del PC la debes realizar usando Visual Studio y será 
  del tipo Consola con .NET framework.
* La aplicación del PC y del controlador interactuarán por medio de un modelo
  cliente servidor. La aplicación del PC será el cliente y la del controlador el servidor.
* Para la aplicación del controlador: 

  * Crea 4 tareas concurrentes. 
  * La tarea uno encenderá y apagará continuamente un LED a 1 Hz;
    la tarea 2 otro LED a 5 Hz; la tarea 3 otro LED a 7Hz; la tarea 4 recibirá comandos
    para leer un sensor digital, leer un sensor analógico, modificar un actuador digital,
    modificar un actuador analógico por PWM.

* En la aplicación del PC debes solicitarle al usuario comandos para interactuar con la
  aplicación del controlador:

  * Un comando para modificar la frecuencia de cada una de las tareas 1, 2 y 3. Debes
    especificar la tarea y la frecuencia.
  * Para la tarea 4 define comandos que te permitan seleccionar el sensor/actuador y los
    valores respectivos.

* Ten presente que solo podrás comunicarte con el controlador una vez tengas toda la información,
  es decir, no debes hacer envíos parciales.
* El PC preguntará si se deseas continuar con la aplicación o terminar.


Ejercicio 13
^^^^^^^^^^^^^

Revisa `este <https://drive.google.com/open?id=1yuDi-tbSpLvV9zAu_TTsXWi9PWn9XyZNPq_NEB4AMao>`__
material.

Ejercicio 14: el puerto serial
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Observa `este <https://www.youtube.com/embed/nm0EdjXEBGQ>`__ video corto que introducirá como
funcionan las comunicaciones seriales entre un sistema embebidos y una
plataforma de cómputo interactiva.

.. raw:: html

    <div style="position: relative; padding-bottom: 5%; height: 0; overflow: hidden; max-width: 100%; height: auto;">
        <iframe width="100%" height="315" src="https://www.youtube.com/embed/nm0EdjXEBGQ" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
    </div>


Ejercicio 15
^^^^^^^^^^^^^^^

Ahora lee el material de `este <https://learn.sparkfun.com/tutorials/serial-communication/all>`__
sitio y responde las siguientes preguntas:

* ¿Cuál es la diferencia entre una interfaz de comunicación paralela y una serial?
* ¿Cuál es la diferencia entre un protocolo serial sincrónico y asincrónico?
* En el caso de arduino ¿Qué tipo de protocolo usamos?
* Si el protocolo serial asíncrono que usaremos es de 8 bits, un bit de arranque,
  un bit de parada, sin bit de paridad y a 9600 bps dibuja los diagramas de tiempo cuando
  se transmite el byte 0x01 y el carácter '1'
* ¿Es lo mismo transmitir el byte 0x01 que el byte '1'?

Ejercicio 16
^^^^^^^^^^^^^^

¿Dónde encuentro el API de arduino para el manejo del serial?

`Aquí <https://www.arduino.cc/reference/en/language/functions/communication/serial/>`__
Las siguientes preguntas las responderemos en los próximos ejercicios, pero por ahora
lee algunas de las funciones del API del serial y responde:

* ¿Cual es la diferencia entre print y println?
* ¿Cuál es la diferencia entre print y write?
* ¿Qué pasa si utilizas read() cuando available() te devuelva cero?
* ¿Cuál es la diferencia entre readBytes? y readBytesUntil()?
* ¿Qué pasa si quieres leer 10 bytes con readBytes pero solo se han recibido 3?

Ejercicio 17
^^^^^^^^^^^^^^

Qué crees que ocurre cuando:

* ¿Qué pasa cuando hago un Serial.available()?
* ¿Qué pasa cuando hago un Serial.read()?
* ¿Qué pasa cuando hago un Serial.read() y no hay nada en el buffer de
  recepción?
* Un patrón común al trabajar con el puerto serial es este:

.. code-block:: cpp
   :lineno-start: 1  

    if(Serial.available() > 0){
        int dataRx = Serial.read() 
    }

* ¿Cuántos datos lee Serial.read()?
* ¿Y si quiero leer más de un dato? No olvides que no se pueden leer más datos
  de los disponibles en el buffer de recepción, claramente porque no hay
  más datos que los que tenga allí.

Ejercicio 18
^^^^^^^^^^^^^^^

Vamos a leer 3 datos del puerto serial:

.. code-block:: cpp
   :lineno-start: 1  

    if(Serial.available() >= 3){
        int dataRx1 = Serial.read()
        int dataRx2 = Serial.read() 
        int dataRx3 = Serial.read() 
    }

Ejercicio 19
^^^^^^^^^^^^^

¿Qué escenarios podría tener en este caso?

.. code-block:: cpp
   :lineno-start: 1  

    if(Serial.available() >= 2){
        int dataRx1 = Serial.read()
        int dataRx2 = Serial.read() 
        int dataRx3 = Serial.read() 
    }


Ejercicio 20: miniRETO
^^^^^^^^^^^^^^^^^^^^^^^

Piense cómo podrías hacer lo siguiente:

.. code-block:: cpp
   :lineno-start: 1  

    void taskSerial(){
        // Esta tarea tiene su propio buffer de recepción,
        // es decir, su propio vector. Nadie más tiene acceso

    }

    void loop(){
        taskSerial();
    }


* Almacenar los datos en su propio buffer de recepción
  (el buffer será un arreglo).
* El buffer debe estar encapsulado en la tarea
* Los datos almacenados en el buffer no se pueden perder
  entre llamados a taskSerial(). La función taskSerial() se llama
  en la función loop.  
* ¿Qué debes hacer para saber, en cualquier parte del código de taskSerial(),
  cuántos datos tengo guardados en el buffer de recepción?

Ejercicio 21
^^^^^^^^^^^^^^^

Vamos a detenernos un momento en el software del lado del
computador: el terminal. Veamos dos de ellas, la terminal
de arduino y `esta <https://sourceforge.net/projects/scriptcommunicator/>`__
otra (scriptcommunicator)

* ¿Qué es un programa terminal? 
* ¿Para qué sirve?

Ejercicio 22
^^^^^^^^^^^^^^

Considera el siguiente programa

.. code-block:: cpp
   :lineno-start: 1  

    void setup()
    {
      Serial.begin(9600);
    }

    void loop()
    {

      if(Serial.available() > 0){

        Serial.read();

        int8_t var = -1;

        Serial.println("Inicio de la prueba");
        Serial.write(var);
        Serial.print("\n");
        Serial.print(var);
        Serial.print('\n');
        Serial.println("Fin de la prueba"); 
      }
    }

* Observa el resultado de la prueba.
* ¿Qué observas en la terminal de arduino justo en estas dos líneas?
 
.. code-block:: cpp
   :lineno-start: 1  

    Serial.write(var);
    Serial.print(var);


* ¿Qué observas en Scriptcommunicator para las dos líneas anteriores?
*  En la siguiente parte del código:

.. code-block:: cpp
   :lineno-start: 1  

    if(Serial.available() > 0){

        Serial.read();

Comenta la línea Serial.read() en esta parte del código:

.. code-block:: cpp
   :lineno-start: 1  

    if(Serial.available() > 0){

        //Serial.read();

* ¿Qué ocurre? ¿Por qué ocurre esto?

En la siguiente parte del código:

.. code-block:: cpp
   :lineno-start: 1  

    Serial.println("Inicio de la prueba");
    Serial.write(var);
    Serial.print("\n");
    Serial.print(var);
    Serial.print('\n');
    Serial.println("Fin de la prueba"); 

¿Cuál es la diferencia entre estas dos líneas de código?

.. code-block:: cpp
   :lineno-start: 1  

   Serial.print("\n");

   Serial.print('\n');

Ejercicio 23: miniRETO
^^^^^^^^^^^^^^^^^^^^^^^

Considera el siguiente código para analizar en Scriptcommunicator:

.. code-block:: cpp
   :lineno-start: 1  

    void setup()
    {
      Serial.begin(9600);
    }

    void loop()
    {

      if(Serial.available() > 0){
        Serial.read();
        int8_t var = 255;
        int8_t var2 = 0xFF;

        Serial.write(var);
        Serial.print(var);
        Serial.write(var2);
        Serial.print(var2);

      }
    }

Explica qué está ocurriendo en cada caso.

Ejercicio 24: máquinas de estado
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Una experiencia interactiva posee un sensor que produce ruido eléctrico al
cambiar de estado. La siguiente figura, capturada con un osciloscopio
muestra la señal del sensor.

.. image:: ../_static/bounce.jpg

En la figura se observa el ruido generado en la transición de la señal
al pasar del estado alto al estado bajo; sin embargo, el
mismo fenómeno ocurre al cambiar del estado bajo al alto. Note que
además pueden ocurrir falsos positivos en la señal, que se manifiestan
como pulsos de muy corta duración.

Un ingeniero electrónica experto nos indica que podemos considerar un
cambio de estado en el sensor siempre que la señal esté estable por
lo menos durante 100 ms, es decir, sin ruido y sin falsos positivos.

Se debe realizar una aplicación que filtre el comportamiento ruidoso
del sensor y reporte por un puerto serial únicamente los valores
estables de la señal.

Para este ejercicio debes:

* Realizar un diagrama con el modelo en máquinas de estado para la aplicación
* Definir escenarios de prueba usando diagramas de secuencias.
* Implementar el modelo.
* Verificar los escenarios definidos

Ejercicio 25: miniRETO
^^^^^^^^^^^^^^^^^^^^^^^^^

Se requiere construir una aplicación para controlar una bomba temporizada.
La siguiente figura ilustra la interfaz de la bomba. El circuito de control
de la bomba está compuesto por tres sensores digitales,
en este caso pulsadores, denominados UP, DOWN, ARM (los simularemos con el PC),
un display (LCD) y una salida digital para activar la bomba
(simularemos la salida y el display con el PC).

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


Para este ejercicio debes:

* Realizar un diagrama con el modelo en máquinas de estado para la aplicación
* Definir escenarios de prueba usando diagramas de secuencias.
* Implementar el modelo.
* Verificar los escenarios definidos

.. Solución a ejercicios
  
  `Aquí <https://github.com/juanferfranco/sensores1/tree/master/docs/_semana5/bomb.ino>`__ una solución de 2020-10 al problema:

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

  Un ejercicio extra para practicar: se propone implementar el modelo que muestra en
  esta imagen:

  .. image:: ../_static/SM.jpeg

PROYECTO 3
^^^^^^^^^^^^^^

En una experiencia interactiva se requiere comunicar un controlador
con una aplicación interactiva (AI). El controlador maneja varios
sensores y varios actuadores. Debes leer con detenimiento la descripción
del protocolo de comunicación y construir un modelo usando una
máquina de estados que te permita capturar de manera gráfica el texto.
Este modelo te permitirá visualizar más fácilmente
el funcionamiento de tu controlador y todos los posibles escenarios
de prueba que deberás posteriormente verificar.

En este proyecto no vas a implementar la AI, te vas a concentrar en
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

Los PASOS para realizar la comunicación son:

* La AI inicia una transacción enviando el byte 3E.
* El controlador deberá responder con el byte 4A.
* La AI no podrá continuar hasta no recibir la respuesta
  del controlador.
* Una vez el controlador responda, la AI enviará una secuencia
  de bytes. 
* Cada byte tendrá la siguiente función:

  Byte 1: longitud

  Byte 2: dirección
  
  Byte 3: comando
  
  Byte 4 a n: datos
  
  Byte n+1: verificación

El byte longitud indicará la cantidad de bytes que la AI le enviará
al controlador a partir del byte 2 hasta el byte n + 1. Para
este ejercicio no te preocupes por los bytes dirección,
comando y datos, puedes colocar allí lo que quieras.

El byte de verificación será calculado así: 

Byte1 XOR Byte2 XOR … XOR Byten.

Recuerda que en lenguaje C el operador XOR es este: ^

* Si la AI se demora más de un 1 segundo en enviar la secuencia,
  el controlador enviará a la AI el byte 3D y la AI deberá iniciar
  de nuevo la secuencia de comunicación desde el paso 1.

* El controlador deberá calcular el byte de verificación que tendrá
  que coincidir con el cálculo de la AI. Si el byte de verificación 
  no corresponde, el controlador enviará el byte 3F y la AI deberá
  reenviar el paquete.

* Si el controlador recibe bien el paquete deberá responder a la AI con
  el byte 4A y luego enviar la siguiente secuencia de bytes:

  Byte 1: longitud

  Byte 2: Byte4 recibido

  Byte m: Byten recibido

  Byte m+1: verificación

La verificación será calculada desde el Byte 1 hasta el byte m.

* Si la AI recibe correctamente el paquete deberá responder con el byte 4A.

* El controlador quedará preparado para volver al paso 1,
  es decir, iniciar una nueva transacción.

* Si pasado 1 segundo el controlador no recibe el 4A, entonces este
  deberá retransmitir el paquete a la AI. Este comportamiento solo 
  se detendrá una vez la AI envié el 4A.

