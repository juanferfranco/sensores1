Unidad 2. Software embebidos: plataforma
==========================================

Introducción
---------------
Para poder construir aplicaciones para sistemas embebidos
es necesario conocer en detalle el hardware, pero también
las herramientas de software. Este conocimiento te permitirá,
no solo construir aplicaciones eficientes, sino también
solucionar problemas o errores.

Propósito de aprendizaje
^^^^^^^^^^^^^^^^^^^^^^^^^

Analizar la plataforma de hardware y software del controlador que se empleará
como interfaz entre los sensores-actuadores y las plataformas de software
interactivas a utilizar en el curso.

Construir aplicaciones simples para el controlador con el fin de explorar algunas
posibilidades y características de su plataforma de software.

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


Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Actividad 1: encuentros sincrónicos
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Fechas: 
  
    * febrero 3 de 2021 - 2:00 p.m. Sesión de asesoría y corrección.
    * febrero 10 de 2021 - 2:00 p.m. Sesión de retroalimentación y revisión.
    
* Descripción: asesorías en tiempo real y retroalimentación final.
* Recursos: ingresa a `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__
* Duración de la actividad: 4 horas. 
* Forma de trabajo: individual-colaborativo/sincrónico

Actividad 2: preparación para el proyecto
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Descripción: realiza los siguientes ejercicios de preparación para 
  el proyecto.
* Recursos: ejercicios propuestos
* Duración de la actividad: 7 horas. 
* Forma de trabajo: individual-colaborativo/asincrónico (recuerda programar
  encuentros con tu compañero de trabajo).

Ejercicios
############

Ejercicio 1
+++++++++++++

Realiza las lecturas propuestas en `este <https://docs.google.com/presentation/d/1KGtjm8v-BUcXMhfFBSAfXOtJ8RtVSL0e90qEHsblnMc/edit?usp=sharing>`__
material donde se explican los fundamentos conceptuales de la plataforma de software
utilizada para la construcción de los programas del controlador.

Ejercicio 2: explorando la carpeta de arduino
+++++++++++++++++++++++++++++++++++++++++++++++

* Descarga una versión .zip del IDE de Arduino.
* Descomprime el archivo.
* Abre la carpeta y explore la estructura de directorios
* ¿Qué contiene la carpeta drivers? ¿Para qué sirve?
* ¿Qué contiene la carpeta examples y cuál es la relación con los ejemplos del IDE de arduino.
* ¿Qué contiene la carpeta libraries?
* Abre la carpeta hardware/arduino/avr
* ¿Qué contiene esta carpeta?
* Abre la carpeta hardware/arduino/avr/cores/arduino
* ¿Qué contiene esta carpeta?

Ejercicio 3: modificar el código fuente de arduino
+++++++++++++++++++++++++++++++++++++++++++++++++++++
Tomando con referencia el ejercicio anterior:

* Busca el archivo main.cpp.
* Modifica este archivo de tal manera que antes y después de llamar
  la función loop se envíe por  el puerto serial el valor que devuelve
  la función millis().
* Salva el archivo main.cpp con los cambios.
* Abre el IDE de arduino y carga el ejemplo Blink.
* Abre la consola.
* ¿Qué puedes concluir?

Ejercicio 4 
+++++++++++++++++++++++++++++++++++++++++++++++
* ¿Recuerdas el ejemplo BlinkWithoutDelay?
* Busca de nuevo el ejemplo.
* Programa el arduino.
* Abre la consola.
* Compara con el ejercicio anterior.
* ¿Qué puedes concluir con respecto a la función delay?

Ejercicio 5
+++++++++++++++++++++++++++++++++++++++++++++++
* ¿Recuerdas el ejemplo BlinkWithoutDelay?
* Busca de nuevo el ejemplo.
* Programa el arduino.
* Abre la consola.
* Compara con el ejercicio anterior.
* ¿Qué puedes concluir con respecto a la función delay?
* Una vez termines, no olvides dejar el archivo main.cpp como
  estaba originalmente.

Ejercicio 6
+++++++++++++++++++++++++++++++++++++++++++++++
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
+++++++++++++++++++++++++++++++++++++++++++++++

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
    
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
    }

Utilizando como referencia el código anterior crea un programa que
encienda y apague tres LEDs a 1 Hz, 5 Hz y 7 Hz respectivamente.

Ejercicio 8
+++++++++++++++++++++++++++++++++++++++++++++++
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
+++++++++++++++++++++++++++++++++++++++++++++++
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
+++++++++++++++++++++++++++++++++++++++++++++++
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
+++++++++++++++++++++++++++++++++++++++++++++++
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
+++++++++++++++++++++++++++++++++++++++++++++++
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

Actividad 3: proyecto y sustentación
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Descripción: resuelve el proyecto y prepara la sustentación
* Recursos: material de esta unidad
* Duración de la actividad: 7 horas.
* Forma de trabajo: individual

Lee con detenimiento el código de honor y luego los pasos que debes seguir
para evidenciar esta actividad.

Código de honor
##################

Para realizar este proyecto se espera que hagas lo siguiente:

* Colabora con tus compañeros cuando así se indique.
* Trabaja de manera individual cuando la actividad así te lo proponga.
* Usa solo la documentación oficial del framework del controlador y .NET de Microsoft.
* NO DEBES utilizar sitios en Internet con soluciones o ideas para abordar el problema.
* NO DEBES hacer uso de foros.
* ¿Entonces qué hacer si no me funciona algo? Te propongo que experimentes, crea hipótesis,
  experimenta de nuevo, observa y concluye.
* NO OLVIDES, este curso se trata de pensar y experimentar NO de BUSCAR soluciones
  en Internet.

Enunciado
##################

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

¿Qué debes entregar?
++++++++++++++++++++++

* Crea una carpeta principal. Guarda allí dos carpetas más, cada uno con el proyecto para el PC
  y para el controlador. Guarda los proyectos completos.
* En la carpeta principal guarda una copia de la `rúbrica <https://docs.google.com/spreadsheets/d/1F4iZ5iFgyxHRecQW1TeAi12MosEwSVgZQYYLSFQ5I3Y/edit?usp=sharing>`__
  con tu autoevaluación.
* En la carpeta principal guarda un archivo .pdf donde colocarás cuatro cosas:
  
  * La versión de Visual Studio utilizada.
  * La versión del software para programar el controlador.
  * UN ENLACE a tu ONE DRIVE donde estará alojado el video de sustentación.
  * Una tabla de contenidos que indique el instante de tiempo en el cual se pueden encontrar
    cada una de las secciones solicitas para el video.
* Comprime la carpeta principal en formato .ZIP
* Entrega el archivo .ZIP `aquí <https://auladigital.upb.edu.co/mod/assign/view.php?id=691971>`__.

¿Qué deberá tener el video de sustentación?
+++++++++++++++++++++++++++++++++++++++++++++

* Máximo 20 minutos: debes planear el video tal como aprendiste en segundo semestre
  en tu curso de narrativa audiovisual.
* Cuida la calidad del audio y del video.
* Sección 1: introducción, donde dirás tu nombre y si realizaste el proyecto
  completo. Si no terminaste indica claramente qué te faltó y por qué.
* Sección 2: muestra que tus dos programas compilan correctamente y sin errores
  o advertencias problemáticas.
* Sección 3: Realiza una demostración del funcionamiento donde ilustres todos los
  aspectos solicitados.
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

