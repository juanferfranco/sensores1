void task1(void) {
  // Data: '1' '5' '2' '7'
  static const uint8_t dataToRx[] = {0x31, 0x35, 0x32, 0x37};
  static uint8_t dataCounter = 0;
  enum class states { WAITING_FIRST, WAITING_OTHERS};
  static states state = states::WAITING_FIRST;
  static uint32_t initTime;
  static bool seqError = false;
  static bool timeOutL = false;
  static bool timeOutH = false;

  switch (state) {

    case states::WAITING_FIRST:
      if (Serial.available()) {
        initTime = millis();
        uint8_t dataRX = Serial.read();
        if (dataRX != dataToRx[dataCounter]) seqError = true;
        dataCounter++;
        state = states::WAITING_OTHERS;
      }
      break;

    case states::WAITING_OTHERS:

      if (Serial.available() ) {
        uint8_t dataRX = Serial.read();
        uint32_t timeNow = millis();
        if (timeNow - initTime < 2000) timeOutL = true ;
        if ( (timeNow - initTime) > 5000 ) timeOutH = true;
        initTime = timeNow;        

        if (dataRX != dataToRx[dataCounter]) seqError = true;
        dataCounter++;
        
        if ( dataCounter == 4) {
          if (timeOutH == true) Serial.println("timeout high");
          if (timeOutL == true) Serial.println("timeout low");
          if (seqError == true) Serial.println("key error");
          
          if ( (seqError == false) && (timeOutL == false) && (timeOutH == false) ) Serial.println("disarm");

          state = states::WAITING_FIRST;
          dataCounter = 0;
          seqError = false;
          timeOutH = false;
          timeOutL = false;
        }
      
      }
      break;
  }
}
