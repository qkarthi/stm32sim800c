#define LED1    PB15
#define LED2    PB14
#define REL1    PA0
#define REL2    PA1
#define GSM_PWR PA5

void initHwPins(){
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(REL1,OUTPUT);
  pinMode(REL2,OUTPUT);
  pinMode(GSM_PWR,OUTPUT);

  pinMode(LED1,LOW);
  pinMode(LED2,LOW);
}
