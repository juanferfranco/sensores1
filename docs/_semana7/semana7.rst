Semana 7
===========

Sesión 1
----------
En esta sesión realizaremos la retroalimentación del parcial número 2.

Un posible modelo de la solución es este:

.. image:: ../_static/parcial2SM.jpg

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


Sesión 2
---------
Hasta este punto del curso, la aplicación interactiva que se
comunica con el sensor/actuador la hemos simulando con
una terminal ascii (monitor de arduino) o una terminal binaria
(Coolterm); sin embargo, ha llegado el momento de abordar los
problemas de integración que se deben enfrentar a la hora de
escribir aplicaciones interactivas que interactúan en tiempo real
con el contenido digital y con información proveniente de sensores.

En este punto aparece un mundo de posibilidades relacionadas con
el origen del sensor, es decir, el sensor puede estar conectado
a la misma plataforma de cómputo en la cual corre la aplicación
interactiva o puede estar en otra plataforma de cómputo
independiente. Adicionalmente, las plataformas de cómputo pueden
estar conectadas por medios alambrados o inalámbricos; pueden estar
en el mismo espacio o incluso en cualquier lugar del planeta.

En sensores 1 nos concentraremos en la comunicación entre la
aplicación interactiva y el sensor conectados a través de un puerto
serial. En sensores 2 abordaremos las otras posibilidades mencionadas.

Para comenzar esta exploración debemos introducir algunos conceptos
traídos de los sistemas operativos: procesos, hilos, espacios de memoria
virtual, máquinas virtuales. Además, usaremos como plataforma de
experimentación Unity y por tanto C#.

Vamos a presentar el concepto de hilo y la relación entre otros
conceptos estudiados en la carrera relativos a la programación orientada
a objetos. Para ello vamos a revisar partes de `este <http://www.albahari.com/threading/>`__
sitio y `esta <https://drive.google.com/file/d/1kYL85ThVU5xJmCiCPDVskS-UI4Y5jDde/view?usp=sharing>`__
presentación de Samy Zafrany tomada de `este <https://samyzaf.com/braude/OS/index.html>`__
sitio.

Vamos a complementar con el material de estos sitios:

* `¿Qué es el .NET? <https://dotnettutorials.net/lesson/dotnet-framework/>`__
* `¿Qué es el CLR? <https://dotnettutorials.net/lesson/common-language-runtime-dotnet/>`__
* `¿Cómo se ejecuta un programa .NET? <https://dotnettutorials.net/lesson/dotnet-program-execution-process/>`__

Y de estos otros, que muestran la relación con Unity:

* `IL2CPP <https://docs.unity3d.com/Manual/IL2CPP.html>`__
* `¿Cómo funciona IL2CPP <https://docs.unity3d.com/Manual/IL2CPP.html>`__
