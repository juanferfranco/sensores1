Unidad 1. Programación: diagnóstico y repaso
==============================================

Introducción
--------------
Para poder abordar con éxito este curso es importante que repases
tus conocimientos de programación de sistemas embebidos y programación
orientada a objetos. Adicionalmente, es importante identificar de una
vez compañeros con los cuales puedas colaborar y establecer mecanismos
de comunicación. Por tanto, en esta unidad te propondré unas actividades
que te permitan repasar y colaborar con otros.

Propósito de aprendizaje
^^^^^^^^^^^^^^^^^^^^^^^^^^

Autoevaluar las competencias en programación abordadas en los cursos previos
con el fin de determinar estrategias personales que permitan afrontar con
mayor comodidad el curso.

Aunque el proceso de autoevaluación es personal, la evaluación de la esta
unidad la vamos a realizar en grupo. La idea es que desde esta primera
semana identifiques compañeros con los cuales puedas colaborar y ayudarte
en el proceso del curso.

Temas
^^^^^^

* Repaso de la programación básica de sistemas embebidos usando el framework de arduino.
* Repaso de la programación orientada a objetos

Trayecto de acciones, tiempos y formas de trabajo
---------------------------------------------------

Actividad 1: encuentros sincrónicos
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Fechas: 
  
    * enero 20 de 2021 - 2:00 p.m. Sesión de asesoría y corrección.
    * enero 27 de 2021 - 2:00 p.m. Sesión de retroalimentación y revisión.
    
* Descripción: asesorías en tiempo real y retroalimentación final.
* Recursos: ingresa a `Teams <https://teams.microsoft.com/l/team/19%3a919658982cb4457e85d706bad345b5dc%40thread.tacv2/conversations?groupId=16c098de-d737-4b8a-839d-8faf7400b06e&tenantId=618bab0f-20a4-4de3-a10c-e20cee96bb35>`__
* Duración de la actividad: 4 horas. 
* Forma de trabajo: individual-colaborativo/sincrónico

Actividad 2: preparación para el proyecto
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Descripción: realiza los siguientes ejercicios de preparación para 
  el proyecto.
* Recursos: realiza `esta guía <https://docs.google.com/presentation/d/1dJEfVysAZUY0561bICTVKtmZg8D6Ix8klRKGw6DZTp4/edit?usp=sharing>`__.
* Duración de la actividad: 1 hora
* Forma de trabajo: individual/asincrónica.

Actividad 3: proyecto y sustentación
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Descripción: procede con la solución del proyecto.
* Recursos: para abordar el proyecto de programación te recomiendo que:
  
  * No olvides agendar un encuentro sincrónico con tu compañero.
  * Antes de comenzar lee con detenimiento la rúbrica de evaluación de la unidad.
  * Lee la documentación y los ejemplos de la clase `Serial Port <https://docs.microsoft.com/en-us/dotnet/api/system.io.ports.serialport?view=netframework-4.8>`__
    de C# y .NET.
  * Lee la documentación del manejo del puerto `serial de arduino <https://www.arduino.cc/reference/en/language/functions/communication/serial/>`__.
    y los ejemplos.

* Duración de la actividad: 6 horas. 
* Forma de trabajo: colaborativa asincrónica.

Lee con detenimiento el código de honor y luego los pasos que debes seguir
para evidenciar esta actividad.

Código de honor
##################

Para realizar este proyecto se espera que hagas lo siguiente:

* Colabora con tus compañeros cuando así se indique.
* Trabaja de manera individual cuando la actividad así te lo proponga.
* Usa solo la documentación oficial del framework del controlador y .NET de Microsoft.
* NO DEBES utilizar sitios en Internet con soluciones o ideas para atacar el problema.
* NO DEBES hacer uso de foros.
* ¿Entonces qué hacer si no me funciona algo? Te propongo que experimentes, crea hipótesis,
  experimenta de nuevo, observa y concluye.
* NO OLVIDES, este curso se trata de pensar y experimentar NO de BUSCAR soluciones
  en Internet.


Enunciado
##################
Se trata de una calculadora interactiva

* Debes crear dos aplicaciones: una para el PC y otra para un controlador.
* La aplicación del PC la debes realizar usando Visual Studio y será 
  del tipo Consola con .NET framework.
* La aplicación del PC y del controlador interactuarán por medio de un modelo
  cliente servidor. La aplicación del PC será el cliente y la del controlador el servidor.
* En el PC debes solicitar al usuario tres datos: operando 1, operando 2
  (serán enteros positivos de 16 bits) y operador: suma o resta.
* UNA VEZ, y solo UNA VEZ tengas los tres datos, el PC deberá enviar la información
  al controlador.
* El controlador realizará el cálculo y devolverá el resultado al PC para visualizarlo.
* El PC preguntará si se deseas continuar con más cálculos o terminar la aplicación.

¿Qué debes entregar?
++++++++++++++++++++++

* Crea una carpeta principal. Guarda allí dos carpetas más, cada uno con el proyecto para el PC
  y para el controlador. Guarda los proyectos completos. 
* En la carpeta principal guarda una copia de la `rúbrica <https://docs.google.com/spreadsheets/d/1KDN_KJeW9zEi2ZWGOayB52BJu6lNZ4lD7bP6Gbn_T_Q/edit?usp=sharing>`__
  con tu autoevaluación.
* En la carpeta principal guarda un archivo .pdf donde colocarás cuatro cosas:
  
  * La versión de Visual Studio utilizada.
  * La versión del software para programar el controlador.
  * UN ENLACE a tu ONE DRIVE donde estará alojado el video de sustentación.
  * Una tabla de contenidos que indique el instante de tiempo en el cual se pueden encontrar
    cada una de las secciones solicitadas para el video.
* Comprime la carpeta principal en formato .ZIP
* Entrega el archivo .ZIP `aquí <https://auladigital.upb.edu.co/mod/assign/view.php?id=691967>`__.

¿Qué deberá tener el video de sustentación?
+++++++++++++++++++++++++++++++++++++++++++++

Te propongo que este video lo hagas en formato DIALOGO/CONVERSACIÓN, 
de preguntas y respuestas con tu compañero. No tienes que reunirte físicamente, 
PERO si debes reunirte virtualmente para la planeación y si quieres para la realización;
sin embargo, dejo a tu creatividad la manera de presentar e interactuar
con tu compañero.

* Máximo 20 minutos: debes planear el video tal como aprendiste en segundo semestre
  en tu curso de narrativa audiovisual.
* Cuida la calidad del audio y del video.
* Opcional: software para capturar `OBS Studio <https://obsproject.com/>`__.
* Opcional: observa `este <https://www.youtube.com/watch?time_continue=3&v=1tuJjI7dhw0>`__
  tutorial para el manejo de OBS Studio.
* Sección 1: introducción, donde dirás tu nombre y si realizaste el proyecto
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
