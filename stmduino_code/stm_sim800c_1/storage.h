#include <EEPROM.h>
#define CONFIG_START 10
#define CONFIG_VERSION "004"

bool eeprom_write_flag = false;

struct StoreStruct {
  char version[4];
  ////////////////////////////////////////////////////
  char  dev_0_mob[16];
  char  master_0_mob[16];
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  uint8_t configflag: 1;
} ;
StoreStruct storage ;
StoreStruct storage_default = {
  CONFIG_VERSION,
  "9524770257", "9524770257",
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
    {
      EEPROM.write(CONFIG_START + t, *((char*)&storage_default + t));
    }
    eeprom_write_flag = false;
    loadcon();
  }
}
