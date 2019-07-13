void serial_to_gsm() {
  if (Serial.available()) {
    gsm_serial.write(Serial.read());
  }
}
void gsm_serial_fun() {
  if (gsm_serial.available()) {
    serstr = gsm_serial.readStringUntil('\n');
    serial_upd = true;
  } else if (serial_upd) {
    /////////////////////////////////////////////////////////////////////////
    Serial.println(serstr); //////////////////
    config_msg_analyser(serstr);
    call_analyser(serstr);
    /////////////////////////////////////////////////////////////////////////
    serial_upd = false;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void config_msg_analyser(String buff) {
  if (buff.indexOf("+CMT:") > -1) {
    mobile_number_str =  (buff.substring(buff.indexOf("91") + 2, buff.indexOf("91") + 12));
    msg_date_str = (buff.substring(buff.indexOf(",,") + 3, buff.indexOf(",,") + 13));
    msg_time_str = (buff.substring(buff.indexOf(",,") + 14, buff.indexOf(",,") + 19));
    dispaly_print("MSG :"+(buff.substring(buff.indexOf("91") + 2, buff.indexOf("91") + 12)));
    msg_recvd_bool = true;
    Serial.println("#_MESSAGE RECEIVED_#");
    Serial.println("mobile_number:" + mobile_number_str);
    Serial.println("date:" + msg_date_str);
    Serial.println("time:" + msg_time_str);
  } else if (msg_recvd_bool == true) {

    msg_validator_bool = false;

    msg_validator(10, buff, "D0_");
    msg_validator(11, buff, "K0_");
    msg_validator(12, buff, "M1_");
    msg_validator(1, buff, "S1_");
    msg_validator(2, buff, "S2_");
    msg_validator(3, buff, "S3_");
    msg_validator(4, buff, "S4_");
    msg_validator(5, buff, "S5_");

    if (msg_validator_bool) {
      gsm_msg_send(mobile_number_str, "SUCCESS");
    }
    else {
      gsm_msg_send(mobile_number_str, "INVALID FORMAT");
      Serial.println("MSG validation fail");
    }

    msg_recvd_bool = false;
  }
}

void msg_validator(int index, String buff, String target_str) {
  if (buff.indexOf(target_str) > -1) {
    msg_str = (buff.substring(buff.indexOf(target_str) + 3, buff.indexOf(",,") + 14));
    if (isDigit(msg_str.charAt(0)) && isDigit(msg_str.charAt(1)) && isDigit(msg_str.charAt(2)) && isDigit(msg_str.charAt(3)) && isDigit(msg_str.charAt(4)) &&
        isDigit(msg_str.charAt(5)) && isDigit(msg_str.charAt(6)) && isDigit(msg_str.charAt(7)) && isDigit(msg_str.charAt(8)) && isDigit(msg_str.charAt(9))) {
      msg_str.toCharArray(char_buffer_array, 16);

      if (index == 1)
        strcpy(storage.slave_1_mob, char_buffer_array);
      else if (index == 2)
        strcpy(storage.slave_2_mob, char_buffer_array);
      else if (index == 3)
        strcpy(storage.slave_3_mob, char_buffer_array);
      else if (index == 4)
        strcpy(storage.slave_4_mob, char_buffer_array);
      else if (index == 5)
        strcpy(storage.slave_5_mob, char_buffer_array);
      else if (index == 10)
        strcpy(storage.dev_0_mob, char_buffer_array);
      else if (index == 11)
        strcpy(storage.master_0_mob, char_buffer_array);
      else if (index == 12)
        strcpy(storage.master_1_mob, char_buffer_array);

      savecon();
      msg_validator_bool = true;
      Serial.println("MSG validation pass");
      Serial.println(storage.dev_0_mob);
      Serial.println(storage.master_0_mob);
      Serial.println(storage.master_1_mob);
      Serial.println(storage.slave_1_mob);
      Serial.println(storage.slave_2_mob);
      Serial.println(storage.slave_3_mob);
      Serial.println(storage.slave_4_mob);
      Serial.println(storage.slave_5_mob);
    }
    Serial.println("MSG :" + (msg_str));
  }
}
/////////////////////////////////////////////////////////////////////////////////////
void call_analyser(String buff){
  if (buff.indexOf("+CLIP:") > -1) {
    mobile_number_str =  (buff.substring(buff.indexOf("91") + 2, buff.indexOf("91") + 12));
    dispaly_print( "CALL:" + mobile_number_str);
    gsm_call_hang();
  }
  if(buff.indexOf("RING") > -1){
    dispaly_print( "CALL DETECT" );
    gsm_call_hang();
  }
}

