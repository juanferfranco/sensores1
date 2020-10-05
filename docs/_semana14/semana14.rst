Semana 14:  Unidad 6
======================

Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Actividad 1
^^^^^^^^^^^^^
* Fecha: octubre 5 de 2020
* Descripción: solución de dudas en tiempo real con el docente 
* Recursos: ingresa a Teams
* Duración de la actividad: 1 hora , 20 minutos. 
* Forma de trabajo: grupal


Ejercicio 1
###############
La semana pasada dejamos este minireto para realizar

* Crea un proyecto nuevo en Unity.
* Configura el soporte para el puerto serial tal como lo viste en la guía.
* OJO, no instales el paquete Ardity. SI YA LO HICISTE, vuelva a comenzar.
* Ahora toma únicamente LOS SCRIPTS de Ardity necesarios (SOLO LOS NECESARIOS)
  para hacer que la aplicación de la guía funcione de nuevo.

¿Vemos los resultados obtenidos?

Ejercicio 2
##############
Este ejercicio, de repaso, te propone una nueva iteración al estudio
de la aplicación demo de la semana pasada.

Primero, vamos a analizar rápidamente el código de arduino:

.. code-block:: cpp
   :lineno-start: 1

    uint32_t last_time = 0;
    
    void setup()
    {
        Serial.begin(9600);
    }
    
    void loop()
    {
        // Print a heartbeat
        if ( (millis() - last_time) >  2000)
        {
            Serial.println("Arduino is alive!!");
            last_time = millis();
        }
    
        // Send some message when I receive an 'A' or a 'Z'.
        switch (Serial.read())
        {
            case 'A':
                Serial.println("That's the first letter of the abecedarium.");
                break;
            case 'Z':
                Serial.println("That's the last letter of the abecedarium.");
                break;
        }
    }

Consideraciones a tener presentes con este código:

* La velocidad de comunicación es de 9600. Esa misma velocidad se tendrá que configurar
  del lado de Unity para que ambas partes se puedan entender.
* Nota que no estamos usando la función delay(). Estamos usando millis para medir tiempos
  relativos. Nota que cada dos segundos estamos enviando un mensaje indicando que el
  arduino está activo:  ``Arduino is alive!!``
* Observa que el buffer del serial se lee constantemente. NO estamos usando
  el método available() que usualmente utilizamos. ¿Recuerdas lo anterior? Con available()
  nos aseguramos que el buffer de recepción tiene al menos un byte para leer; 
  sin embargo, cuando usamos Serial.read() sin verificar antes que tengamos datos en el
  buffer, es muy posible que el método devuelva un -1 indicando que no había nada en el
  buffer de recepción. NO OLVIDES ESTO POR FAVOR.
* Por último nota que todos los mensajes enviados por arduino usan el método println.
  ¿Y esto por qué es importante? porque println enviará la información que le pasemos
  como argumento, codificada en ASCII, y adicionará al final 2 bytes: 0x0D y 0x0A. Estos
  bytes serán utilizados por Ardity para detectar que la cadena enviada por Arduino está completa.
  NO OLVIDES VERIFICAR LO ANTERIOR, si no logras identificarlo habla con el profe.

Ahora analicemos la parte de Unity/Ardity. Para ello, carguemos una de las escenas ejemplo:
DemoScene_UserPoll_ReadWrite

.. image:: ../_static/scenes.jpg
   :scale: 100%
   :align: center

Nota que la escena tiene 3 gameObjects: Main Camera, SerialController y SampleUserPolling_ReadWrite.

Veamos el gameObject SampleUserPolling_ReadWrite. Este gameObject tiene dos components, un transform
y un script. El script tiene el código como tal de la aplicación del usuario.

.. image:: ../_static/user_code.jpg
   :scale: 100%
   :align: center

Nota que el script expone una variable pública: serialController. Esta variable es del tipo SerialController.

.. image:: ../_static/serialControllerVarCode.jpg
   :scale: 100%
   :align: center

Esa variable nos permite almacenar la referencia a un objeto tipo SerialController. ¿Donde estaría ese
objeto? Pues cuando el gameObject SerialController es creado nota que uno de sus componentes es un objeto
de tipo SerialController:

.. image:: ../_static/serialControllerGO_Components.jpg
   :scale: 100%
   :align: center

Entonces desde el editor de Unity podemos arrastrar el gameObject SerialController al campo SerialController
del gameObject SampleUserPolling_ReadWrite y cuando se despliegue la escena, automáticamente se inicializará
la variable serialController con la referencia en memoria al objeto SerialController:

.. image:: ../_static/serialControllerUnityEditor.jpg
   :scale: 100%
   :align: center

De esta manera logramos que el objeto SampleUserPolling_ReadWrite tenga acceso a la información
del objeto SerialController.

Observemos ahora qué datos y qué comportamientos tendría un objeto de tipo SampleUserPolling_ReadWrite:

.. code-block:: csharp
   :lineno-start: 1

    /**
     * Ardity (Serial Communication for Arduino + Unity)
     * Author: Daniel Wilches <dwilches@gmail.com>
     *
     * This work is released under the Creative Commons Attributions license.
     * https://creativecommons.org/licenses/by/2.0/
     */

    using UnityEngine;
    using System.Collections;

    /**
     * Sample for reading using polling by yourself, and writing too.
     */
    public class SampleUserPolling_ReadWrite : MonoBehaviour
    {
        public SerialController serialController;

        // Initialization
        void Start()
        {
            serialController = GameObject.Find("SerialController").GetComponent<SerialController>();

            Debug.Log("Press A or Z to execute some actions");
        }

        // Executed each frame
        void Update()
        {
            //---------------------------------------------------------------------
            // Send data
            //---------------------------------------------------------------------

            // If you press one of these keys send it to the serial device. A
            // sample serial device that accepts this input is given in the README.
            if (Input.GetKeyDown(KeyCode.A))
            {
                Debug.Log("Sending A");
                serialController.SendSerialMessage("A");
            }

            if (Input.GetKeyDown(KeyCode.Z))
            {
                Debug.Log("Sending Z");
                serialController.SendSerialMessage("Z");
            }


            //---------------------------------------------------------------------
            // Receive data
            //---------------------------------------------------------------------

            string message = serialController.ReadSerialMessage();

            if (message == null)
                return;

            // Check if the message is plain data or a connect/disconnect event.
            if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_CONNECTED))
                Debug.Log("Connection established");
            else if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_DISCONNECTED))
                Debug.Log("Connection attempt failed or disconnection detected");
            else
                Debug.Log("Message arrived: " + message);
        }
    }

Vamos a realizar una prueba. Pero antes configuremos el puerto serial en el cual está conectado
el arduino. El arduino ya debe estar corriendo el código de muestra del sitio web del plugin.

.. image:: ../_static/serialControllerCOM.jpg
   :scale: 100%
   :align: center

En este caso el puerto es COM4.

Corre el programa, abre la consola y selecciona la ventana Game del Editor de Unity. Con la ventana
seleccionada (click izquierdo del mouse), escribe las letras A y Z. Notarás los mensajes que aparecen
en la consola:

.. image:: ../_static/unityConsole.jpg
   :scale: 100%
   :align: center

Una vez la aplicación funcione nota algo en el código de SampleUserPolling_ReadWrite:

.. code-block:: csharp
   :lineno-start: 1

    serialController = GameObject.Find("SerialController").GetComponent<SerialController>();

Comenta esta línea y corre la aplicación de nuevo. Funciona?

Ahora, elimina el comentario de la línea y luego borra la referencia al SerialController
en el editor de Unity:

.. image:: ../_static/removeSerialControllerUnityEditor.jpg
   :scale: 100%
   :align: center

Corre de nuevo la aplicación.

* ¿Qué puedes concluir?
* ¿Para qué incluyó esta línea el autor del plugin?

Ahora analicemos el código del método Update de SampleUserPolling_ReadWrite:

.. code-block:: csharp
   :lineno-start: 1

    // Executed each frame
    void Update()
    {
      .
      .
      .
      serialController.SendSerialMessage("A");
      .
      .
      .
      string message = serialController.ReadSerialMessage();
      .
      .
      .
    }

¿Recuerdas cada cuánto se llama el método Update? 

Update se llama en cada frame. Lo llama automáticamente el motor de Unity

Nota los dos métodos que se resaltan:

.. code-block:: csharp
   :lineno-start: 1

    serialController.SendSerialMessage("A");
    string message = serialController.ReadSerialMessage();

Ambos métodos se llaman sobre el objeto cuya dirección en memoria está guardada en
la variable serialController.

El primer método permite enviar la letra A y el segundo permite recibir una cadena
de caracteres.

* ¿Cada cuánto se envía la letra A o la Z?
* ¿Cada cuánto leemos si nos llegaron mensajes desde el arduino?

Ahora vamos a analizar cómo transita la letra A desde el SampleUserPolling_ReadWrite hasta
el arduino.

Para enviar la letra usamos el método SendSerialMessage de la clase SerialController. Observa
que la clase tiene dos variables protegidas importantes:

.. image:: ../_static/serialControllerUMLClass.jpg
   :scale: 35%
   :align: center

.. code-block:: csharp
   :lineno-start: 1

   protected Thread thread;
   protected SerialThreadLines serialThread;

Con esas variables vamos a administrar un nuevo hilo y vamos a almacenar una referencia 
a un objeto de tipo SerialThreadLines.

En el método onEnable de SerialController tenemos:

.. code-block:: csharp
   :lineno-start: 1

   serialThread = new SerialThreadLines(portName, baudRate, reconnectionDelay, maxUnreadMessages);
   thread = new Thread(new ThreadStart(serialThread.RunForever));
   thread.Start();

Aquí vemos algo muy interesante, el código del nuevo hilo que estamos creando será RunForever y
ese código actuará sobre los datos del objeto cuya referencia está almacenada en serialThread.

Vamos a concentrarnos ahora en serialThread que es un objeto de la clase SerialThreadLines:

.. code-block:: csharp
   :lineno-start: 1

    public class SerialThreadLines : AbstractSerialThread
    {
        public SerialThreadLines(string portName,
                                 int baudRate,
                                 int delayBeforeReconnecting,
                                 int maxUnreadMessages)
            : base(portName, baudRate, delayBeforeReconnecting, maxUnreadMessages, true)
        {
        }

        protected override void SendToWire(object message, SerialPort serialPort)
        {
            serialPort.WriteLine((string) message);
        }

        protected override object ReadFromWire(SerialPort serialPort)
        {
            return serialPort.ReadLine();
        }
    }

Al ver este código no se observa por ningún lado el método RunForever, que es el código
que ejecutará nuestro hilo. ¿Dónde está? Observe que SerialThreadLines también es un
AbstractSerialThread. Entonces es de esperar que el método RunForever esté en la clase
AbstractSerialThread.

Por otro lado nota que para enviar la letra A usamos el método SendSerialMessage también
sobre los datos del objeto reverenciado por serialThread del cual ya sabemos que es un
SerialThreadLines y un AbstractSerialThread

.. code-block:: csharp
   :lineno-start: 1

    public void SendSerialMessage(string message)
    {
        serialThread.SendMessage(message);
    }

Al igual que RunForever, el método SendMessage también está definido en AbstractSerialThread.

Veamos entonces ahora qué hacemos con la letra A:

.. code-block:: csharp
   :lineno-start: 1

    public void SendMessage(object message)
    {
        outputQueue.Enqueue(message);
    }

Este código nos da la clave. Lo que estamos haciendo es guardar la letra A 
que queremos transmitir en una COLA. Esta estructura de datos permite 
PASAR información de un HILO a otro HILO.

¿Cuáles hilos?

Pues tenemos en este momento dos hilos: el hilo del motor y el nuevo hilo que creamos antes.
El hilo que ejecutará el código RunForever sobre los datos del objeto de tipo
SerialThreadLines:AbstractSerialThread. Por tanto, observa que la letra A la estamos
guardando en la COLA del SerialThreadLines:AbstractSerialThread

Si observas con detenimiento el código de RunForever:

.. code-block:: csharp
   :lineno-start: 1

    public void RunForever()
    {
        try
        {
            while (!IsStopRequested())
            {
                ...
                try
                {
                    AttemptConnection();
                    while (!IsStopRequested())
                        RunOnce();
                }
                catch (Exception ioe)
                {
                ...
                }
            }
        }
        catch (Exception e)
        {
        ...
        }
    }

Los detalles están en RunOnce():

.. code-block:: csharp
   :lineno-start: 1

    private void RunOnce()
    {
        try
        {
            // Send a message.
            if (outputQueue.Count != 0)
            {
                SendToWire(outputQueue.Dequeue(), serialPort);
            }
            object inputMessage = ReadFromWire(serialPort);
            if (inputMessage != null)
            {
                if (inputQueue.Count < maxUnreadMessages)
                {
                    inputQueue.Enqueue(inputMessage);
                }
            }
        }
        catch (TimeoutException)
        {
        }
    }

Y en este punto vemos finalmente qué es lo que pasa: para enviar la letra
A, el código del hilo pregunta si hay mensajes en la cola. Si los hay,
nota que el mensaje se saca de la cola y se envía:

.. code-block:: csharp
   :lineno-start: 1

   SendToWire(outputQueue.Dequeue(), serialPort);

Si buscamos el método SendToWire en AbstractSerialThread vemos:

.. code-block:: csharp
   :lineno-start: 1
   
   protected abstract void SendToWire(object message, SerialPort serialPort);

Y aquí es donde se conectan las clases SerialThreadLines con AbstractSerialThread, ya
que el método SendToWire es abstracto, SerialThreadLines tendrá que implementarlo

.. code-block:: csharp
   :lineno-start: 1

    public class SerialThreadLines : AbstractSerialThread
    {
        ...
        protected override void SendToWire(object message, SerialPort serialPort)
        {
            serialPort.WriteLine((string) message);
        }
        ...
    }

Aquí vemos finalmente el uso de la clase SerialPort de C# con el método
`WriteLine <https://docs.microsoft.com/en-us/dotnet/api/system.io.ports.serialport.writeline?view=netframework-4.8>`__ 

Finalmente, para recibir datos desde el serial, ocurre el proceso contrario:

.. code-block:: csharp
   :lineno-start: 1


    public class SerialThreadLines : AbstractSerialThread
    {
        ...
        protected override object ReadFromWire(SerialPort serialPort)
        {
            return serialPort.ReadLine();
        }
    }

`ReadLine <https://docs.microsoft.com/en-us/dotnet/api/system.io.ports.serialport.readline?view=netframework-4.8>`__
también es la clase SerialPort. Si leemos cómo funciona ReadLine queda completamente claro la razón de usar otro
hilo:

.. warning::

  Remarks
  Note that while this method does not return the NewLine value, the NewLine value is removed from the input buffer.

  By default, the ReadLine method will block until a line is received. If this behavior is undesirable, set the
  ReadTimeout property to any non-zero value to force the ReadLine method to throw a TimeoutException if
  a line is not available on the port.

Por tanto, volviendo a RunOnce:

.. code-block:: csharp
   :lineno-start: 1

    private void RunOnce()
    {
        try
        {
            if (outputQueue.Count != 0)
            {
                SendToWire(outputQueue.Dequeue(), serialPort);
            }

           object inputMessage = ReadFromWire(serialPort);
            if (inputMessage != null)
            {
                if (inputQueue.Count < maxUnreadMessages)
                {
                    inputQueue.Enqueue(inputMessage);
                }
                else
                {
                    Debug.LogWarning("Queue is full. Dropping message: " + inputMessage);
                }
            }
        }
        catch (TimeoutException)
        {
            // This is normal, not everytime we have a report from the serial device
        }
    }

Vemos que se envía el mensaje: 

.. code-block:: csharp
   :lineno-start: 1

    SendToWire(outputQueue.Dequeue(), serialPort);

Y luego el hilo se bloquea esperando por una respuesta:

.. code-block:: csharp
   :lineno-start: 1

    object inputMessage = ReadFromWire(serialPort);

Nota que primero se envía y luego el hilo se bloquea. NO SE DESBLOQUEARÁ HASTA que no envíe
una respuesta desde Arduino o pasen 100 ms que es el tiempo que dura bloqueada la función
antes de generar una excepción de timeout de lectura.

¿Cómo sabemos que son 100 ms? 

Mira con detenimiento el código. La siguiente línea te dará una pista.

.. code-block:: csharp
   :lineno-start: 1

   // Amount of milliseconds alloted to a single read or connect. An
    // exception is thrown when such operations take more than this time
    // to complete.
    private const int readTimeout = 100;

Actividad 2
^^^^^^^^^^^^^
* Fecha: octubre 5 a octubre 7 de 2020
* Descripción: trabaja en el ejercicio 2. Asegúrate de entenderlo por favor.
  Aprovecha para repasar los conceptos de programación orientada a objetos
  que no recuerdes.
* Recursos: mira los ejercicios abajo.
* Duración de la actividad: 5 horas. 
* Forma de trabajo: individual

Actividad 3
^^^^^^^^^^^^^
* Fecha: octubre 7 de 2020
* Descripción: MINI RETO EN CLASE.
* Recursos: ingresa a Teams
* Duración de la actividad: 1 hora , 20 minutos. 
* Forma de trabajo: grupal

Trabaja en el siguiente mini-reto y aprovecha al profesor para resolver
dudas en tiempo real.

* Crea un proyecto nuevo en Unity.
* Configura el soporte para el puerto serial tal como lo viste en la guía.
* OJO, no instales el paquete Ardity. SI YA LO HICISTE, vuelva a comenzar.
* Ahora toma únicamente LOS SCRIPTS de Ardity PERO sin destruir la arquitectura 
  planteada por el autor. 
* Ahora implementa el protocolo binario de la unidad anterior (el sensor RFID).
