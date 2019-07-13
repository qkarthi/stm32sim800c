/*
   TX -> PGM
   RX -> PGM
   D2 -> NULL
   D3 -> NULL
   D4 -> SENSOR 1
   D5 -> SENSOR 2
   D6 -> BUZZER
   D7 -> GSM_PWR
   D8 -> NULL
   D9 -> NULL
   D10 -> NULL
   D11 -> NULL
   D12 -> NULL
   D13 -> NULL
   A0(14) -> GSM RX
   A1(15) -> GSM TX
   A2(16) -> NULL
   A3(17) -> NULL
   A4(18) -> DISPALY_I2C_SDA
   A5(19) -> DISPALY_I2C_SCL
*/

//////////////////////////////////////////////////////////////////////////
#include "storage.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define printByte(args)  write(args);
//////////////////////////////////////////////////////////////////////////
const int sensor_1_pin = 4;
const int sensor_2_pin = 5;
const int buzzer_pin = 6;
//const int buzzer_pin = 8;
const int gsm_pwr_pin = 7;
const int gsm_tx_pin = 14;
const int gsm_rx_pin = 15;
//////////////////////////////////////////////////////////////////////////
SoftwareSerial gsm_serial(gsm_rx_pin, gsm_tx_pin); // RX, TX <-ARDUINO
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
//////////////////////////////////////////////////////////////////////////
unsigned long at_check_sec = 0;
unsigned long s1_check_sec=0;
unsigned long now_sec=0;
String serstr = "";
bool serial_upd = false;
bool msg_recvd_bool = false, msg_validator_bool;
String mobile_number_str,time_stamp_str, msg_str,carrier_str,msg_date_str,msg_time_str;
char char_buffer_array[16];
int opern_stg_vars = 1;
int rssi = 0,int_hour,int_minute,int_year,int_month,int_day, i = 0;
/////////////////////////////////////////////////////////////////////////
String network_provider;
///////////////////////////////////////////////////////////////////////////
uint8_t tower_sym[8] = { 0x1F, 0x1F, 0xE, 0x4, 0x4, 0x4, 0x4, 0x4};

uint8_t signal_1_1[8] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x10};
uint8_t signal_1_2[8] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x14, 0x14};
uint8_t signal_1_3[8] = { 0x0, 0x0, 0x0, 0x0, 0x1, 0x5, 0x15, 0x15};

uint8_t signal_2_1[8] = { 0x0, 0x0, 0x0, 0x10, 0x10, 0x10, 0x10, 0x10};
uint8_t signal_2_2[8] = { 0x0, 0x0, 0x4, 0x14, 0x14, 0x14, 0x14, 0x14};
uint8_t signal_2_3[8] = { 0x1, 0x1, 0x5, 0x15, 0x15, 0x15, 0x15, 0x15};

///////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  gsm_serial.begin(9600);
  display_init();
  loadcon();
  con_default();
  init_hw_pins();
  gsm_power_up();
}

void loop() {
  switch (opern_stg_vars) {
    case 1:
      //at command listener
      if ((millis() - now_sec > 3000)) {
        gsm_live_checker();
        now_sec = millis();
      }
      break;
    case 2:
      //simcard detection
      sim_detection();
      break;
    case 3:
      //carrier

      opern_stg_vars += 1;
      break;
    case 4:
      gsm_init();
      dispaly_print(" ");
      break;
    default:
      if ((millis() - at_check_sec > 10000)) {
         gsm_call_hang();
        at_check_sec = millis();
        display_cluster();
        gsm_utc();
      }
      gsm_serial_fun();
      sensor_1_func();
      break;
  }
  serial_to_gsm();
}


