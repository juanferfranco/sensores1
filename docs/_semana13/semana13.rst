Semana 13: Unidad 6
======================

Propósitos de aprendizaje
--------------------------
En esta unidad 6 abordaremos la última parte del curso. Vamos
a utilizar todo lo aprendido hasta ahora para aprender
cómo integrar sensores y actuadores a herramientas de software
para la construcción de aplicaciones interactivas.


Código de honor
----------------

Para realizar las actividades y el RETO de evaluación se espera que hagas
lo siguiente:

* Colabora con tus compañeros cuando así se indique.
* Trabaja de manera individual cuando la actividad así te lo
  proponga.
* Usa solo la documentación oficial del framework del controlador,
  .NET de Microsoft y Unity
* NO DEBES utilizar sitios en Internet con soluciones o ideas para
  abordar el problema.
* NO DEBES hacer uso de foros.
* ¿Entonces qué hacer si no me funciona algo? Te propongo que
  experimentes, crea hipótesis, experimenta de nuevo, observa y concluye.
* NO OLVIDES, este curso se trata de pensar y experimentar NO de
  BUSCAR soluciones en Internet.
* VAMOS A TENER SESIONES sincrónicas donde podrás trabajar y resolver
  dudas en tiempo real con el docente.

Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Actividad 1
^^^^^^^^^^^^^
* Fecha: septiembre 28 de 2020
* Descripción: vamos a introducir la unidad. 
* Recursos: ingresa a Teams
* Duración de la actividad: 1 hora , 20 minutos. 
* Forma de trabajo: grupal


Reto de la Unidad anterior sin hilos
#######################################

Te dejo una propuesta de solución al reto de la
unidad anterior. Primero sin el hilo que imprime el contador
y luego con ese hilo.

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

* ¿Qué pasa si el sensor se desconecta?
* ¿Qué pasa si el sensor se desconecta en medio de una transmisión 
   y no llegan los datos?

Ahora adicionamos el hilo que muestra el contador cada 100 ms

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
#######################
Para realizar la integración, vamos a utilizar un plugin para Unity llamada
Ardity. Sin embargo, vamos a analizar este plugin completamente hasta entender
cada una de sus partes.

La guía de trabajo se encuentra 
`aquí <https://docs.google.com/presentation/d/1uHoIzJGHLZxLbkMdF1o_Ov14xSD3wP31-MQtsbOSa2E/edit?usp=sharing>`__


Actividad 2
^^^^^^^^^^^^^
* Fecha: septiembre 28 a septiembre 30 de 2020
* Descripción: realiza los ejercicios propuestos.
* Recursos: mira los ejercicios abajo.
* Duración de la actividad: 5 horas. 
* Forma de trabajo: individual

Ejercicio 1
###############
Al final de la guía te dejo un MINI-RETO. Este consiste en estudiar a fondo
el código fuente del plugin. Es un reto grande porque posiblemente tengas que 
recordar algunas de tus cursos anteriores de programación en el programa.
Es por ello que el mini-reto requiere que repases y estudies algunas cosas nuevas.

Una vez hagas el paso anterior:

* Crea un proyecto nuevo en Unity.
* Configura el soporte para el puerto serial tal como lo viste en la guía.
* OJO, no instales el paquete Ardity. SI YA LO HICISTE, vuelva a comenzar.
* Ahora toma únicamente LOS SCRIPTS de Ardity necesarios (SOLO LOS NECESARIOS)
  para hacer que la aplicación de la guía funcione de nuevo.

Actividad 3
^^^^^^^^^^^^^
* Fecha: septiembre 30 de 2020
* Descripción: realiza los ejercicios propuestos con soporte
  del docente para resolver dudas en tiempo real.
* Recursos: ingresa a Teams
* Duración de la actividad: 1 hora , 20 minutos. 
* Forma de trabajo: grupal

En esta sesión vamos a terminar el material de esta semana y a resolver dudas
de la actividad final de análisis de Ardity.