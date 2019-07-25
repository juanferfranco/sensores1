#include <Arduino.h>

// VERY IMPORTANT: 
// This code needs a new line character in addition to the data.

//#define _DEBUG 1
#ifdef _DEBUG
#define DEBUG(MSG, VALUE)  Serial.print(MSG); Serial.println(VALUE)
#else
#define DEBUG(MSG, VALUE)
#endif

void taskCalc();

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(3000);

  Serial.print("\nIngrese la operacion: ");
}

enum class calcStates
{
  getOperation,
  getFirstOperand,
  getSecondOperand
};

void loop()
{
  taskCalc();
}

void taskCalc()
{
  static auto calcState = calcStates::getOperation;
  static char operation = '+';
  static uint32_t firstOperand = 0;
  static uint32_t secondOperand = 0;

  switch (calcState)
  {

    case calcStates::getOperation:
      if (Serial.available())
      {
        operation = Serial.read();
        Serial.read();
        Serial.println(operation);
        calcState = calcStates::getFirstOperand;
        Serial.print("Ingrese el primer operando: ");
      }
      break;

    case calcStates::getFirstOperand:
      if (Serial.available())
      {
        firstOperand = Serial.parseInt();
        Serial.read();
        Serial.println(firstOperand);
        calcState = calcStates::getSecondOperand;
        Serial.print("Ingrese el segundo operando: ");
      }
      break;

    case calcStates::getSecondOperand:
      if (Serial.available())
      {
        secondOperand = Serial.parseInt();
        Serial.read();
        Serial.println(secondOperand);

        uint32_t result = 0;
        switch (operation)
        {
          case '+':
            result = firstOperand + secondOperand;
            break;
          case '-':
            result = firstOperand - secondOperand;
            break;
          case '*':
            result = firstOperand * secondOperand;
            break;
          case '/':
            result = firstOperand / secondOperand;
            break;

          case '%':
            result = firstOperand % secondOperand;
            break;
          default:
            Serial.print("Error: ");
            Serial.println(operation);
            calcState = calcStates::getOperation;
            Serial.print("Ingrese la operacion: ");
            return;
            break;
        }
        char message[30];
        Serial.print("Resultado: ");
        sprintf(message, "%d %c %d = %d", firstOperand, operation, secondOperand, result);
        Serial.println(message);

        calcState = calcStates::getOperation;
        Serial.print("Ingrese la operacion: ");
      }
      break;
  }
}
