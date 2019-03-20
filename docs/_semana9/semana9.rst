Semana 9
===========
Esta semanas abordaremos la construcción de aplicaciones que hagan uso de protocolos de comunicación ASCII para intercambiar 
información con sensores y/o actuadores.

En la primera sesión revisaremos dudas en la implementación del ejercicio 2 de la semana pasada. Luego analizaremos la 
biblioteca `ArduinoSerialCommand <https://github.com/scogswell/ArduinoSerialCommand>`__ 
escrita por Steven Cogswell y publicada el 23 de mayo de 2011. En 
`este <https://awtfy.com/2011/05/23/a-minimal-arduino-library-for-processing-serial-commands/>`__ sitio se puede leer la 
documentación inicial del proyecto.

En la segunda sesión realizaremos los siguientes ejercicios:

Ejercicio 1
------------
Este lo realizaremos de manera grupal.

* Abrir el código fuente de la biblioteca ArduinoSerialCommand.
* ¿Para qué sirven los siguientes macros: #define SERIALCOMMANDBUFFER 32, #define MAXSERIALCOMMANDS	10, #define MAXDELIMETER 2?
* ¿Para qué sirven los siguientes macros: #define SERIALCOMMANDDEBUG 1 #undef SERIALCOMMANDDEBUG?
* ¿Cuál es el API de la biblioteca?
* ¿Para qué sirven cada uno de los métodos del API de la biblioteca?
* En el constructor de la biblioteca: ¿Qué es el delimitador?
* En el constructor de la biblioteca: ¿Cómo hace la biblioteca para saber que ya se recibió un comando completo?
* ¿Cómo se borra el buffer de recepción de caracteres de un comando?
* ¿A qué se refiere la biblioteca con un token?
* Cuando se dice que la biblioteca devuelve un token ¿Qué devuelve exactamente?


Ejercicio 2
------------
* Instale la biblioteca ArduinoSerialCommand.
* Abra el ejemplo SerialCommandExample. Analice con detenimiento el funcionamiento del programa. Compare el programa con la 
  documentación de la biblioteca.
* ¿Cómo se accede a los argumentos de un comando?
* ¿Qué pasa si un comando no se reconoce?


Ejercicio 3
------------
* Abra el ejemplo SerialCommandHardwareOnlyExample. 
* Para qué sirve el macro SERIALCOMMAND_HARDWAREONLY que se encuentra en el archivo SerialCommand.h
* Abra el código fuente de la biblioteca y analice los efectos del macro anterior.

Ejercicio 4
-------------
Empleando la biblioteca, construya una aplicación en el arduino que responda a los siguientes comandos todos terminado con 
`\\n`

* red value
* green value
* blue value
* rgb valueRed valueGreen valueBlue

Tenga en cuenta que:

* value representará números enteros entre 0 y 255.
* Para probar el funcionamiento conecte un actuadore RGB (puede ser un LED).
* Si el arduino entiende el comando responderá con los caracteres `OK\\n`. En caso contrario no responderá nada.

Ejercicio 5
------------
* Investigue cómo hacer una aplicación en la herramienta processing o visual studio (C# aplicación gráfica) que envíe los 
  comandos anteriores al arduino. NO VAMOS A UTILIZAR UNITY por ahora (más adelante).
* La aplicación en la herramienta seleccionada debe tener interfaz gráfica para controlar los LEDs.
* La aplicación debe reportar si el arduino no responde a los comandos enviados.
* Como reto adicional: debe ser capaz de explicar cómo funciona cada línea de código empleada para construir la aplicación 
  en la herramienta seleccionada.