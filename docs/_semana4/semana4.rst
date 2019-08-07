Semana 4
===========
A continuación se muestra el reto de la semana anterior:

.. code-block:: c 
   :lineno-start: 1

    const unsigned long TIMEOUT = 1000;

    void setup() {
        Serial.begin(115200);
    }

    void loop() {
        static unsigned long oldTime = 0;
        static bool ledState = false;

    //  unsigned long initTime = micros();
    
        unsigned long newTime = millis();
        if (newTime - oldTime >= TIMEOUT) {
            oldTime = newTime;
            if(true == ledState)Serial.println("LED OFF");
            else Serial.println("LED ON");
            ledState = !ledState;
        //    Serial.print("Loop takes: ");
        //    Serial.print(micros() - initTime);
        //    Serial.println(" us");
        }
    }

Note en el código la palabra reservada static. En este caso las variables marcadas con el
modificador static le indican al compilador que oldTime y ledState DEBEN ser privadas a la
función loop, es decir, no podrán ser accedidas por fuera de loop; sin embargo, estas 
variables no estarán definidas en el stack a diferencia de la variable newTime que si estará
definida allí. ¿Y esto qué implica? Pues que cada vez que se retorne de la función loop 
el valor de newTime será perderá, en cambio oldTime y ledState conservarán siempre el 
último valor almacenado.

Lo que haremos esta semana
---------------------------
Esta semana realizaremos dos ejercicios para introducir la técnica de programación de 
máquinas de estado.

Ejercicio 1
------------
Una experiencia interactiva posee un sensor que produce mucho ruido eléctrico cuando 
cambia de estado. La siguiente figura muestra una transición, capturada con un 
osciloscopio, donde puede apreciarse el fenómeno.

.. image:: ../_static/bounce.jpg

En la figura se observa el ruido generado en la transición de la señal del estado alto 
al estado bajo; sin embargo, el mismo fenómeno ocurre al cambiar del estado bajo al alto. 
Note que además pueden ocurrir falsos positivos en la señal, que se manifiestan 
como pulsos de muy corta duración.

Un ingeniero electrónica experto informa que podemos considerar que el sensor ha 
cambiado de estado cuando la señal esté estable por lo menos durante 100 ms sin ruido y 
sin falsos positivos.

Se debe realizar una aplicación que filtre el comportamiento ruidoso del sensor y 
reporte por un puerto serial únicamente los valores 
estables de este así: ``1`` cuando el sensor cambie de 0 a 1 y ``0`` cuando cambien de 
1 a 0.

Ejercicio 2
------------
Se requiere construir una aplicación para controlar una bomba de tiempo. La siguiente 
figura ilustra la interfaz de la bomba. El circuito de control de la bomba está compuesto 
por tres sensores (botones: UP, DOWN, ARM), un display (LCD) y una salida para 
activar la bomba. Los sensores son digitales al igual que la salida de activación de la 
bomba. El display posee una interfaz de comunicación serial (lo simularemos con el PC). 
El controlador funciona así: 

.. image:: ../_static/bomb.png

* Inicia en modo de configuración, es decir, no cuenta aún, el conteo regresivo 
  está ``desarmado``. El valor incial del conteo regresivo es de 20 segundos.
* En el modo de configuración, los botones UP y DOWN permiten aumentar o disminuir el 
  timpo inicial de la bomba.
* El tiempo se puede programar entre 10 y 60 segundos con cambios de 1 segundo. 
* El tiempo de configuración se debe visualizar en el LCD (enviamos el 
  valor al PC).
* El botón ARM arma la bomba.
* Una vez armada la bomba, comienza la cuenta regresiva que será visualizada en el LCD en
  por medio de una cuenta regresiva en segundos.
* La bomba explotará (se activa la salida de activación de la bomba) cuando el tiempo 
  llegue a cero. En este punto el control regreserá al modo de configuración.
* Una vez la bomba esté armada es posible desactivarla ingresando un código de seguridad. 
  El código será la siguiente secuencia de botones presionados uno después de otro: 
  UP, DOWN, DOWN, UP, UP, ARM.
* Si la secuencia se ingresa correctamente el controlador pasará de nuevo al modo de 
  configuración de lo contrario continuará la fatal cuenta regresiva.
