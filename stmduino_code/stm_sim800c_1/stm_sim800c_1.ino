#include "aConfig.h"
#include "hwPins.h"
#include "serial.h"
#include "storage.h"
#include "gsm.h"
#include "led.h"
/////////////////////////////////////////////////////////
void setup() {
  initSerial();
  initHwPins();
  delay(3000); // for debug purpose
  pwrGsmModule();
  loadcon();
  con_default();
  debugEchos1(storage.dev_0_mob);
  debugEchos1(storage.master_0_mob);
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
      acKMsgInit();
      opernStgVar += 1;
      break;
    case 4:
      gsmSerialFunc();
      serialDebugTx();
      break;
    default:
      //debug at last
      serialDebug();
      break;
  }

}
