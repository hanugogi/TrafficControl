#define STOP 2
#define START 3

#define MOTOR 4

#define LED_R 5
#define LED_G 6
#define LED_B 7

void StopFall(void);
void StartFall(void);
void StopMotor(void);
void StartMotor(void);

bool stopFlag = false, startFlag = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  pinMode(STOP, INPUT);
  pinMode(START, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(STOP), StopMotor, RISING);
  attachInterrupt(digitalPinToInterrupt(START), StartMotor, RISING);
  
  attachInterrupt(digitalPinToInterrupt(STOP), StopFall, FALLING);
  attachInterrupt(digitalPinToInterrupt(START), StartFall, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(stopFlag && startFlag){
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);

    digitalWrite(MOTOR, LOW);
  }
  delay(1);
}

void StopFall(void){
  stopFlag = false;
}

void StartFall(void){
  startFlag = false;
}

void StopMotor(void){
  stopFlag = true;
  
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  
  digitalWrite(MOTOR, LOW);
}

void StartMotor(void){
  startFlag = true;
  
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, LOW);
  
  digitalWrite(MOTOR, HIGH);
}
