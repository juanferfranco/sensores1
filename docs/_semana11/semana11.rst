Semana 11: Unidad 5
=======================

Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Actividad 4
^^^^^^^^^^^^^
* Fecha: septiembre 14 de 2020
* Descripción: Te propondré otros ejercicios complementarios
  que necesitarás para afrontar otros protocolos binarios
* Recursos: ingresa a Teams
* Duración de la actividad: 1 hora , 20 minutos. 
* Forma de trabajo: grupal

Ejercicio 1
#############

Analicemos el siguiente asunto:

Cuando trabajamos con protocolos binarios es necesario
transmitir variables que tienen una longitud mayor a un byte.
Por ejemplo, los números en punto flotante cumplen con el
`estándar IEEE754 <https://www.h-schmidt.net/FloatConverter/IEEE754.html>`__
y se representan con 4 bytes.

Algo que debemos decidir al trabajar con número como los anteriormente
descritos es el orden en cual serán transmitidos sus bytes. En principio
tenemos dos posibilidades: transmitir primero el byte de menor peso (little endian)
o transmitir primero el byte de mayor peso (big endian). Al diseñar un protocolo
binario deberemos escoger una de las dos posibilidades.

Ejercicio 2
#############
¿Cómo transmitir un número de 16 bits?

.. code-block:: cpp
   :lineno-start: 1

    void setup() {
      Serial.begin(115200);
    
    }
    
    void loop() {
      //vamos a transmitir el 16205
      
      static uint16_t x = 0x3F4D;  
    
      if (Serial.available()) {
        if (Serial.read() == 's') {
          Serial.write((uint8_t)( x & 0x00FF));
          Serial.write( (uint8_t)( x >> 8 ));
        }
      }
    }    

* ¿Qué endian estamos utilizando en este caso?

Ejercicio 3
#############
¿Cómo transmitir un número en punto flotante?

Veamos dos maneras:

.. code-block:: cpp
   :lineno-start: 1

    void setup() {
        Serial.begin(115200);
    }
    
    void loop() {
        // 45 60 55 d5
        // https://www.h-schmidt.net/FloatConverter/IEEE754.html
        static float num = 3589.3645;
     
        if(Serial.available()){
            if(Serial.read() == 's'){
                Serial.write ( (uint8_t *) &num,4);
            }
        }
    }

Es posible que queramos copiar los bytes que componen el número
previamente en un arreglo:


.. code-block:: cpp
   :lineno-start: 1


    void setup() {
        Serial.begin(115200);
    }
    
    void loop() {
        // 45 60 55 d5
        // https://www.h-schmidt.net/FloatConverter/IEEE754.html
        static float num = 3589.3645;
        static uint8_t arr[4] = {0};
    
        if(Serial.available()){
            if(Serial.read() == 's'){
                memcpy(arr,(uint8_t *)&num,4);
                Serial.write(arr,4);
            }
        }
    }

* ¿En qué endian estamos transmitiendo el número?

* Y si queremos transmitir en el endian contrario?

.. code-block:: cpp
   :lineno-start: 1

    void setup() {
        Serial.begin(115200);
    }
    
    void loop() {
        // 45 60 55 d5
        // https://www.h-schmidt.net/FloatConverter/IEEE754.html
        static float num = 3589.3645;
        static uint8_t arr[4] = {0};
    
        if(Serial.available()){
            if(Serial.read() == 's'){
                memcpy(arr,(uint8_t *)&num,4);
                for(int8_t i = 3; i >= 0; i--){
                  Serial.write(arr[i]);  
                }
            }
        }
    }

Ejercicio 4
#############
Y ahora cómo lidiamos con el protocolo binario del sensor 
de RFID desde la aplicación interactiva?

Ya habíamos dado algunas pistas, es decir,
ya sabemos hacer varias cosas:

* Inicializar el puerto
* Enviar bytes
* Saber si hay datos en el puerto serial
* Leer los bytes

Por ejemplo, el siguiente código utiliza las cosas que ya
sabemos usar y permite leer los bytes que se están enviando
desde el arduino (toma el ejercicio anterior).

.. code-block:: csharp
   :lineno-start: 1

    using System;
    using System.IO.Ports;

    namespace serialRFID
    {
        class Program{
                static void Main(string[] args)
                {
                    SerialPort _serialPort = new SerialPort();
                    // Allow the user to set the appropriate properties.
                    _serialPort.PortName = "/dev/ttyUSB0";
                    _serialPort.BaudRate = 115200;
                    _serialPort.DtrEnable = true;
                    _serialPort.Open();
                    byte[] data = {0x73};
                    _serialPort.Write(data,0,1);
                    byte[] buffer = new byte[4];

                    while(true){
                        if(_serialPort.BytesToRead >= 4){
                            _serialPort.Read(buffer,0,4);
                            for(int i = 0;i < 4;i++){
                                Console.Write(buffer[i].ToString("X2") + " ");
                            }
                            Console.ReadKey();
                            _serialPort.Write(data,0,1);
                        }
                    }
                }
            }
    }

Ejercicio 5
#############
Y si queremos que la aplicación interactiva lea los 4 bytes y lo
convierta al número en punto flotante?

Pero antes de comenzar, ¿En qué endian se envía el número en punto flotante
del ejercicio 3?

.. code-block:: csharp
   :lineno-start: 1

    using System;
    using System.IO.Ports;

    namespace serialRFID
    {
        class Program{
                static void Main(string[] args)
                {
                    SerialPort _serialPort = new SerialPort();
                    // Allow the user to set the appropriate properties.
                    _serialPort.PortName = "/dev/ttyUSB0";
                    _serialPort.BaudRate = 115200;
                    _serialPort.DtrEnable = true;
                    _serialPort.Open();
                    byte[] data = {0x73};
                    _serialPort.Write(data,0,1);
                    byte[] buffer = new byte[4];

                    while(true){
                        if(_serialPort.BytesToRead >= 4){
                            _serialPort.Read(buffer,0,4);
                            
                            for(int i = 0;i < 4;i++){
                                Console.Write(buffer[i].ToString("X2") + " ");
                            }
                            Console.WriteLine();

                            Console.WriteLine(System.BitConverter.ToSingle(buffer,0));
                            byte [] bufferReverse = new byte[4];
                            for(int i = 3; i>= 0; i--) bufferReverse[3-i] = buffer[i];
                            Console.WriteLine(System.BitConverter.ToSingle(bufferReverse,0));    

                            Console.ReadKey();
                            _serialPort.Write(data,0,1);
                        }
                    }
                }
            }
    }

Actividad 5
^^^^^^^^^^^^^
* Fecha: septiembre 14 a septiembre 16 de 2020
* Descripción: Repasa todo los visto hasta ahora
* Recursos: material semana 10 y 11
* Duración de la actividad: 5 horas
* Forma de trabajo: individual

Actividad 6
^^^^^^^^^^^^^
* Fecha: septiembre 16 de 2020
* Descripción: sigamos aclarando dudas. ¿Ya estás preparado
  para el reto?
* Recursos: ingresa a Teams
* Duración de la actividad: 1 hora 40 minutos.
* Forma de trabajo: grupal.