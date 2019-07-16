void gsmSerialFunc() {
  if (Serial2.available()) {
    serStr = Serial2.readString();
    gsmSerialUpd = true;
  } else if (gsmSerialUpd) {
    /////////////////////////////////////////////////////////////////////////
    debugEchos1("DEBUG :" + serStr); //////////////////
    callAnalyser(serStr);
    msgAnalyser(serStr);
    msgReader(serStr);
    msgConfigValidator(serStr);
    msgController(serStr);
    /////////////////////////////////////////////////////////////////////////
    gsmSerialUpd = false;
  }
}

void callAnalyser(String buff) {
  if (buff.indexOf("+CLIP:") > -1) {
    mobileNumberStr =  (buff.substring(buff.indexOf("91") + 2, buff.indexOf("91") + 12));
    debugEchos1( "CALL:" + mobileNumberStr);
    if(mobileNumberStr==storage.master_0_mob){
      REL1_status = !REL1_status;
      digitalWrite(REL1,REL1_status);
    }
    callHangerBool = true;
  }
  if (buff.indexOf("RING") > -1) {
    debugEchos1( "CALL DETECT" );
    if (callHangerBool) {
      delay(3000);
      gsmCommand("ATH");
      debugEchos1( "CALL DISCONNECTED" );
      callHangerBool = false;
      //StatusAck = true ;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void msgAnalyser(String buff) {
  if (buff.indexOf("+CMTI:") > -1) {
    if (buff.indexOf(",") > -1) {
      String temp = buff.substring(buff.indexOf(",") + 1, buff.length() - 1);
      debugEchos1(temp);
      gsmCommand("AT+CMGR=" + temp);
    }
  }
}
void msgReader(String buff) {
  if (buff.indexOf("+CMGR:") > -1) {
    mobileNumberStr =  (buff.substring(buff.indexOf("91") + 2, buff.indexOf("91") + 12));
    msgDateStr = (buff.substring(buff.indexOf("/") - 2, buff.indexOf("/") + 6));
    msgTimeStr = (buff.substring(buff.indexOf("/") + 7, buff.indexOf("/") + 15));
    debugEchos1("#_MESSAGE RECEIVED_#");
    debugEchos1("mobile_number:" + mobileNumberStr);
    debugEchos1("date:" + msgDateStr);
    debugEchos1("time:" + msgTimeStr);
    msgRecvd = true;
  }
}

void msgConfigValidator(String buff) {
  if (buff.indexOf("CONFIG") > -1) {
    msgConfigUpdator(0, buff, "DEVELO");
    msgConfigUpdator(1, buff, "MASTER");
  }
}

void msgConfigUpdator(int index, String buff, String target_str) {
  if (buff.indexOf(target_str) > -1) {
    msgStr = (buff.substring(buff.indexOf(target_str) + 7, buff.indexOf(target_str) + 17));
    debugEchos1("here:");
    debugEchos1(msgStr);
    debugEchos1("there:");
    if (isDigit(msgStr.charAt(0)) && isDigit(msgStr.charAt(1)) && isDigit(msgStr.charAt(2)) && isDigit(msgStr.charAt(3)) && isDigit(msgStr.charAt(4)) &&
        isDigit(msgStr.charAt(5)) && isDigit(msgStr.charAt(6)) && isDigit(msgStr.charAt(7)) && isDigit(msgStr.charAt(8)) && isDigit(msgStr.charAt(9))) {
      msgStr.toCharArray(charBufferArray, 16);

      if (index == 0)
        strcpy(storage.dev_0_mob, charBufferArray);
      else if (index == 1)
        strcpy(storage.master_0_mob, charBufferArray);

      savecon();
      debugEchos1("MSG validation pass");
      debugEchos1(storage.dev_0_mob);
      debugEchos1(storage.master_0_mob);
      gsmMsgSend(mobileNumberStr, "Configuration Success ! \r\n MASTER Assigned as " + String(storage.master_0_mob));
    }
    else {
      gsmMsgSend(mobileNumberStr, "FORMAT ERROR");
    }
  }
}
