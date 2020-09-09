Semana 10: Unidad 5
=======================

Propósitos de aprendizaje
--------------------------

Construir aplicaciones interactivas utilizando múltiples hilos
para la producción y el prototipado de experiencias interactivas.

Integrar controladores con aplicaciones interactivas mediante
el uso de protocolos seriales binarios.

Actividad de aprendizaje
-------------------------

Se realizará las SEMANAS 10, 11 y 12 (septiembre 7-septiembre 23).

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
  experimentes, crea hipótesis, experimenta de nuevo, observa y concluye.
* NO OLVIDES, este curso se trata de pensar y experimentar NO de
  BUSCAR soluciones en Internet.

Enunciado
^^^^^^^^^^

El reto consiste en ser capaz de reproducir el archivo de prueba
que provee el fabricante de un sensor de RFID. El archivo se encuentra
`aquí <https://drive.google.com/file/d/1iVr2Fiv8wXLqNyShr_EOplSvOJBIPqJP/view>`__.

Para ello vamos a programar un arduino para simular el sensor (vale un millón
de pesos el sensor) y vamos a programar una aplicación interactiva en C# desde
la cual enviaremos comandos al sensor tal como aparecen en el archivo de
prueba.

No olviden calcular y verificar el checksum en Arduino y en C#.

La aplicación debe tener:

* Dos hilos.
* Un hilo debe imprimir cada 100 ms el valor de un contador (aquí simulamos
  el funcionamiento de un motor o aplicación interactiva que debe mantener
  un framerate constante.
* Otro hilo responsable de realizar las operaciones de entrada salida: eventos
  del teclado y comunicaciones seriales con el sensor. 
* Asigne una tecla a cada comando que será enviado al arduino.


¿Qué debes entregar?
^^^^^^^^^^^^^^^^^^^^^

.. warning::
  * Crea una carpeta, la llamaremos principal. 
  * Guarda allí el proyecto para el controlador y el proyecto para la aplicación
    interactiva.
  * En la carpeta principal guarda una copia de la `rúbrica <https://docs.google.com/spreadsheets/d/1dDYGM7RKUWipoPZPhid-FIbw5sHI9WIYka1IgCu6OKw/edit?usp=sharing>`__
    con tu autoevaluación.
  * Comprime la carpeta principal en formato .ZIP
  * Entrega el archivo .ZIP `aquí <https://auladigital.upb.edu.co/mod/assign/view.php?id=487312>`__.

¿Qué deberás tener en cuenta para la sustentación?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* La sustentación se realizará en la última sesión de esta unidad.
* Tendrá una duración máxima de 10 minutos. Allí mostrarás: el funcionamiento y explicarás
  cómo realizaste las pruebas, qué problemas tuviste, cómo los solucionaste.
* Estudia muy bien tu solución y prepárate para responder algunas preguntas. 
* Ten en cuenta la rúbrica para preparar tu sustentación.

Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Actividad 1
^^^^^^^^^^^^^
* Fecha: septiembre 7 de 2020
* Descripción: vamos a introducir el reto.
* Recursos: ingresa a Teams
* Duración de la actividad: 1 hora , 20 minutos. 
* Forma de trabajo: grupal

Actividad 2
^^^^^^^^^^^^^
* Fecha: septiembre 7 a septiembre 9 de 2020
* Descripción: realiza algunos ejercicios.
* Recursos: mira los ejercicios abajo.
* Duración de la actividad: 5 horas. 
* Forma de trabajo: individual

Ejercicio 1
#############

¿Cómo se ve un protocolo binario?

Para responder esta pregunta vamos a utilizar como ejemplo
`este sensor <http://www.chafon.com/productdetails.aspx?pid=382>`__.
Cuyo manual del fabricante se encuentra `aquí <https://drive.google.com/open?id=1uDtgNkUCknkj3iTkykwhthjLoTGJCcea>`__

Explora la documentación, pero lee con mucho detalle hasta la página 5. NO abandones el documento hasta no
entender, es clave para realizar el RETO.

Ejercicio 2
#############
Recuerda el `API de arduino <https://www.arduino.cc/reference/en/language/functions/communication/serial/>`__
para el manejo del serial. En particular los siguientes métodos:

.. code-block:: cpp
   :lineno-start: 1

   Serial.available()
   Serial.read()
   Serial.readBytes(buffer, length)
   Serial.write()

Nota que la siguiente función no está en el repaso:

.. code-block:: cpp
   :lineno-start: 1
    
   Serial.readBytesUntil() 

La razón es que en un protocolo binario usualmente no tenemos
un carácter de fin de trama, como si ocurre con los protocolos
ASCII, donde usualmente el último carácter es un enter.

Analiza de nuevo el API, en particular los métodos resaltados.
NO SIGAS sin asegurarte que entiendes. Repasa los proyectos
previos.


Ejercicio 3
#############
Mira `este <https://drive.google.com/file/d/1iVr2Fiv8wXLqNyShr_EOplSvOJBIPqJP/view>`__
documento del fabricante del sensor. Podrás ver unos ejemplos de tramas. Utiliza
ScriptCommunicator para reproducir al menos un par de tramas. ¿Cuál es la idea? que
seas capaz de calcular el checksum tanto para transmitir como para recibir.

En el manual del sensor, el fabricante nos entrega el algoritmo para calcular el
checksum. Entiendes cómo utilizar este método? Si tienes dudas con algunos experimenta.

.. code-block:: cpp
   :lineno-start: 1

    unsigned int uiCrc16Cal(unsigned char const *pucY, unsigned char ucX)
    {
      const uint16_t PRESET_VALUE = 0xFFFF;
      const uint16_t POLYNOMIAL = 0x8408;
    
    
      unsigned char ucI, ucJ;
      unsigned short int uiCrcValue = PRESET_VALUE;
    
      for (ucI = 0; ucI < ucX; ucI++)
      {
        uiCrcValue = uiCrcValue ^ *(pucY + ucI);
        for (ucJ = 0; ucJ < 8; ucJ++)
        {
          if (uiCrcValue & 0x0001)
          {
            uiCrcValue = (uiCrcValue >> 1) ^ POLYNOMIAL;
          }
          else
          {
            uiCrcValue = (uiCrcValue >> 1);
          }
        }
      }
      return uiCrcValue;
    }

Actividad 3
^^^^^^^^^^^^^
* Fecha: septiembre 9 de 2020
* Descripción: ¿qué te parece si discutimos las dudas?
* Recursos: ingresa a Teams
* Duración de la actividad: 1 horas 20 minutos 
* Forma de trabajo: grupal

Ejercicio
##########
Vamos a repasar el protocolo binario del reto de la unidad 3.

Un posible modelo de la solución es este:

.. image:: ../_static/parcial2SM.jpg
   :scale: 100%
   :align: center

Y una posible implementación del modelo es este otro modelo en C++:

.. code-block:: cpp 
   :lineno-start: 1

    void setup() {
      Serial.begin(115200);
    }
    
    void taskCom() {
      enum class state_t {WAIT_INIT, WAIT_PACKET, WAIT_ACK};
      static state_t state = state_t::WAIT_INIT;
      static uint8_t bufferRx[20] = {0};
      static uint8_t dataCounter = 0;
      static uint32_t timerOld;
      static uint8_t bufferTx[20];
    
      switch (state) {
        case  state_t::WAIT_INIT:
          if (Serial.available()) {
            if (Serial.read() == 0x3E) {
              Serial.write(0x4A);
              dataCounter = 0;
              timerOld = millis();
              state = state_t::WAIT_PACKET;
            }
          }
    
          break;
    
        case state_t::WAIT_PACKET:
    
          if ( (millis() - timerOld) > 1000 ) {
            Serial.write(0x3D);
            state = state_t::WAIT_INIT;
          }
          else if (Serial.available()) {
            uint8_t dataRx = Serial.read();
            if (dataCounter >= 20) {
              Serial.write(0x3F);
              dataCounter = 0;
              timerOld = millis();
              state = state_t::WAIT_PACKET;
            }
            else {
              bufferRx[dataCounter] = dataRx;
              dataCounter++;
    
              // is the packet completed?
              if (bufferRx[0] == dataCounter - 1) {
    
                // Check received data
                uint8_t calcChecksum = 0;
                for (uint8_t i = 1; i <= dataCounter - 1; i++) {
                  calcChecksum = calcChecksum ^ bufferRx[i - 1];
                }
                if (calcChecksum == bufferRx[dataCounter - 1]) {
                  bufferTx[0] = dataCounter - 3; //Length
                  calcChecksum = bufferTx[0];
    
                  // Calculate Tx checksum
                  for (uint8_t i = 4; i <= dataCounter - 1; i++) {
                    bufferTx[i - 3] = bufferRx[i - 1];
                    calcChecksum = calcChecksum ^ bufferRx[i - 1];
                  }
    
                  bufferTx[dataCounter - 3] = calcChecksum;
                  Serial.write(0x4A);
                  Serial.write(bufferTx, dataCounter - 2);
                  timerOld = millis();
                  state = state_t::WAIT_ACK;
                }
                else {
                  Serial.write(0x3F);
                  dataCounter = 0;
                  timerOld = millis();
                  state = state_t::WAIT_PACKET;
                }
              }
            }
          }
    
          break;
    
        case state_t::WAIT_ACK:
          if ( (millis() - timerOld) > 1000 ) {
            timerOld = millis();
            Serial.write(bufferTx, dataCounter - 2);
          } else if (Serial.available()) {
            if (Serial.read() == 0x4A) {
              state = state_t::WAIT_INIT;
            }
          }
    
          break;
      }
    }
    
    
    void loop() {
      taskCom();
    }

Un ejemplo de una escenario de prueba:

.. image:: ../_static/vector1.jpg
   :scale: 100%
   :align: center

