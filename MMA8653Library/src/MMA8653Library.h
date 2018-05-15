#ifndef MMA8653Library_h //标志头文件格式，防止 头文件 被重复引用。
#define MMA8653Library_h

 #if defined(ARDUINO) && ARDUINO >= 100 //判断版本号的，兼容低版本IDE
  #include "Arduino.h"
  #else
  #include "WProgram.h"
  #endif

// The SparkFun breakout board defaults to 1, set to 0 if SA0 jumper on the bottom of the board is set
#define MMA8452_ADDRESS 0x1D  // 0x1D if SA0 is high, 0x1C if low

//Define a few of the registers that we will be accessing on the MMA8452
#define OUT_X_MSB 0x01
#define XYZ_DATA_CFG  0x0E
#define WHO_AM_I   0x0D
#define CTRL_REG1  0x2A

#define GSCALE 2 // Sets full-scale range to +/-2, 4, or 8g. Used to calc real g values. 将满量程范围设置为+/- 2,4或8g。
void readAccelData(int *destination);
void initMMA8653();
void MMA8452Standby();
void MMA8452Active();
void readRegisters(byte addressToRead, int bytesToRead, byte * dest);
byte readRegister(byte addressToRead);
void writeRegister(byte addressToWrite, byte dataToWrite);
void data(float *accelG);
float  MMA8653_x_Gdata();
float  MMA8653_y_Gdata();
float  MMA8653_z_Gdata();
float  MMA8653_x_angle();
float  MMA8653_y_angle();
#endif
