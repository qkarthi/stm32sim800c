#define BLYNK_PRINT Serial
#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

GSMSecurity profile;
// Your GPRS credentials
// Leave empty, if missing user or pass
const char apn[]  = "airtelgprs.com";
const char user[] = "";
const char pass[] = "";
