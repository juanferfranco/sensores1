Semana 9
===========
Esta semanas abordaremos la construcción de aplicaciones que hagan uso de protocolos de 
comunicación ASCII para intercambiar información con sensores y/o actuadores.

En la primera sesión revisaremos dudas en la implementación del ejercicio de la semana pasada.
Para la segunda sesión, vamos a comenzar la implementación una aplicación para el ejercicio, 
pero utilizando processing. En `este <https://processing.org/reference/libraries/>`__ enlace 
podemos consultar algunas bibliotecas, por ejemplo, Interfascia y Serial.


Este ejemplo, permite adicionar botones:

.. code-block:: java 
   :lineno-start: 1

    import interfascia.*;

    GUIController c;
    IFButton b1, b2;
    IFLabel l;

    void setup() {
        size(200, 100);
        background(155);
        
        c = new GUIController (this);
        
        b1 = new IFButton ("Green", 40, 40, 40, 17);
        b2 = new IFButton ("Blue", 120, 40, 40, 17);

        b1.addActionListener(this);
        b2.addActionListener(this);

        c.add (b1);
        c.add (b2);
    }

    void draw() {

    }

    void actionPerformed (GUIEvent e) {
        if (e.getSource() == b1) {
            background(100, 155, 100);
        } else if (e.getSource() == b2) {
            background(100, 100, 130);
        }
    }

Este otro ejemplo muestra como adicionar cajas de textos y modificar labels en la GUI.

.. code-block:: java 
   :lineno-start: 1

    import interfascia.*;

    GUIController c;
    IFTextField t;
    IFLabel l;

    void setup() {
        size(200, 100);
        background(150);
        
        c = new GUIController(this);
        t = new IFTextField("Text Field", 25, 30, 150);
        l = new IFLabel("", 25, 70);
        
        c.add(t);
        c.add(l);
        
        t.addActionListener(this);
    
    }

    void draw() {
    
    }

    void actionPerformed(GUIEvent e) {
        if (e.getMessage().equals("Completed")) {
            l.setLabel(t.getValue());
        }
    }

Con respecto al manejo del serial. 
Ingrese a este `sitio <https://processing.org/reference/libraries/serial/index.html>`__. Abra 
cada una de las funciones del API y observe los ejemplos. Notará que el uso es muy similar al del 
API de Arduino.

Sustentación parcial 1
-----------------------

En el siguiente `enlace <https://drive.google.com/open?id=1wlD7Lxjqr7CV8DbnAp_7Y5KiCOVtX5JeoEEPrFzTvD4>`__ 
se encuentra el enunciado de la sustentación.


