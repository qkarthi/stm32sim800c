int opernStgVar = 1;
String carrierStr = "", mobileNumberStr = "";
unsigned long nowSec = 0;
bool gsmSerialUpd ;
bool msgRecvd =false;
bool msgRecvdBool = false, msgValidatorBool,callHangerBool = false;
String timeStampStr, msgStr, msgDateStr, msgTimeStr;
char charBufferArray[16];
//////////////////////////////////////////////
void pwrGsmModule() {
  debugEchos1("gsm power low");
  digitalWrite(GSM_PWR, LOW);
  delay(1500); // 1.5 SECONDS FOR WAKE UP TO STBY
  debugEchos1("gsm power high");
  digitalWrite(GSM_PWR, HIGH);
}
//////////////////////////////////////////////
void gsmLiveChecker() {
  debugEchos1("GSM live checker");
  gsmCommand("AT");

  if (serStr.indexOf("AT") > -1) {
    opernStgVar  += 1;
    debugEchos1("AT Mode OK");
    nowSec = millis();
  }
}
//////////////////////////////////////////////
void initGsm() {
  debugEchos1("init gsm");
  gsmCommand("AT+CMGF=1");
  gsmCommand("AT+CLIP=1");
}
//////////////////////////////////////////////
void gsmCarrierIdent() {
  debugEchos1("carrier opern");
  gsmCommand("AT+COPS=3,0");
  gsmCommand("AT+COPS?");

  carrierStr = serStr.substring(serStr.indexOf('"') + 1);
  carrierStr = carrierStr.substring(0, carrierStr.indexOf('"'));
  debugEchos1(carrierStr);
}
//////////////////////////////////////////////
void gsmMsgSend(String mobile_number, String msg) {
  gsmCommand("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsmCommandPrint("AT+CMGS="); // Replace x with mobile number
  gsmCommandPrint("\"");
  gsmCommandPrint(mobile_number);
  gsmCommand("\"");
  delay(500);
  gsmCommandPrint(msg);// The SMS text you want to send
  delay(500);
  Serial2.write(0x1A); // ASCII code of CTRL+Z
  delay(1000);
}
void ackMsgInit(){
  String msg = "";
  
  msg+="GSM POWERED ON";
  msg+="\r\n FW ver. : "+String(CONFIG_VERSION);
  msg+="\r\n Network : "+carrierStr;
  
  gsmMsgSend(String(storage.master_0_mob), msg);
}
