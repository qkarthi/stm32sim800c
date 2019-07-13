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
