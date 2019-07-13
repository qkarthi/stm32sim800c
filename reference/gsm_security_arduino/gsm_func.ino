// Basic notes
// default baud rate = 38400
// AT+IPR=9600;

void gsm_live_checker() {
  gsm_serial.println("AT");
  if (gsm_serial.available()) {
    serstr = gsm_serial.readStringUntil('\n');
    if (serstr.indexOf("AT") > -1) {
      dispaly_print(" GSM POWERED UP ");
      opern_stg_vars  += 1;
   //   buzzer();
    }
  }
}
void gsm_init() {
  gsm_serial.print("AT+CMGF=1\r\n");
  delay(500);
  gsm_serial.print("AT+CLIP=1\r\n");
  delay(500);
  dispaly_print(" GSM STARTED");
  gsm_carrier_identification();
  opern_stg_vars += 1;
 // buzzer();
}
void gsm_call(String mobile_number) {
  gsm_serial.print("ATD" + mobile_number + "\r\n"); // call command for GSM
}
void gsm_call_hang() {
  gsm_serial.print("ATH\r\n");
}
void gsm_msg_send(String mobile_number, String msg) {
  gsm_serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsm_serial.print("AT+CMGS="); // Replace x with mobile number
  gsm_serial.println(mobile_number);
  delay(1000);
  gsm_serial.print(msg);// The SMS text you want to send
  delay(1000);
  gsm_serial.write(0x1A); // ASCII code of CTRL+Z
  delay(1000);
}


int gsm_rssi() {
  gsm_serial.println("AT+CSQ");
  serstr = gsm_serial.readStringUntil("OK");
  (serstr.substring(serstr.indexOf(":") + 2, serstr.indexOf(","))).toCharArray(char_buffer_array, 3 );
  i = atoi(char_buffer_array);
  return map(i, 0, 31, 0, 100);
}

void gsm_carrier_identification() {
  Serial.println("carrier opern");
  Serial.println(serstr);
  gsm_serial.println("AT+COPS=3,0");
  delay(300);
  gsm_serial.println("AT+COPS?");
  serstr = gsm_serial.readStringUntil("OK");
  carrier_str = serstr.substring(serstr.indexOf('"') + 1);
  carrier_str = carrier_str.substring(0, carrier_str.indexOf('"'));
  serstr="";
}
void gsm_utc() {
  gsm_serial.println("AT+CCLK");
  delay(300);
  serstr = gsm_serial.readStringUntil("OK"); 
  if ((serstr.indexOf("ERR"))==-1){
    serstr=serstr.substring(serstr.indexOf("\"")+1,serstr.lastIndexOf("\"")-1);  
    int_year=serstr.substring(0,2).toInt();
    int_month= serstr.substring(3,5).toInt();
    int_day=serstr.substring(6,8).toInt();
    int_hour=serstr.substring(9,11).toInt();
    int_minute=serstr.substring(12,14).toInt();
    serstr="";
    time_stamp_str=String(int_day)+"/"+String(int_month)+"/"+String(int_year)+"  "+String(int_hour+5)+":"+String(int_minute+30);
    Serial.println(time_stamp_str);
 }else{
  int_year=0;
  int_month=0;
  int_day=0;
  int_hour=0;
  int_minute=0;
   time_stamp_str="TIME UPDATE ERROR";
    Serial.println(time_stamp_str);
 }
}

void sim_detection() {
  Serial.println("sim card opern");
  gsm_serial.println("AT+CPIN?");
  serstr = gsm_serial.readStringUntil("OK");
  if (serstr.indexOf("READY") > -1) {
    opern_stg_vars += 1;
    dispaly_print(" SIM CARD FOUND ");
  } else {
    dispaly_print("  NO SIM CARD   ");
  }
  serstr = "";
  delay(1000);
}

