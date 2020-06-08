Semana 2
===========

Propósito de aprendizaje
--------------------------

Analizar la plataforma de hardware y software del controlador que se empleará
como interfaz entre los sensores-actuadores y las plataformas de software
interactivas a utilizar en el curso.

Construir aplicaciones simples para el controlador con el fin de explorar algunas
posibilidades y características de su plataforma de software.


Actividad de aprendizaje
-------------------------
Se realizará las SEMANA 2 y 3 de julio 13 al 24.

Lee con detenimiento el código de honor y luego los pasos que debes seguir
para evidenciar esta actividad.

Código de honor
----------------
Para realizar este reto se espera que hagas lo siguiente:

* Colabora con tus compañeros cuando así se indique.
* Trabaja de manera individual cuando la actividad así te lo proponga.
* Usa solo la documentación oficial del framework del controlador y .NET de Microsoft.
* NO DEBES utilizar sitios en Internet con soluciones o ideas para abordar el problema.
* NO DEBES hacer uso de foros.
* ¿Entonces qué hacer si no me funciona algo? Te propongo que experimentes, crea hipótesis,
  experiementa de nuevo, observa y concluye.
* NO OLVIDES, este curso se trata de pensar y experimentar NO de BUSCAR soluciones
  en Internet.

Actividad de aprendizaje
-------------------------

Enunciado: 
^^^^^^^^^^^
Debes controlar el funcionamiento algunos sensores, actuadores y tareas desde el computador.

* Debes crear dos aplicaciones: una para el PC y otra para tu controlador.
* La aplicación del PC la debes realizar usando Visual Studio y será 
  del tipo Consola con .NET framework.
* La aplicación del PC y del controlador interacturán por medio de un modelo
  cliente servidor. La aplicación del PC será el cliente y la del controlador el servidor.
* Para la aplicación del controlador: 

  * Crea 4 tareas concurrentes. 
  * La tarea uno encederá y apagará continuamente un LED a 1 Hz;
    la tarea 2 otro LED a 5 Hz; la tarea 3 otro LED a 7Hz; la tarea 4 recibirá comandos
    para leer un sensor digital, leer un sensor analógico, modificar un actuador digital,
    modificar un actuador analógico por PWM.

* En la aplicación del PC debes solicitarle al usuario comandos para interactuar con la
  aplicación del controlador:

  * Un comando para modificar la frecuencia de cada una de las tareas 1, 2 y 3. Debes
    especificar la tarea y la frecuencia.
  * Para la tarea 4 define comandos que te permitan seleccionar el sensor/actuador y los
    valores respectivos.

* Ten presente que solo podrás comunicarte con el controlador una vez tengas toda la información,
  es decir, no debes hacer envíos parciales.
* El PC preguntará si se deseas continuar con la aplicación o terminar.

¿Qué debes entregar?
^^^^^^^^^^^^^^^^^^^^^^

* Crea una carpeta principal. Guarda allí dos carpetas más, cada uno con el proyecto para el PC
  y para el controlador. Guarda los proyectos completos. Adicionalmente,
  en la carpeta principal guarda un archivo .pdf donde colocarás cuatro cosas:
  
  * La versión de Visual Studio utilizada.
  * La versión del software para programar el controlador.
  * UN ENLACE a tu ONE DRIVE donde estará alojado el video de sustentación.
  * Una tabla de contenidos que indique el instante de tiempo en el cual se pueden encontrar
    cada una de las sesiones siguientes.

¿Qué deberá tener el video de sustentación?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Máximo 20 minutos: debes planear el video tal como aprendiste en segundo semestre
  en tu curso de narrativa audiovisual.
* Cuida la calidad del audio y del video.
* Sección 1: introducción, donde dirás tu nombre y si realizaste el RETO
  completo. Si no terminaste indica claramente qué te faltó y por qué.
* Sección 2: muestra que tus dos programas compilan correctamente y sin errores
  o advertencias problemáticas.
* Sección 3: Realiza una demostración del funcionamiento donde ilustres todos los
  aspectos solicitados.
* Define un conjuntos de vectores de prueba donde indiques los datos de entrada y el
  resultado esperado.
* Aplica los vectores de prueba y muestra que si producen los valores esperados.
* Sección 4: explica la arquitectura de las aplicaciones. Utiliza una
  aplicación de `WhiteBoard <https://www.microsoft.com/en-us/microsoft-365/microsoft-whiteboard/digital-whiteboard-app>`__
  para esto.
* Tus explicaciones deben ser claras, precisas y completas. No olvides planear 
  bien tu video de sustentación.
* Debes explicar las partes de la aplicación, la función que realiza cada parte y
  sus propiedades.
* Debes explicar las relaciones entre las partes, cómo funcionan esas relaciones y
  sus propiedades
* Sección 5: protocolo de integración entre las aplicaciones.
* Debes explicar claramente cómo se comunicarán tus aplicaciones.
* Muestra de manera detallada los pasos que deben realizar cada una de las aplicaciones.
  Te recomiendo utilizar un `diagrama de secuencias <https://en.wikipedia.org/wiki/Sequence_diagram#:~:text=A%20sequence%20diagram%20shows%20object,the%20functionality%20of%20the%20scenario.>`__.


Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Fase 1 (motivación)
^^^^^^^^^^^^^^^^^^^^^^

* Fecha: julio 15 de 2020 - 2 p.m.
* Descripción: asiste al encuentro sincrónico donde se introducirá la actividad de
  aprendizaje de la unidad 2 correspondiente a las semanas 2 y 3.
* Recursos: ingresa al grupo de `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__
* Duración de la actividad: 20 minutos sincrónicos.
* Forma de trabajo: grupal

Fase 2 (diagnóstico-repaso)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: julio 15 de 2020
* Descripción: lee las preguntas y ejercicios orientadores para autoevaluar si tienes
  los conocimientos necesarios para abordar el RETO.
* Recursos: realiza `esta guía <https://docs.google.com/presentation/d/1y270S1bs49Vn-EX6OJqZrTqaCy2EWlUHECcKAD9ZUrg/edit?usp=sharing>`__.
* Duración de la actividad: 1 hora 10 minutos
* Forma de trabajo: individual con solución de dudas en tiempo real

Fase 3 (fundamentación)
^^^^^^^^^^^^^^^^^^^^^
* Fecha: julio 15-16 de 2020
* Descripción: realiza las lecturas donde se explican los fundamentos conceptuales de la plataforma de software utilizada para 
  la construcción de los programas del controlador.
* Recursos: observa `este <https://docs.google.com/presentation/d/1KGtjm8v-BUcXMhfFBSAfXOtJ8RtVSL0e90qEHsblnMc/edit?usp=sharing>`__
  meterial.
* Duración de la actividad: 1 hora de trabajo autónomo 
* Forma de trabajo: individual

Fase 4 (ejercicios y discusión)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: julio 15-16-17 de 2020
* Descripción: realiza los ejercicios propuestos. Acuerda reuniones con tus compañeros para trabajar de manera *colaborativa*
* Recursos: 

  * observa `este <https://docs.google.com/presentation/d/1KGtjm8v-BUcXMhfFBSAfXOtJ8RtVSL0e90qEHsblnMc/edit?usp=sharing>`__
    meterial.

* Duración de la actividad: 4 horas de trabajo autónomo y colaborativo. Acuerda reuniones con tus compañeros.
* Forma de trabajo: individual y colaborativa.

Fase 5 (retroalimentación): 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* Fecha: julio 17 de 2020 - 2 p.m.
* Descripción: encuentro sincrónico para compartir y discutir los ejercicios. 
* Recursos: 
  
  * Ingresar al grupo de `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__
  * Corrige tus ejercicios (acciones de mejora)

* Duración de la actividad: 50 minutos discusión y 50 minutos para que hagas las acciones de mejora sobre tu trabajo.
* Forma de trabajo: colaborativo con solución de dudas en tiempo real y trabajo individual en la acción de mejora.
