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
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(MOTOR, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  pinMode(STOP, INPUT);
  pinMode(START, INPUT);
   
  stopFlag = false;
  startFlag = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(STOP) == HIGH)
    StopMotor();
  else if(digitalRead(STOP) == LOW)
    StopFall();

  if(digitalRead(START) == HIGH)
    StartMotor();
  else if(digitalRead(START) == LOW)
    StartFall();
  
  if(stopFlag == true && startFlag == true){
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);

    digitalWrite(MOTOR, LOW);
  }
  delay(5);
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

