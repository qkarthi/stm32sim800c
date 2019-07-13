#include <EEPROM.h>
#define CONFIG_START 10
#define CONFIG_VERSION "001"

bool eeprom_write_flag = false;

void(* resetFunc_eeprom) (void) = 0;

struct StoreStruct {
  char version[4];
  ////////////////////////////////////////////////////
  char      dev_0_mob[16];
  char      master_0_mob[16];
  char      master_1_mob[16];
  char      slave_1_mob[16];
  char      slave_2_mob[16];
  char      slave_3_mob[16];
  char      slave_4_mob[16];
  char      slave_5_mob[16];
  ////////////////////////////////////////////////////
  uint8_t dev_0_sms: 1;
  uint8_t master_0_sms: 1;
  uint8_t master_1_sms: 1;
  uint8_t slave_1_sms: 1;
  uint8_t slave_2_sms: 1;
  uint8_t slave_3_sms: 1;
  uint8_t slave_4_sms: 1;
  uint8_t slave_5_sms: 1;
  ////////////////////////////////////////////////////
  uint8_t dev_0_call: 1;
  uint8_t master_0_call: 1;
  uint8_t master_1_call: 1;
  uint8_t slave_1_call: 1;
  uint8_t slave_2_call: 1;
  uint8_t slave_3_call: 1;
  uint8_t slave_4_call: 1;
  uint8_t slave_5_call: 1;
  ////////////////////////////////////////////////////
  uint8_t security_on_off: 1;
  uint8_t power_down_alert: 1;
  uint8_t power_up_alert: 1;
  ////////////////////////////////////////////////////

  ////////////////////////////////////////////////////
  uint8_t configflag: 1;
} ;
StoreStruct storage ;
StoreStruct storage_default = {
  CONFIG_VERSION,
  "9524770257", "9524770257", "9524770257", "9524770257", "9524770257", "9524770257", "9524770257", "9524770257",
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  1,0,0,
  0,
};

void loadcon() {
  if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
      EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
      EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2])
  { for (unsigned int t = 0; t < sizeof(storage); t++)
      *((char*)&storage + t) = EEPROM.read(CONFIG_START + t);
  }
  else {
    delay(2000);
    eeprom_write_flag = true;
  }
}

void savecon() {
  for (unsigned int t = 0; t < sizeof(storage); t++) {
    EEPROM.write(CONFIG_START + t, *((char*)&storage + t));
  }
  loadcon();
}

void con_default() {
  if (eeprom_write_flag) {
    storage = storage_default;
    for (unsigned int t = 0; t < sizeof(storage_default); t++)
      EEPROM.write(CONFIG_START + t, *((char*)&storage_default + t));
    delay(2000);
    eeprom_write_flag = false;
    resetFunc_eeprom();
  }
}
