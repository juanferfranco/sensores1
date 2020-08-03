Semana 6
===========

Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Fase 6 (RETO-continuación)
^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: agosto 10 de 2020 - 2 p.m. 
* Descripción: procede con la solución del reto.
* Recursos: para abordar el reto de programación te recomiendo que tengas a la mano el siguiente material

  * Ingresa al grupo de `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__.
    para resolver dudas en tiempo real con el docente.
  * Continua trabajando en el RETO en tus horas de trabajo autónomas.

* Duración de la actividad: 
  
  * 1 hora 40 minutos con solución de dudas en tiempo real.
  * 3 horas de trabajo autónomo

* Forma de trabajo: individual.


Fase 7 (sustentación):
^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: agosto 10,11 y 12 de 2020
* Descripción: realiza el video de sustentación.
* Recursos: para realizar el video de sustentación te recomiendo los siguientes recursos
  
  * Software para capturar `OBS Studio <https://obsproject.com/>`__.
  * Ver `este <https://www.youtube.com/watch?time_continue=3&v=1tuJjI7dhw0>`__
    tutorial para el manejo de OBS Studio.

* Duración de la actividad: 2 horas de trabajo autónomo
* Forma de trabajo: individual

Fase 8 (retroalimentación): 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: agosto 12 de 2020 - 2 p.m.
* Descripción: encuentro sincrónico para compartir y discutir los resultados del RETO. 
* Recursos: ingresa al grupo de `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__
* Duración de la actividad: 
  
  * 50 minutos de discusión.
  * 50 minutos para que hagas las acciones de mejora sobre tu trabajo.

* Forma de trabajo: colaborativo con solución de dudas en tiempo real y trabajo individual en la acción de mejora.

Criterios de evaluación
------------------------
1. Criterio: integro dispositivos de entrada-salida con sistemas de cómputo para la
   creación de sistemas intermediados por el entretenimiento digital (Materialización).

2. Criterio: aplico los conceptos necesarios para el correcto diseño, implementación,
   funcionamiento y 
   diagnóstico del software en la producción de sistemas de entretenimiento digital utilizando los procedimientos y herramientas adecuadas según el contexto (Ingeniería de software).

Esta actividad tendrá un porcentaje sumativo del 15% en la nota final.

..
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





