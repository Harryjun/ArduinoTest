//本历程为IMU测试程序
#include <Servo.h>
#include "MMA8653Library.h"
#include <Wire.h>

Servo myservo;  // create servo 
int IMU= 14;
int Led = 11;
float sensorValue = 0;
int flag = 0;
const byte interruptPin = 2;


void setup() {
  // put your setup code here, to run once:
 // pinMode(IMU,INPUT);
  pinMode(Led,OUTPUT);
  Serial.begin(9600);

Wire.begin(); //Join the bus as a master
  initMMA8653(); //Test and intialize the MMA8452
  
   myservo.attach(9);
   digitalWrite(Led,HIGH); 
myservo.write(0);
   pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    MMA8653_x_Gdata();//显示G值在x轴的加速度
     MMA8653_y_Gdata();//显示G值在y轴的加速度
     MMA8653_z_Gdata();//显示G值在z轴的加速度
     MMA8653_x_angle();//显示物体与x轴的夹角
     MMA8653_y_angle();//显示物体与y轴的夹角
    
    if(flag == 1)
    {
      myservo.write(0);
      delay(500);
      
       sensorValue = MMA8653_x_Gdata();
      delay(100);
      Serial.print(sensorValue); Serial.print("      ");
delay(10);
      if(sensorValue >= 0.8)
      {
        flag = 2;  
      }
      if(sensorValue <= -0.8)
      {
        flag = 3;  
      }
      
    
    }
    if(flag == 2)
    {
      myservo.write(190);
      delay(500);
      sensorValue = MMA8653_x_Gdata();
      delay(100);
      Serial.print(sensorValue); Serial.print("      ");
delay(10);
      if(sensorValue <= -0.8)
      {
        flag = 4;  
      }
    }
    if(flag == 3)
    {
      myservo.write(190);
      delay(500);
      sensorValue = MMA8653_x_Gdata();
      delay(100);
      Serial.print(sensorValue); Serial.print("      ");
delay(10);
      if(sensorValue >= 0.8)
      {
        flag = 4;  
      }
    }
    if(flag == 4)
    {
      while(flag == 4)
      {
         digitalWrite(Led,LOW);       delay(100);
         Serial.print("      ");//Serial.print(flag);
      }
       
    }


    
  }

}



void blink() {
flag = 1;Serial.print("      ");
Serial.print(flag); digitalWrite(Led,HIGH);   

}
