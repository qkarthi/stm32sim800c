void gsmSerialFunc() {
  if (Serial2.available()) {
    serStr = Serial2.readString();
    gsmSerialUpd = true;
  } else if (gsmSerialUpd) {
    /////////////////////////////////////////////////////////////////////////
    debugEchos1(serStr); //////////////////
    configMsgAnalyser(serStr);
    callAnalyser(serStr);
    
    /////////////////////////////////////////////////////////////////////////
    gsmSerialUpd = false;
  }
}

void callAnalyser(String buff){
  if (buff.indexOf("+CLIP:") > -1) {
    mobileNumberStr =  (buff.substring(buff.indexOf("91") + 2, buff.indexOf("91") + 12));
    debugEchos1( "CALL:" + mobileNumberStr);
  }
  if(buff.indexOf("RING") > -1){
    debugEchos1( "CALL DETECT" );
  delay(3000);
  gsmCommand("ATH");
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void configMsgAnalyser(String buff) {
  if (buff.indexOf("+CMT:") > -1) {
    mobileNumberStr =  (buff.substring(buff.indexOf("91") + 2, buff.indexOf("91") + 12));
    msgDateStr = (buff.substring(buff.indexOf(",,") + 3, buff.indexOf(",,") + 13));
    msgTimeStr = (buff.substring(buff.indexOf(",,") + 14, buff.indexOf(",,") + 19));
    msgRecvdBool = true;
    debugEchos1("#_MESSAGE RECEIVED_#");
    debugEchos1("mobile_number:" + mobileNumberStr);
    debugEchos1("date:" + msgDateStr);
    debugEchos1("time:" + msgTimeStr);
  } else if (msgRecvdBool == true) {

    msgValidatorBool = false;

    msgValidator(10, buff, "D0_");
    msgValidator(11, buff, "K0_");
    msgValidator(12, buff, "M1_");
    msgValidator(1, buff, "S1_");
    msgValidator(2, buff, "S2_");
    msgValidator(3, buff, "S3_");
    msgValidator(4, buff, "S4_");
    msgValidator(5, buff, "S5_");

    if (msgValidatorBool) {
      gsmMsgSend(mobileNumberStr, "SUCCESS");
    }
    else {
      gsmMsgSend(mobileNumberStr, "INVALID FORMAT");
      debugEchos1("MSG validation fail");
    }

    msgRecvdBool = false;
  }
}


void msgValidator(int index, String buff, String target_str) {
  if (buff.indexOf(target_str) > -1) {
    msgStr = (buff.substring(buff.indexOf(target_str) + 3, buff.indexOf(",,") + 14));
    if (isDigit(msgStr.charAt(0)) && isDigit(msgStr.charAt(1)) && isDigit(msgStr.charAt(2)) && isDigit(msgStr.charAt(3)) && isDigit(msgStr.charAt(4)) &&
        isDigit(msgStr.charAt(5)) && isDigit(msgStr.charAt(6)) && isDigit(msgStr.charAt(7)) && isDigit(msgStr.charAt(8)) && isDigit(msgStr.charAt(9))) {
      msgStr.toCharArray(charBufferArray, 16);

      if (index == 1)
        strcpy(storage.slave_1_mob, charBufferArray);
      else if (index == 2)
        strcpy(storage.slave_2_mob, charBufferArray);
      else if (index == 3)
        strcpy(storage.slave_3_mob, charBufferArray);
      else if (index == 4)
        strcpy(storage.slave_4_mob, charBufferArray);
      else if (index == 5)
        strcpy(storage.slave_5_mob, charBufferArray);
      else if (index == 10)
        strcpy(storage.dev_0_mob, charBufferArray);
      else if (index == 11)
        strcpy(storage.master_0_mob, charBufferArray);
      else if (index == 12)
        strcpy(storage.master_1_mob, charBufferArray);

      savecon();
      msgValidatorBool = true;
      debugEchos1("MSG validation pass");
      debugEchos1(storage.dev_0_mob);
      debugEchos1(storage.master_0_mob);
      debugEchos1(storage.master_1_mob);
      debugEchos1(storage.slave_1_mob);
      debugEchos1(storage.slave_2_mob);
      debugEchos1(storage.slave_3_mob);
      debugEchos1(storage.slave_4_mob);
      debugEchos1(storage.slave_5_mob);
    }
    debugEchos1("MSG :" + (msgStr));
  }
}
