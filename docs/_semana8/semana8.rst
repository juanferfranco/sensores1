Semana 8
===========

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

Sesión 1
----------

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

Sesión 2
----------

Ejercicio 1
^^^^^^^^^^^^

Un ejercicio extra para comenzar a calentar, sin hilos aún.
La idea del ejercicio es comunicar a través del puerto serial
el computador con un arduino, en este caso, un ESP32. Si desea
trabajar en visual studio solo se requiere crear una aplicación
.NET framework tipo consola. En caso de utilizar .netcore se pueden
seguir los siguientes pasos en la terminal:

* mkdir dotNetTest
* cd dotNetTest
* dotnet new console
* En la siguiente línea, antes de versión tenemos doble guión. Ojo se ve como
  un solo guión, pero son dos.
* dotnet add package System.IO.Ports --version 4.7
* code .
* copiar el código
* dotnet build
* dotnet run

Este es el código para programar en el arduino:

.. code-block:: cpp
   :lineno-start: 1

    void setup() {
      Serial.begin(115200);
    }

    void loop() {

      if(Serial.available()){
        if(Serial.read() == '1'){
          Serial.print("Hello from ESP32");
        }
      }
    }


Este es el código para programar en el computador:

.. code-block:: csharp
   :lineno-start: 1

    using System;
    using System.IO.Ports;

    namespace hello_serialport{
        class Program{
            static void Main(string[] args)
            {
                SerialPort _serialPort = new SerialPort();
                // Allow the user to set the appropriate properties.
                _serialPort.PortName = "/dev/ttyUSB0";
                _serialPort.BaudRate = 115200;
                _serialPort.DtrEnable = true;
                _serialPort.Open();
                byte[] data = {0x31};
                _serialPort.Write(data,0,1);
                byte[] buffer = new byte[20];

                while(true){
                    if(_serialPort.BytesToRead > 0){
                        _serialPort.Read(buffer,0,20);
                        Console.WriteLine(System.Text.Encoding.ASCII.GetString(buffer));
                        Console.ReadKey();
                        _serialPort.Write(data,0,1);
                    }
                }
            }
        }
    }

Ejercicio 2
^^^^^^^^^^^^
Este es el código para programar en el arduino:

.. code-block:: cpp
   :lineno-start: 1

    void setup() {
      Serial.begin(115200);
    }

    void loop() {

      if(Serial.available()){
        if(Serial.read() == '1'){
          delay(1000);
          Serial.print("Hello from ESP32\n");
        }
      }
    }

Este es el código para programar el computador

.. code-block:: cpp
   :lineno-start: 1

    using System;
    using System.IO.Ports;
    using System.Threading;

    namespace serialTestBlock
    {
    class Program{
            static void Main(string[] args)
            {
                SerialPort _serialPort = new SerialPort();
                _serialPort.PortName = "/dev/ttyUSB0";
                _serialPort.BaudRate = 115200;
                _serialPort.DtrEnable = true;
                _serialPort.Open();

                byte[] data = {0x31};
                byte[] buffer = new byte[20];
                int counter = 0;

                while(true){
                    if(Console.KeyAvailable == true){
                        Console.ReadKey(true);
                        _serialPort.Write(data,0,1);
                        string message = _serialPort.ReadLine();
                        Console.WriteLine(message);
                    }
                    Console.WriteLine(counter);
                    counter = (counter + 1) % 100;
                    Thread.Sleep(100);
                } 
            }   
        }
    }

* Conecte el arduino.
* Modifique el código del computador asignando el puerto
  serial correcto.
* Corra el código del computador.
* Al presionar cualquier tecla qué pasa?

Ejercicio 3: Reto
^^^^^^^^^^^^^^^^^^
Con lo que hemos discutido hoy cómo podríamos solucionar el
problema anterior, considerando que no es posible (por el
ejercicio académico) modificar el código de Arduino?

