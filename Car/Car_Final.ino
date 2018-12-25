#define SIG1 2
#define SIG2 3

#define MOTOR A5

#define LED_R 4
#define LED_G 5
#define LED_B 6

void StopMotor(void);
void StartMotor1(void);
void StartMotor2(void);
void Fix(void);

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(MOTOR, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  pinMode(SIG1, INPUT);
  pinMode(SIG2, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(SIG1) == LOW)
  {
    if(digitalRead(SIG2) == LOW)
      StopMotor();
  }

  if(digitalRead(SIG1) == LOW)
  {
    if(digitalRead(SIG2) == HIGH)
      StartMotor1();
  }

  if(digitalRead(SIG1) == HIGH)
  {
    if(digitalRead(SIG2) == LOW)
      StartMotor2();
  }

  if(digitalRead(SIG1) == HIGH)
  {
    if(digitalRead(SIG2) == HIGH)
      Fix();  
  }
  delay(5);
}

void StopMotor(void)
{
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  
  analogWrite(MOTOR, 0);
}

void StartMotor1(void)
{ 
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, LOW);

  analogWrite(MOTOR, 255);
  delay(20);
  analogWrite(MOTOR, 0);
}

void StartMotor2(void)
{ 
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, HIGH);
  
  analogWrite(MOTOR, 255);
}

void Fix(void)
{
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, HIGH);
  
  analogWrite(MOTOR, 0);
}

