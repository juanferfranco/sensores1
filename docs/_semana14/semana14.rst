Semana 14
===========

..
  Esta semana vamos a continuar la exploración del paquete Ardity.

  Sesión 1
  ----------

  Ejercicio 1
  ^^^^^^^^^^^^
  ¿Qué excepciones se están considerando en el código?

  Ejercicio 2
  ^^^^^^^^^^^^
  ¿Qué pasa si no reciben datos por el puerto serial durante 100ms?

  Ejercicio 3
  ^^^^^^^^^^^^
  ¿Qué pasa si el cable serial se desconecta de manera inesperada?

  Ejercicio 4
  ^^^^^^^^^^^^^
  ¿Cómo se reestablece el funcionamiento de la aplicación?

  Ejercicio 5
  ^^^^^^^^^^^^^
  ¿Qué modificación tendríamos que hacer a la aplicación de arduino para
  reestablecer la comunicación?

  Sesión 2
  ----------

  Ejercicio 1
  ^^^^^^^^^^^^^
  ¿Qué modificación debemos realizar en el paquete Ardity si queremos
  soportar un nuevo protocolo de comunicación?

  RETO
  ^^^^^
  En la semana 11 trabajamos con un sensor que utilizaba un protocolo binario.
  `Este era el sensor <http://www.chafon.com/productdetails.aspx?pid=382>`__.
  Y su manual del fabricante se encuentra `aquí <https://drive.google.com/open?id=1uDtgNkUCknkj3iTkykwhthjLoTGJCcea>`__.
  Adicionalmente usamos `este <https://drive.google.com/file/d/1iVr2Fiv8wXLqNyShr_EOplSvOJBIPqJP/view>`__
  archivo de prueba enviado por el fabricante del sensor.

  El siguiente código simula el funcionamiento del sensor RFID para poder
  probar una aplicación interactiva que se conecte al sensor.

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

  La semana 12 presentamos una solución a los retos de la semana 11
  que buscaban conectar el sensor a una aplicación de consola usando
  C#.

  El siguiente código muestra cómo interactuar con el sensor desde una
  aplicación C#.

  .. code-block:: csharp
    :lineno-start: 1

      using System;
      using System.IO.Ports;

      namespace sem11Reto1
      {
          class Program
          {
              private static SerialPort _serialPort = new SerialPort();
              private static readonly byte[] q_commnad = new byte[] { 0x04, 0xFF, 0x21, 0x19, 0x95 };
              private static readonly byte[] w_commnad = new byte[] { 0x05, 0x00, 0x24, 0x00, 0x25, 0x29 };
              private static readonly byte[] e_commnad = new byte[] { 0x05, 0x00, 0x2F, 0x1E, 0x72, 0x34 };
              private static readonly byte[] r_commnad =  new byte[] { 0x06, 0x00, 0x22, 0x31, 0x80, 0xE1, 0x96 };
              private static readonly byte[] t_commnad =  new byte[] { 0x05, 0x00, 0x28, 0x05, 0x28, 0xD7 };
              private static readonly byte[] y_commnad = new byte[] { 0x05, 0x00, 0x25, 0x00, 0xFD, 0x30 };
              private static byte[] buffer = new byte[32];

              static void Main(string[] args)
              {
                  // Allow the user to set the appropriate properties.
                  _serialPort.PortName = "COM4";
                  _serialPort.BaudRate = 57600;
                  _serialPort.DtrEnable = true;
                  _serialPort.Open();

                  while (true)
                  {
                      Console.WriteLine();
                      Console.WriteLine("Commands available: Q: 0x21, W: 0x24, E: 0x2F, R: 0x22, T: 0x28, Y: 0x25");
                      switch (Console.ReadKey(true).Key)
                      {
                          case ConsoleKey.Q:
                              sendCommand(q_commnad);
                              readData();
                              break;
                          case ConsoleKey.W:
                              sendCommand(w_commnad);
                              readData();
                              break;

                          case ConsoleKey.E:
                              sendCommand(e_commnad);
                              readData();
                              break;
                          case ConsoleKey.R:
                              sendCommand(r_commnad);
                              readData();
                              break;

                          case ConsoleKey.T:
                              sendCommand(t_commnad);
                              readData();
                              break;

                          case ConsoleKey.Y:
                              sendCommand(y_commnad);
                              readData();
                              break;

                          default:
                              break;
                      }

                  
                  }
              }

              private static void sendCommand(byte[] data)
              {
                  Console.Write("Send this packet: ");
                  for(int i = 0; i < data.Length; i++)
                  {
                      Console.Write("{0:X2}",data[i]);
                      Console.Write(' ');
                  }
                  Console.WriteLine();
                  _serialPort.Write(data, 0, data.Length);
              }

              private static void readData()
              {
                  // 1. Este llamado bloque completamente el hilo
                  // esperando a que lleguen datos por el puerto serial
                  while (_serialPort.BytesToRead == 0) ;

                  // 2. Leo el primer byte que me dice la longitud
                  _serialPort.Read(buffer, 0, 1);
                  // 3. Espero el resto de datos
                  while (_serialPort.BytesToRead < buffer[0]) ;

                  // 4. Leo los datos
                  _serialPort.Read(buffer, 1, buffer[0]);

                  // 5. Verifica el checksum
                  bool checksumOK = verifyChecksum(buffer);
                  Console.Write("Packet received: ");
                  for(int i = 0; i < (buffer[0] + 1); i++)
                  {
                      Console.Write("{0:X2}", buffer[i]);
                      Console.Write(' ');

                  }
                  if(checksumOK == false)
                  {
                      Console.WriteLine(" Checksum Fails");
                  }
                  else
                  {
                      Console.WriteLine();
                  }

              }

              private static bool verifyChecksum(byte[] packet)
              {
                  bool checksumOK = false;
                  byte ucI, ucJ;

                  int uiCrcValue = 0x0000FFFF;
                  int len = packet[0] + 1;

                  for (ucI = 0; ucI < (len - 2); ucI++)
                  {
                      uiCrcValue = uiCrcValue ^ packet[ucI];
                      for (ucJ = 0; ucJ < 8; ucJ++)
                      {
                          if ((uiCrcValue & 0x00000001) == 0x00000001)
                          {
                              uiCrcValue = (uiCrcValue >> 1) ^ 0x00008408;
                          }
                          else
                          {
                              uiCrcValue = (uiCrcValue >> 1);
                          }
                      }
                  }

                  int LSBCkecksum = uiCrcValue & 0x000000FF;
                  int MSBCkecksum = (uiCrcValue & 0x0000FF00) >> 8;

                  if ((packet[len - 2] == LSBCkecksum) && (packet[len - 1] == MSBCkecksum)) checksumOK = true;
                  return checksumOK;
              }

          }
      }

  El reto entonces consiste en realizar la integración del sensor, pero esta vez
  al motor Unity, modificando el paquete Ardity para que pueda soportar este nuevo
  protocolo.