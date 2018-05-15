#include <MsTimer2.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//施密特触发器上下边沿值
int Value_Change_Low = 920;
int Value_Change_High = 950;
//ConfigValue
int Value_High = 0;
int Value_Low = 0;
//记录红外的距离
int Count_Infrard = 0;
//系统开始标志位（可以作为按钮操作）预留标志
int START = 0;
//开始计数标志
bool Beign_Count = 0;
//时间计数（计数单位10ms）
int Count_Time = 0;
//存储按键值
int Function_Key = 1;
int Function = 0;

//If using hardware SPI
#define OLED_DC     4
#define OLED_CS     0xff//not use CS, because the circuit has pulled it down to ground
#define OLED_RESET  7
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

 #if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
 
void setup() {
  // put your setup code here, to run once:
 pinMode(19, INPUT);pinMode(18, INPUT);
 pinMode(14, INPUT);
 pinMode(15, INPUT);
 pinMode(16, INPUT);
 pinMode(17, INPUT);
 Serial.begin(9600);
 MsTimer2::set(10,Time_Count); 

// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("VelocityMeasurement");
  display.setCursor(40,35);
  display.println("By HTE Robot");
  display.display();
  delay(2000);
  View_Main();
 
 
 //attachInterrupt(digitalPinToInterrupt(15), Start_Change, CHANGE);
}


void Time_Count()
{

  Count_Time++;

}


void loop() {

  int Count_Motor = 0;//记录电机转动的圈数

bool Status_Motor = 0;//电机状态

  
  int AAA;
  // put your main code here, to run repeatedly:
   Count_Infrard = analogRead(19);
//   Serial.print(AAA);Serial.print('\n');
//   delay(1000);
while(1){
  Count_Infrard = analogRead(19);
 // Serial.print(Count_Infrard);Serial.print('\n');
  if(START == 0)
  {//主页
      display.setTextColor(WHITE,BLACK);
  display.setCursor(0,0);
  display.println("Menu");
    Function_Key = Key_Scan();
    if(Function_Key == 1)
    {
      Function = 1;
      display.setTextColor(BLACK, WHITE); // 'inverted' text
      display.setCursor(0,20);
      display.println("[A0] ParameterCorrect");
      display.setTextColor(WHITE,BLACK);
      display.setCursor(0,40);
      display.println("[A2] SpeedMeasure");
      display.display();
    }
    if(Function_Key == 3)
    {
      Function = 3;
      display.setTextColor(WHITE,BLACK); // 'inverted' text
      display.setCursor(0,20);
      display.println("[A0] ParameterCorrect");
      display.setTextColor(BLACK, WHITE);
      display.setCursor(0,40);
      display.println("[A2] SpeedMeasure");
      display.display();
    }
    if(Function_Key == 2)
    {
      
      START = Function;
      display.clearDisplay();
      Function_Key = 0;
      Function = 0;
    }
  }
//参数修改模式
  if(START == 1)
  {display.clearDisplay();
      display.setTextColor(WHITE,BLACK); // 'inverted' text
      display.setCursor(0,17);
      display.println("Please Enable The Motor");
      display.setCursor(0,40);
      display.println("[A2] START [A3] EXIT");
      display.display();
      Function_Key = Key_Scan();

      if(Function_Key == 3)
      {
  //    
        Function = 3;
        display.clearDisplay();
        display.setCursor(0,17);
        display.println(" Calculating ...");
        display.setCursor(0,40);
        display.println("[A2] START [A3] EXIT");
        display.display();
      }
      if(Function_Key == 4)
      {
         START = 0;
         display.clearDisplay();
         View_Main();
         Function = 0;
      }
      if(Function == 3)
      {
          MsTimer2::start();Count_Time = 0;
          Count_Infrard = analogRead(19);
          Value_High = Count_Infrard;
          Value_Low = Count_Infrard;
          while(Count_Time < 1000)
          {
            Count_Infrard = analogRead(19);
            if(Count_Infrard > Value_High)
            {
                Value_High = Count_Infrard;
            }
           if(Count_Infrard < Value_Low)
           {
              Value_Low = Count_Infrard;
           }   
              Serial.print(Count_Time);Serial.print('\n');
          }
          MsTimer2::stop();
         //  Serial.print(Count_Time);Serial.print('\n');
          Count_Time = 0;
         //  Serial.print(Count_Time);Serial.print('\n');
          display.clearDisplay();
          display.setCursor(0,17);
          display.println("HIGH");
          display.setCursor(35,17);
          display.println(Value_High - 20);
          display.setCursor(0,27);
          display.println("LOW");
          display.setCursor(35,27);
          display.println(Value_Low + 20);
          display.setCursor(0,40);
          display.println("[A2] YES [A3] NO");
          display.display();
          Function_Key = 0;
          while(Function_Key != 3 && Function_Key != 4 )
          {
            Function_Key = Key_Scan();Serial.print(Function_Key);Serial.print('\n');
          }
          
          if(Function_Key == 4)
          {
            Function_Key = 0;
            Function = 0;Serial.print(Function_Key);Serial.print('\n');
            display.setTextColor(WHITE,BLACK); // 'inverted' text
            display.setCursor(0,17);
            display.println("Please Enable The Motor");
            display.setCursor(0,40);
            display.println("[A2] START [A3] EXIT");
            display.display();delay(1000);delay(1000);
          }
          if(Function_Key == 3)
          {Serial.print(Function_Key);Serial.print('\n');delay(1000);
            Value_Change_Low = Value_Low + 20;
            Value_Change_High = Value_High - 20;
            Function = 0;
            Function_Key = 0;
            
          }
          

      }
  
  
  }

  //测速模式
   if(START == 3)
  {
      display.setTextColor(WHITE,BLACK); // 'inverted' text
      display.setCursor(0,17);
      display.println("Circle:");
      display.setTextColor(WHITE,BLACK);
      display.setCursor(0,27);
      display.println("Speed:");
      display.setCursor(0,40);
      display.println("[A0] Start [A1] None [A2] Stop  [A3] Exit");
      display.display();
      Function_Key = Key_Scan();
   //   Serial.print(Function_Key);
      if(Function_Key == 4)
      {
         START = 0;
        display.clearDisplay();
        View_Main();
        Function = 0;
      }
      if(Function_Key == 3 )
      {
        Function = 3;
      }
      if(Function_Key == 1)
   
      {
        Function = 1; 
        display.clearDisplay();
        display.setTextColor(WHITE,BLACK);
        display.setCursor(0,0);
        display.println("           ");
            
        display.setTextColor(WHITE,BLACK);
        display.setCursor(40,17);
        display.println("          ");
         display.setCursor(40,27);
          display.println("               ");
         display.display(); 
      }
      if(   Function == 1)
      {
display.setTextColor(WHITE,BLACK);
        display.setCursor(0,0);
        display.println(Count_Time);
            
        display.setTextColor(WHITE,BLACK);
        display.setCursor(40,17);
        display.println(Count_Motor);
         display.display();
      }
      if(Function == 3)
      {         
        Function = 3;  
        Count_Time = 0;
        Beign_Count = 0;
        Status_Motor = 0;
        MsTimer2::stop();
        
      }
    //施密特触发器
    if(Count_Infrard < Value_Change_Low && Status_Motor == 0 && Function == 1)
    {
      if(Beign_Count == 0)
      {//复位工作
        Beign_Count = 1;//开启计数模式
        Count_Motor = 0;Status_Motor = 1;
        MsTimer2::start();
        Count_Time = 0;
       }
      else{
        //Serial.print("111");
          Status_Motor = 1;
       }
    }
    else if(Count_Infrard > Value_Change_High && Status_Motor == 1 && Beign_Count == 1  && Function == 1)
    {
     //Serial.print("222");
         Status_Motor = 0; 
         Count_Motor ++;
  //       Serial.print(Count_Motor);Serial.print("  ");
         Serial.print(Count_Motor);Serial.print('\n');
         if(Count_Motor == 30)
         {
          display.setCursor(40,27);
          display.println(1800/((double) (Count_Time))*100);
          display.setCursor(55,27);
          display.println("rad/min ");
                display.display();
   //       Serial.print("Time is ");Serial.print((double)(Count_Time)/100);Serial.print("s ");Serial.print('\n');
    //      Serial.print("Speed is ");Serial.print(1800/((double) (Count_Time))*100);Serial.print("rad/min ");Serial.print('\n');
          Beign_Count = 0;
          MsTimer2::stop();
          Function = 3;
          }
  
     }
  } 
  }  
}

/**************************************
 * 函数名称：主界面显示函数
 * 参数：无
 * 功能：显示功能选择界面
 */

void View_Main(void)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Menu");
  display.setCursor(0,20);
  display.println("[A0] ParameterCorrect");
  display.setCursor(0,40);
  display.println("[A2] SpeedMeasure");
  display.display();
}
/**************************
 * 函数名称：按键扫描
 * 返回参数：按键值
 * 说明：1-4分别代表四个按钮值，0代表没有按钮。
 */
int Key_Scan(void)
{
  int key_1;
  int key_2;
  int key_3;
  int key_4;
  key_1 = analogRead(14);
  key_2 = analogRead(15);
  key_3 = analogRead(16);
  key_4 = analogRead(17);  
  if(key_1 < 20)
  {
    return 1;  
  }
  else if(key_2 < 20)
  {
    return 2;  
  }
  else if(key_3 < 20)
  {
    return 3;  
  }
  else if(key_4 < 20)
  {
    return 4;  
  }
  else 
  {
    return 0;  
  }
  
}



