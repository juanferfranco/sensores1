Semana 7 : UNIDAD 4
====================

Propósitos de aprendizaje
--------------------------

Construir aplicaciones interactivas utilizando múltiples hilos
para la producción y el prototipado de experiencias interactivas.

Integrar controladores con aplicaciones interactivas mediante
el uso de protocolos seriales ascii.

Actividad de aprendizaje
-------------------------

Se realizará las SEMANAS 7, 8 y 9 (agosto 17/agosto 24/agosto 31).

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
Debes realizar un sistema interactivo compuesto por una aplicación en el PC y
un controlador al cual se conectan varios sensores y actuadores.

Para el controlador tienes:

* Dos sensores digitales
* Dos sensores analógicos: valores de 0 a 1023
* Dos actuadores digitales.
* Dos actuadores analógicos (pwm)

El controlador se conecta a un computador a través del puerto USB y se comunica 
utilizando la interfaz Serial.

Realiza un programa, para le controlador, que haga las siguientes tareas 
concurrentes:

* Recibir comandos a través de la interfaz Serial
* Enciende y apaga un LED a una frecuencia de 10 Hz
* Enciende y apaga un LED a una frecuencia de 5 Hz.

Los comandos recibidos por el puerto serial serán los siguientes:

* read D1. Este comando hace que se envíe al PC el valor del sensor digital 1. 
  El controlador devuelve la cadena:  D1 estado. Donde estado puede ser 1 o 0.

* read D2: enviar al PC el valor del sensor digital 2.  
  El controlador devuelve la cadena: D2 estado. Donde estado puede ser 1 o 0.

* read A1: enviar el PC el valor del sensor analógico 1.  
  El controlador devuelve la cadena A1 valor. Donde valor está entre 0 y 1023.

* read A2: enviar el PC el valor del sensor analógico 2. 
  El controlador devuelve la cadena A2 valor. Donde valor está entre 0 y 1023.

* write O1 estado: donde estado puede ser 1 o 0. 
  Activa o desactiva la salida digital 1 

* write O2 estado: donde estado puede ser 1 o 0. 
  Activa o desactiva la salida digital 2 

* write P1 valor: donde valor puede ser de 0 a 255. 
  Escribir un valor de PWM igual a valor en el actuador analógico 1. 

* write P2 valor: donde valor puede ser de 0 a 255. 
  Escribir un valor de PWM igual a valor en el actuador analógico 2.

La aplicación interactiva en el PC es tipo consola en C# y debe tener:

* Dos hilos.
* Un hilo debe imprimir cada 100 ms el valor de un contador.
* El otro hilo estará atento a los eventos del teclado producidos por el usuario.
* Asigne una tecla a cada comando que será enviado al controlador.
* Indicar si el controlador entendió o no entendió el comando, es decir,
  mostrar el NACK o el ACK (abajo la explicación de esto)

.. note::

  Para cualquiera de los comandos tipo write el controlador debe devolver los caraceres
  ACK si reconoce el comando y NACK si no los reconoce. 

  Debes decidir, dados los requisitos
  de la aplicación, si requieres introducir caracteres de nueva línea y/o retorno de carro. 
  TEN PRESENTE que LOS LEDs deben funcionar SIEMPRE a 5 Hz y 10 HZ como se declaró previamente, 
  ese decir, su funcionamiento no puede ser interrumpido por las operaciones del puerto serial


¿Qué debes entregar?
^^^^^^^^^^^^^^^^^^^^^

.. warning::
  * Crea una carpeta, la llamaremos principal. 
  * Guarda allí el proyecto para el controlador y el proyecto para la aplicación
    interactiva.
  * En la carpeta principal guarda una copia de la rúbrica con tu autoevaluación.
  * Comprime la carpeta principal en formato .ZIP
  * Entrega el archivo .ZIP `aquí <https://auladigital.upb.edu.co/mod/assign/view.php?id=487305>`__.

¿Qué deberás tener en cuenta para la sustentación?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* La sustentación se realizará en la última sesión de esta unidad.
* Tendrá una duración máxima de 10 minutos. Allí mostrarás: el funcionamiento y explicarás
  cómo realizaste las pruebas, qué problemas tuviste, cómo los solucionaste.
* Estudia muy bien tu solución y prepárate para responder algunas preguntas. 
* Ten en cuenta la rúbrica para preparar tu sustentación.

Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Fase 1 (motivación)
^^^^^^^^^^^^^^^^^^^^^^

* Fecha: agosto 17 de 2020 - 2 p.m.
* Descripción: asiste al encuentro sincrónico donde se introducirá la actividad de
  aprendizaje de la unidad 4 correspondiente a las semanas 7, 8 y 9.
* Recursos: ingresa al grupo de `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__
* Duración de la actividad: 20 minutos sincrónicos.
* Forma de trabajo: grupal

Fase 2 (diagnóstico-repaso)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: agosto 17 de 2020 - 2:30 p.m
* Descripción: lee las preguntas y ejercicios orientadores para autoevaluar si tienes
  los conocimientos necesarios para abordar el RETO.
* Recursos: 

  * Realiza `esta guía <https://docs.google.com/presentation/d/1AyKBtJ3QKP-Qsuv8qFn9Azz4jPwjxEodjj5MLBXLy60/edit?usp=sharing>`__.
  * Ingresa al grupo de `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__
    para que resuelvas tus dudas en tiempo real con el docente.

* Duración de la actividad: 1 hora 10 minutos
* Forma de trabajo: individual con solución de dudas en tiempo real

Fase 3 (fundamentación)
^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: agosto 17 de 2020
* Descripción: realiza las lecturas donde se explican los fundamentos conceptuales de la plataforma de software utilizada para 
  la construcción de los programas del controlador.
* Recursos: lee `este blog <http://www.albahari.com/threading/>`__ hasta la la sección que dice Join and Sleep
  y reproduce de manera analítica los ejemplos que están allí.
* Duración de la actividad: 1 hora de trabajo autónomo 
* Forma de trabajo: individual

Fase 4 (ejercicios y discusión)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: agosto 18 de 2020
* Descripción: realiza los ejercicios propuestos. Acuerda reuniones con tus compañeros para trabajar de manera *colaborativa*
* Recursos: 

  * realiza estos :ref:`ejercicios`.

* Duración de la actividad: 4 horas de trabajo autónomo y colaborativo. Acuerda reuniones con tus compañeros.
* Forma de trabajo: individual y colaborativa.

Fase 5 (retroalimentación): 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: agosto 19 de 2020 - 2 p.m.
* Descripción: encuentro sincrónico para compartir y discutir los ejercicios. 
* Recursos: 
  
  * Ingresar al grupo de `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__
  * Corrige tus ejercicios (acciones de mejora)

* Duración de la actividad: 50 minutos de discusión y 50 minutos para que hagas
  las acciones de mejora sobre tu trabajo.
* Forma de trabajo: colaborativo con solución de dudas en tiempo real y 
  trabajo individual en la acción de mejora.

.. _ejercicios:

Ejercicios
--------------

Ejercicio 1
^^^^^^^^^^^^^
Hasta este punto del curso hemos utilizado .NET para la construcción de aplicaciones
interactivas. En este ejercicio te propongo que indagues un poco más sobre la plataforma
de software que estamos usando:

* `¿Qué es el .NET? <https://dotnettutorials.net/lesson/dotnet-framework/>`__
* `¿Qué es el CLR? <https://dotnettutorials.net/lesson/common-language-runtime-dotnet/>`__
* `¿Cómo se ejecuta un programa .NET? <https://dotnettutorials.net/lesson/dotnet-program-execution-process/>`__

Ejercicio 2
^^^^^^^^^^^^^
Al finalizar el curso estaremos utilizando el motor Unity para construir aplicaciones interactivas
a las que se integren sensores y actuadores.

Profundiza un poco más sobre la relación entre .NET, código compilado y Unity:

* `IL2CPP <https://docs.unity3d.com/Manual/IL2CPP.html>`__
* `¿Cómo funciona IL2CPP <https://docs.unity3d.com/Manual/IL2CPP.html>`__

Ejercicio 3
^^^^^^^^^^^^^^
La idea del ejercicio es comunicar a través del puerto serial
el computador con un controlador, en este caso un ESP32. Recuerda que la 
aplicación del computador será tipo consola .NET framework.

Estudia con detenimiento el código para el controlador y para el computador.

* ¿Quién debe comenzar primero, el compu o el controlador? ¿Por qué?

.. warning::

  SOLO PARA LOS MÁS CURIOSOS: microsoft está en proceso de unificación
  de su plataforma .NET y .NET core. Te dejo aquí los pasos para que
  configures tu aplicación tipo .NET core

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

Programa el arduino con este código:

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

Y este es el código para el computador:

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

Ejercicio 4
^^^^^^^^^^^^
Ahora programa tanto el controlador como el PC con los siguientes
códigos.

NO OLVIDES! analiza el código con detenimiento, entiéndelo.

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

* Conecta el controlador.
* Modifica el código del computador asignando el puerto
  serial correcto.
* Corra el código del computador.
* Al presionar cualquier tecla qué pasa?

Ejercicio 5
^^^^^^^^^^^^^^^^^^
Te diste cuenta que al presionar una tecla, el conteo se detiene
un momento?

Al construir aplicaciones interactivas no te puedes dar este lujo.
Piensa en esto: ¿Y si en vez de imprimir un contador estás
renderizando una escena? Por tanto, las comunicaciones con el
controlador y el proceso de impresión del contador en la pantalla deben
ser dos flujos independientes, es decir, dos hilos.

¿Quieres intentarlo tu mismo?

.. warning::
  Alerta de spoiler

  El siguiente código muestra una posible solución al reto

.. code-block:: csharp
  :lineno-start: 1

    using System;
    using System.IO.Ports;
    using System.Threading;

    namespace SerialTest
    {
        class Program
        {
            static void Main(string[] args)
            {

                int counter = 0;

                Thread t = new Thread(readKeyboard);
                t.Start();

                while (true)
                {
                    Console.WriteLine(counter);
                    counter = (counter + 1) % 100;
                    Thread.Sleep(100);
                }
            }

            static void readKeyboard()
            {

                SerialPort _serialPort = new SerialPort(); ;
                _serialPort.PortName = "COM4";
                _serialPort.BaudRate = 115200;
                _serialPort.DtrEnable = true;
                _serialPort.Open();

                byte[] data = { 0x31 };

                while (true) {     
                    if (Console.KeyAvailable == true)
                    {
                        Console.ReadKey(true);
                        _serialPort.Write(data, 0, 1);
                        string message = _serialPort.ReadLine();
                        Console.WriteLine(message);
                    }
                }
            }
        }
    }


