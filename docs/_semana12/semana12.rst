Semana 12
===========

Retos de la semana pasada: RETO 1
----------------------------------
El primer reto de la semana pasada podría quedar así:

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

Tenga presente que este código no hace ninguna verificación de errores de entrada/salida,
por ejemplo:

* Se desconectó el sensor
* Se desconectó el sensor en medio de una transmisión y no llegan los datos completos.

Retos de la semana pasada: RETO 2
----------------------------------

.. code-block:: csharp
   :lineno-start: 1

    using System;
    using System.IO.Ports;
    using System.Threading;

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
            private static bool running = true;

            private static void counterCode()
            {
                int counter = 0;
                while (running)
                {
                    Thread.Sleep(1000);
                    Console.WriteLine(counter);
                    counter = (counter + 1) % 100;
                }
            }
            static void Main(string[] args)
            {

                Thread counterThread = new Thread(counterCode);
                counterThread.Start();


                // Allow the user to set the appropriate properties.
                _serialPort.PortName = "COM4";
                _serialPort.BaudRate = 57600;
                _serialPort.DtrEnable = true;
                _serialPort.Open();

                while (running)
                {
                    Console.WriteLine();
                    Console.WriteLine("Commands available: Q: 0x21, W: 0x24, E: 0x2F, R: 0x22, T: 0x28, Y: 0x25 X:exit");
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

                        case ConsoleKey.X:
                            running = false;
                            break;
                        default:
                            break;
                    }
                }
                counterThread.Join();
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


Integración con Unity
----------------------
Esta semana vamos a abordar la integración de sensores y actuadores o un motor como
Unity. Para ellos vamos a tomar como referencia un plugin para Unity llamado Ardity.

La guía de trabajo se encuentra 
`aquí <https://docs.google.com/presentation/d/1uHoIzJGHLZxLbkMdF1o_Ov14xSD3wP31-MQtsbOSa2E/edit?usp=sharing>`__

Ejercicio: RETO (está al final de la guía de trabajo)
------------------------------------------------------
Este reto es muy importante y consisten en estudiar a fondo el código fuente del plugin.
Es un reto grande porque posiblemente usted no recuerde algunas cosas de C# o nunca las
trabajó en un curso previo. Es por ello que el reto requiere que repase y estudie
algunas cosas nuevas.

Una vez haga el paso anterior:

* Cree un proyecto nuevo en Unity.
* Configure el soporte para el puerto serial tal como lo realizó en la guía.
* OJO, no instale el paquete Ardity. SI YA LO HIZO, vuelva a comenzar.
* Ahora tome únicamente LOS SCRIPTS de Ardity necesarios (SOLO LOS NECESARIOS)
  para hacer que la aplicación de la guía funcione de nuevo.

