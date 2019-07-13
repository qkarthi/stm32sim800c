#include "aConfig.h"
#include "hwPins.h"
#include "led.h"
#include "serial.h"
#include "storage.h"
#include "gsm.h"

/////////////////////////////////////////////////////////
void setup() {
  initSerial();
  initHwPins();
  delay(3000); // for debug purpose
  pwrGsmModule();
  loadcon();
  con_default();
}

void loop() {
  StbyLedMillisFunc();
  switch (opernStgVar) {
    case 1:
      //WARM UP TIME for gsm
      if ((millis() - nowSec > 30000)) {
        opernStgVar += 1;
      }
      serialDebug();
      break;
    case 2:
      //AT command checker for gsm
      if ((millis() - nowSec > 2000)) {
        gsmLiveChecker();
        nowSec = millis();
      }
      break;
    case 3:
      //init gsm for sms and call
      initGsm();
      gsmCarrierIdent();
      gsmMsgSend("9524770257", "hello");
      opernStgVar += 1;
      break;
    default:
      //debug at last
      serialDebug();
      //gsmSerialFunc();
      break;
  }

}
