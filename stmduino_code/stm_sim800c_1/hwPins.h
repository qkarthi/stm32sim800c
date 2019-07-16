#define LED1    PB15
#define LED2    PB14
#define REL1    PA0
#define REL2    PA1
#define GSM_PWR PA5

bool REL1_status = false ;
bool REL2_status = false ;

void initHwPins(){
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(REL1,OUTPUT);
  pinMode(REL2,OUTPUT);
  pinMode(GSM_PWR,OUTPUT);

  digitalWrite(LED1,LOW);
  digitalWrite(LED2,HIGH);
}
