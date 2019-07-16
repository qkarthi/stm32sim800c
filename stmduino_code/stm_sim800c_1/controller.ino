void msgController(String buff) {
  if (msgRecvd) {
    if (mobileNumberStr == storage.master_0_mob) {
      String temp ="";
      if(REL1_status){
        temp = "CURRENT STATUS - ON (RUNNING)";
      }else{
        temp = "CURRENT STATUS - OFF (STOPPED)";
      }
      
      if (buff.indexOf("ON") > -1) {
        REL1_status = HIGH;
        digitalWrite(REL1, REL1_status);
        gsmMsgSend(storage.master_0_mob, "TURNED ON");
      } else if (buff.indexOf("on") > -1) {
        REL1_status = HIGH;
        digitalWrite(REL1, REL1_status);
        gsmMsgSend(storage.master_0_mob, "TURNED ON");
      } else if (buff.indexOf("On") > -1) {
        REL1_status = HIGH;
        digitalWrite(REL1, REL1_status);
        gsmMsgSend(storage.master_0_mob, "TURNED ON");
      }else if (buff.indexOf("OFF") > -1) {
        REL1_status = LOW;
        digitalWrite(REL1, REL1_status);
        gsmMsgSend(storage.master_0_mob, "TURNED OFF - DOWN");
      } else if (buff.indexOf("off") > -1) {
        REL1_status = LOW;
        digitalWrite(REL1, REL1_status);
        gsmMsgSend(storage.master_0_mob, "TURNED OFF - DOWN");
      }else if (buff.indexOf("Off") > -1) {
        REL1_status = LOW;
        digitalWrite(REL1, REL1_status);
        gsmMsgSend(storage.master_0_mob, "TURNED OFF - DOWN");
      }else if (buff.indexOf("STATUS") > -1) {
        gsmMsgSend(storage.master_0_mob, temp);
      }else if (buff.indexOf("status") > -1) {
        gsmMsgSend(storage.master_0_mob, temp);
      }else if (buff.indexOf("Status") > -1) {
        gsmMsgSend(storage.master_0_mob, temp);
      }
    }
    msgRecvd =false;
  }

}
