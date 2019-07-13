void init_hw_pins() {
  pinMode(sensor_1_pin, INPUT) ; // sensor 1
  pinMode(sensor_2_pin, INPUT) ; // sensor 2
  pinMode(buzzer_pin, OUTPUT)  ; // buzzer
  pinMode(gsm_pwr_pin, OUTPUT) ; // gsm power
}

void gsm_power_up() {
  digitalWrite(gsm_pwr_pin, HIGH);
}
void buzzer() {
  digitalWrite(buzzer_pin, HIGH);
  delay(300);
  digitalWrite(buzzer_pin, LOW);
}

void sensor_1_func() {
  if (digitalRead(sensor_1_pin)==HIGH) {
    if ((millis() - s1_check_sec > 60000)) {
     gsm_call("9524770257");
      s1_check_sec = millis();
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.print("alert sent");
      Serial.println("alert sent");
      buzzer();
      delay(10000);
      
         gsm_call_hang();
    }
  }
}

