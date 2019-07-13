void display_init() {
  lcd.init();
  lcd_custom_char_create();
  dispaly_print(" GSM  SECURITY ");
  lcd.backlight();
}

void dispaly_print(String buff) {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(buff);
}

void display_cluster() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.printByte(1);
  lcd.setCursor(5, 0);
  lcd.print(carrier_str);
  lcd.setCursor(1, 0);
  //update network
  if (rssi < 15) {
    lcd.print("x");
  } else if (rssi < 30) {
    lcd.printByte(2);
  } else if (rssi < 45) {
    lcd.printByte(3);
  } else if (rssi < 60) {
    lcd.printByte(4);
  } else if (rssi < 75) {
    lcd.printByte(4); lcd.printByte(5);
  } else if (rssi < 90) {
    lcd.printByte(4); lcd.printByte(6);
  } else if (rssi <= 100) {
    lcd.printByte(4); lcd.printByte(7);
  }

  rssi = gsm_rssi();
  // next line
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.print(time_stamp_str);
}
void lcd_custom_char_create() {
  lcd.createChar(1, tower_sym);

  lcd.createChar(2, signal_1_1);
  lcd.createChar(3, signal_1_2);
  lcd.createChar(4, signal_1_3);

  lcd.createChar(5, signal_2_1);
  lcd.createChar(6, signal_2_2);
  lcd.createChar(7, signal_2_3);

}


/*

  //  lcd.noBacklight();

*/
