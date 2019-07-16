HardwareSerial Serial2(USART2);   // or HardWareSerial Serial2 (PA3, PA2);
String serStr ;

void initSerial() {
  Serial1.begin(SERIAL_BAUD);
  Serial2.begin(SERIAL_BAUD);
}

void serialDebug() {
  if (Serial2.available()) {
    Serial1.print( Serial2.readString());
  }
  if (Serial1.available()) {
    Serial2.print( Serial1.readString());
  }
}
void serialDebugTx() {
  if (Serial1.available()) {
    Serial2.print( Serial1.readString());
  }
}


//////////////////////////////////////////////
void debugEchos1(String echo) {
  Serial1.println(echo);
}

void gsmCommand(String echo) {
  debugEchos1(" ### - " + echo);
  Serial2.println(echo);
  serStr = Serial2.readString();
  debugEchos1(serStr);
  delay(500);
}
void gsmCommandPrint(String echo) {
  Serial2.print(echo);
}

//------------------------------------------//
