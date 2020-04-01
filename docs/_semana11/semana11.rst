Semana 11
===========

Esta semana vamos a abordar la integración de sensores
y actuadores con aplicaciones interactivas escritas en C#
mediante el uso de protocolos binarios.

Sesión 1
----------
Para aprender los detalles de manejo de lo protocolos binarios
vamos a realizar una serie de ejercicios que nos permitan
entender y practicar con pequeños retos los asuntos relacionados
con el manejo de los protocolos binarios.

Ejercicio 1
^^^^^^^^^^^^^
¿Cómo se ve un protocolo binario?

Para responder esta pregunta vamos a utilizar como ejemplo
`este sensor <http://www.chafon.com/productdetails.aspx?pid=382>`__.
Cuyo manual del fabricante se encuentra `aquí <https://drive.google.com/open?id=1uDtgNkUCknkj3iTkykwhthjLoTGJCcea>`__


Ejercicio 2
^^^^^^^^^^^^
Recordemos el `API de arduino <https://www.arduino.cc/reference/en/language/functions/communication/serial/>`__
para el manejo del serial. En particular los siguientes métodos:

.. code-block:: cpp
   :lineno-start: 1

   Serial.available()
   Serial.read()
   Serial.readBytes(buffer, length)
   Serial.write()

Note que la siguiente función no está en el repaso:

.. code-block:: cpp
   :lineno-start: 1
    
   Serial.readBytesUntil() 

La razón es que en un protocolo binario usualmente no tenemos
un carácter de fin de trama, como si ocurre con los protocolos
ASCII, donde usualmente el último carácter es un enter.

Ejercicio 3
^^^^^^^^^^^^^
¿Cómo hacemos para lidiar con protocolos binarios?

Para responder esta pregunta tomemos como base el protocolo binario
del sensor RFID y `este <https://drive.google.com/file/d/1iVr2Fiv8wXLqNyShr_EOplSvOJBIPqJP/view>`__
archivo de prueba enviado por el fabricante del sensor.

El siguiente código simula el funcionamiento del sensor RFID para poder
probar una aplicación interactiva que se conecte al sensor.

Vamos a analizar cada parte del código y las técnicas de programación
que vemos allí.

.. code-block:: cpp
   :lineno-start: 1

    #include <Arduino.h>
    //#define DEBUG
    #ifdef DEBUG
    #define DEBUG_PRINT(msg,value) Serial.print(msg); Serial.println(value)
    #else
    #define DEBUG_PRINT(msg,value)
    #endif
    
    void TaskReadCommand();
    unsigned int uiCrc16Cal(unsigned char const *, unsigned char);
    void parseCommad(uint8_t *);
    
    void setup()
    {
      Serial.begin(57600);
    }
    
    void loop()
    {
      TaskReadCommand();
    }
    
    void TaskReadCommand()
    {
      enum class serialStates {
        waitLen,
        waitData
      };
      
      static auto state = serialStates::waitLen;
      static uint8_t buffer[32] = {0};
      static uint8_t dataCounter = 0;
    
      switch (state)
      {
        case serialStates::waitLen: // wait for the first byte: len
    
          if (Serial.available())
          {
            buffer[dataCounter] = Serial.read();
            dataCounter++;
            state = serialStates::waitData;
            DEBUG_PRINT("Go to rx data", "");
          }
          break;
    
        case serialStates::waitData: // read data
          while (Serial.available())
          {
            buffer[dataCounter] = Serial.read();
            dataCounter++;
    
            if (dataCounter == (buffer[0] + 1))
            { // if all bytes arrived
              // verify the checksum
              DEBUG_PRINT("Verify the checksum", "");
              DEBUG_PRINT("dataCount: ",´ dataCounter);
              if (dataCounter >= 5)
              {
                unsigned int checksum = uiCrc16Cal(buffer, dataCounter - 2);
                uint8_t lsBChecksum = (uint8_t)(checksum & 0x000000FF);
                uint8_t msBChecksum = (uint8_t)((checksum & 0x0000FF00) >> 8);
                if ((lsBChecksum == buffer[dataCounter - 2]) && (msBChecksum == buffer[dataCounter - 1]))
                {
                  DEBUG_PRINT("ChecksumOK", "");
                  parseCommad(buffer);
                }
              }
              dataCounter = 0;
              state = serialStates::waitLen;
              DEBUG_PRINT("Go to rx len", "");
            }
          }
          break;
      }
    }
    
    
    
    void parseCommad(uint8_t *pdata)
    {
      uint8_t command = pdata[2];
      static uint8_t command21[] = {0x0D, 0x00, 0x21, 0x00, 0x02, 0x44, 0x09, 0x03, 0x4E, 0x00, 0x1E, 0x0A, 0xF2, 0x16};
      static uint8_t command24[] = {0x05, 0x00, 0x24, 0x00, 0x25, 0x29};
      static uint8_t command2F[] = {0x05, 0x00, 0x2F, 0x00, 0x8D, 0xCD};
      static uint8_t command22[] = {0x05, 0x00, 0x22, 0x00, 0xF5, 0x7D};
      static uint8_t command28[] = {0x05, 0x00, 0x28, 0x00, 0x85, 0x80};
      static uint8_t command25[] = {0x05, 0x00, 0x25, 0x00, 0xFD, 0x30};
    
    
      switch (command)
      {
        case 0x21:
          Serial.write(command21, sizeof(command21));
          break;
        case 0x24:
          Serial.write(command24, sizeof(command24));
          break;
    
        case 0x2F:
          Serial.write(command2F, sizeof(command2F));
          break;
    
        case 0x22:
          Serial.write(command22, sizeof(command22));
          break;
    
        case 0x28:
          Serial.write(command28, sizeof(command28));
          break;
    
        case 0x25:
          Serial.write(command25, sizeof(command25));
          break;
      }
    }
    
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

Ejercicio 4
^^^^^^^^^^^^
A veces cuando trabajamos con protocolos binarios es necesario
transmitir variables que tienen una longitud mayor a un byte.
Por ejemplo, los números en punto flotante cumplen con el
`estándar IEEE754 <https://www.h-schmidt.net/FloatConverter/IEEE754.html>`__
y se representan con 4 bytes.

Algo que debemos decidir al trabajar con número como los anteriormente
descritos es el orden en cual serán transmitidos sus bytes. En principio
tenemos dos posibilidades: transmitir primero el byte de menor peso (little endian)
o transmitir primero el byte de mayor peso (big endian). Al diseñar un protocolo
binario deberemos escoger una de las hos posibilidades.

Ejercicio 5
^^^^^^^^^^^^
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

Ejercicio 6
^^^^^^^^^^^^
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

Ejercicio 7
^^^^^^^^^^^^
Y ahora cómo lidiamos con el protocolo binario del sensor 
de RFID desde la aplicación interactiva?

En la semana 9 ya habíamos dado algunas pistas, es decir,
ya sabemos hacer varias cosas:

* Inicializar el puerto
* Enviar bytes
* Saber si hay datos en el puerto serial
* Leer los bytes

Por ejemplo, el siguiente código utiliza las cosas que ya
sabemos usar y permite leer los bytes que se están enviando
desde el arduino con el código del ejercicio 6.

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
                    byte[] buffer = new byte[20];

                    while(true){
                        if(_serialPort.BytesToRead > 0){
                            _serialPort.Read(buffer,0,20);
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

Ejercicio 8
^^^^^^^^^^^^
Y si queremos que la aplicación interactiva lea los 4 bytes y lo
convierta al número en punto flotante?

Pero antes de comenzar, ¿En qué endian se envía el número en punto flotante
del ejercicio 6?

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
                    byte[] buffer = new byte[20];

                    while(true){
                        if(_serialPort.BytesToRead >= 4){
                            _serialPort.Read(buffer,0,20);
                            
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


Sesión 2
----------
En esta sesión realizaremos un reto con protocolos binarios
que permita comunicar un sensor con una aplicación interactiva.

El reto consiste en ser capaz de reproducir el archivo de prueba
que provee el fabricante del sensor de RFID. El archivo se encuentra
`aquí <https://drive.google.com/file/d/1iVr2Fiv8wXLqNyShr_EOplSvOJBIPqJP/view>`__.

Para ello vamos a programar un arduino para simular el sensor (vale un millón
de pesos el sensor) y vamos programar una aplicación interactiva en C# desde
la cual enviaremos comandos al sensor tal como aparecen en el archivo de
prueba.

No olviden calcular y verificar el checksum en Arduino y en C#.