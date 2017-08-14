#include "include.h"

uint8 DATA_H,DATA_L;
uint8 data;
int g_angle_x;
int angle_x;
int angle_y;
int angle_z;

uint8 mpu6050_init()                                   //mpu6050初始化
{
  DELAY_MS(500);
  i2c_init(I2C_n, baud_n);
  
  i2c_write_reg(I2C_n,SlaveAddress,PWR_MGMT_1,0x00);     //解除休眠状态
  i2c_write_reg(I2C_n,SlaveAddress,SMPLRT_DIV,0x07);
  i2c_write_reg(I2C_n,SlaveAddress,CONFIG,0x06);

  //设置转换后数据的精度   0x08 最大值为 8192 (2^13)
  i2c_write_reg(I2C_n,SlaveAddress,GYRO_CONFIG,0x18);    
  i2c_write_reg(I2C_n,SlaveAddress,ACCEL_CONFIG,0x01);   

  data = i2c_read_reg(I2C_n,SlaveAddress,WHO_AM_I);
  if(data == 0x68)
    return 1;
  else 
    return 0;
}

//*********读 加速度计X轴 数据*******************
int16 mpu6050_ACCEL_X_data()                                    
{
  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,ACCEL_XOUT_H);
  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,ACCEL_XOUT_L);
  DELAY_MS(5);
  return (DATA_H<<8)+DATA_L;
}
//*********读 加速度计Y轴 数据*******************
int16 mpu6050_ACCEL_Y_data()                                    
{
  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,ACCEL_YOUT_H);
  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,ACCEL_YOUT_L);
  DELAY_MS(5);
  return (DATA_H<<8)+DATA_L;
}
//*********读 加速度计Z轴 数据*******************
int16 mpu6050_ACCEL_Z_data()                                    
{
  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,ACCEL_ZOUT_H);
  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,ACCEL_ZOUT_L);
  DELAY_MS(5);
  return (DATA_H<<8)+DATA_L;
}
//*********读 陀螺仪计X轴 数据*******************
int16 mpu6050_GYRO_X_data()                                    
{
  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,GYRO_XOUT_H);
  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,GYRO_XOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 陀螺仪计Y轴 数据*******************
int16 mpu6050_GYRO_Y_data()                                    
{
  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,GYRO_YOUT_H);
  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,GYRO_YOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 陀螺仪计Z轴 数据*******************
int16 mpu6050_GYRO_Z_data()                                    
{
  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,GYRO_ZOUT_H);
  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,GYRO_ZOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 温度 数据*******************
int16 mpu6050_TEMP_OUT_data()                                    
{
  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,TEMP_OUT_H);
  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,TEMP_OUT_L);
  return (DATA_H<<8)+DATA_L;
}

int Get_X_Angle()       //角速度
{
    int angle=0;
    angle=mpu6050_GYRO_X_data()/16;
    g_angle_x=angle+3;
    return g_angle_x;
}

int MPU6050_Get_Angle() 
{ 
        float temp;       
        float res=0;
        int x=mpu6050_ACCEL_X_data();
        int y=mpu6050_ACCEL_Y_data();
        int z=mpu6050_ACCEL_Z_data();
        
        temp=y/sqrt((x*x+z*z));            
        res=atan(temp);                   
        
        return (int)(res*180/3.14);//把弧度转换成角
}

