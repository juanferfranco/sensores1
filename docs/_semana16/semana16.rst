Semana 16: Unidad 6 
=======================

Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Actividad 1
^^^^^^^^^^^^^
* Fecha: octubre 19 de 2020
* Descripción: Evaluación final
* Recursos: ingresa a Teams
* Duración de la actividad: 1 hora , 40 minutos. 
* Forma de trabajo: individual

Evaluación final
#################

Construye una aplicación interactiva (AI), utilizando Unity-Ardity,
que tendrá que comunicarse con un controlador que posee varios sensores y actuadores. 

Considera:

* El protocolo de integración es BINARIO.
* Deberás extender la funcionalidad de Ardity heredando de la clase
  AbstractSerialThread.
* La AI iniciará la comunicación cuando el usuario pulse la tecla ``s``.
* Puedes usar el paquete del escenario de prueba que encuentras más abajo.
* Muestra en la Consola de Unity los paquetes que estás transmitiendo
  y qué paquetes estás recibiendo.
* La secuencia de bytes más grande será de 20 bytes.
* COMPRIME la carpeta del proyecto de Unity en formato .ZIP (OJO, solo .ZIP)
* Entrega tu evaluación `aquí <https://auladigital.upb.edu.co/mod/assign/view.php?id=487316>`__.

PASOS para realizar la comunicación:

1. La AI inicia una transacción enviando el byte 3E.
2. El controlador deberá responder con el byte 4A.
3. La AI no podrá continuar hasta no recibir la respuesta del controlador.
   Una vez el controlador responda, la AI enviará al controlador
   un paquete de bytes así:

.. code-block:: cpp
   :lineno-start: 1

    Byte 1 : longitud
    Byte 2 : Dirección
    Byte 3 : Comando
    Byte 4 a n : Datos
    Byte n+1: verificacion

* El byte de longitud, es el primer byte de la trama e indica cuántos bytes la AI
  enviará a continuación, es decir, la cantidad de bytes a enviar
  comprendidos desde el byte 2 hasta el byte n + 1.
* La AI calculará el byte de verificación así: Byte1 XOR Byte2 XOR … XOR ByteN.

4. El controlador esperará hasta un 1 segundo a que la trama llegue. Si esta condición
   NO se cumple el controlador enviará a la AI el byte 3D. La AI deberá iniciar de
   nuevo la secuencia de comunicación desde el paso 1. 
  
   Una vez el controlador tenga la trama completa calculará el byte de verificación
   de la misma manera que la AI lo hizo. El resultado debe ser igual al bytes de verificación
   recibido. Sí el byte de verificación calculado no corresponde al byte de verificación
   recibido, el controlador enviará el byte 3F y la AI deberá reenviar la trama. 
   Sí hay coincidencia en la verificación, el controlador deberá responder a la AI con 
   el byte 4A y luego enviar la siguiente secuencia de bytes:

.. code-block:: cpp
   :lineno-start: 1

    Byte 1 : longitud
    Byte 2 : Byte4 recibido
    Byte m : Byten recibido
    Byte m+1 : verificación

5. Si la AI recibe correctamente el paquete deberá responder con el byte 4A. 
   El controlador quedará preparado para volver al paso 1, es decir, esperar por una nueva
   trama. Si ha pasado 1 segundo y el controlador no recibe el 4A, entonces deberá
   retransmitir el paquete a la AI. Este comportamiento solo se detendrá hasta que la
   AI envíe el 4A.


Este es un posible modelo de solución para el controlador:

.. image:: ../_static/SM_model.jpg
   :scale: 80%
   :align: center

Y una posible implementación del modelo para el controlador
es este otro modelo en C++:

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

.. image:: ../_static/scenario1.jpg
   :scale: 100%
   :align: center


Actividad 2
^^^^^^^^^^^^^
* Fecha: octubre 19 a octubre 21 de 2020
* Descripción: prepara la sustentación de la evaluación final
* Recursos: mira los ejercicios abajo.
* Duración de la actividad: 5 horas. 
* Forma de trabajo: individual

Actividad 3
^^^^^^^^^^^^^
* Fecha: octubre 21 de 2020
* Descripción: sustentación de la evaluación final
* Recursos: debes estar pendiente de la llamada del docente
  por medio de Teams.
* Duración de la actividad: 1 hora , 40 minutos. 
* Forma de trabajo: individual

