#include <Servo.h>

Servo myservo;  // create servo 
int Left_Value = 570;
int Right_Value = 580;
const byte interruptPin = 2;


int Temp = 50;
const int LED_RED = 4;
const int LED_GREEN = 5;
int flag = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  //pinMode(16, INPUT);
  //pinMode(17, INPUT);
 // pinMode(18, INPUT);
 Serial.begin(9600);
 myservo.attach(9);
 // pinMode(14, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a,b,c,d,e,f,g;
  while(1)
  {

    digitalWrite(LED_GREEN,HIGH);
        digitalWrite(LED_RED,LOW);
 //   a = analogRead(14);b = analogRead(15);
  //  c = analogRead(16);d = analogRead(17);
  //  e = analogRead(18);
   
  f = analogRead(14);g = analogRead(15);
  Serial.print(f);
  Serial.print("      ");Serial.print(g);
  Serial.print('\n');

  myservo.write(180);  delay(2000);
  f = analogRead(14);g = analogRead(15);
  Serial.print(f);
  Serial.print("      ");Serial.print(g);
  Serial.print("      ");Serial.print(flag);
  Serial.print('\n');
  if(f >= Left_Value && flag == 0)
  {
    flag++;  
  }
  myservo.write(0);  delay(2000);
  f = analogRead(14);g = analogRead(15);
  Serial.print(f);
  Serial.print("      ");Serial.print(g);
  Serial.print("      ");Serial.print(flag);
  Serial.print('\n');
  if(g >= Right_Value && flag == 1)
  {
    flag++;  
  }
  if(flag == 2)
  {
    Serial.print("      ");Serial.print(flag);
    digitalWrite(LED_GREEN,LOW); 
      digitalWrite(LED_RED,HIGH);
    flag++;
  }
  else
  {
    flag++;
  }
  Serial.print("      ");Serial.print(flag);
  while(flag == 3)
  {
    Serial.print("      ");Serial.print(flag);
   }
  Serial.print("      ");Serial.print("4444");

  }
  

}


void blink() {
  flag = 0;
}
