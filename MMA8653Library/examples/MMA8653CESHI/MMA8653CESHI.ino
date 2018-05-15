#include "MMA8653Library.h"
#include <Wire.h>
void setup()
{
  Serial.begin(9600);
  Wire.begin(); //Join the bus as a master
  initMMA8653(); //Test and intialize the MMA8452
}

void loop()
{    
     MMA8653_x_Gdata();//显示G值在x轴的加速度
     MMA8653_y_Gdata();//显示G值在y轴的加速度
     MMA8653_z_Gdata();//显示G值在z轴的加速度
     MMA8653_x_angle();//显示物体与x轴的夹角
     MMA8653_y_angle();//显示物体与y轴的夹角
     Serial.print(MMA8653_x_Gdata(),4); //显示G值在x轴的加速度
     Serial.print("\t");  // tabs in between axes
     Serial.print(MMA8653_y_Gdata(),4); //显示G值在y轴的加速度
     Serial.print("\t");  // tabs in between axes
     Serial.print(MMA8653_z_Gdata(),4); //显示G值在z轴的加速度
     Serial.print("\t");  // tabs in between axes
     Serial.print(MMA8653_x_angle(),2);  //显示物体与x轴的夹角
     Serial.print("\t");  // tabs in between axes
     Serial.print(MMA8653_y_angle(),2);  //显示物体与y轴的夹角
     Serial.print("\t");  // tabs in between axes
     Serial.println();
     delay(10);
}
