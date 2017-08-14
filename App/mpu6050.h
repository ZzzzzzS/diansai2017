/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：MPU6050.h
 * 描述         ：MPU6050驱动头文件
 *
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：野火嵌入式开发工作室
**********************************************************************************/	


#ifndef __MPU6050_H__
#define __MPU6050_H__

//****************************************
#define   I2C_n   I2C1
#define   baud_n   400 * 1000
extern uint8 data;
extern int g_angle_x;
//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	        0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	        0x3B    //X轴加速度  加速度
#define	ACCEL_XOUT_L	        0x3C
#define	ACCEL_YOUT_H	        0x3D    //X轴加速度
#define	ACCEL_YOUT_L	        0x3E
#define	ACCEL_ZOUT_H	        0x3F    //X轴加速度
#define	ACCEL_ZOUT_L	        0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43    //X轴角速度  陀螺仪
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45    //X轴角速度
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47    //X轴角速度
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	        0x68	//IIC写入时的地址字节数据，+1为读取



extern int angle_x;
extern int angle_y;
extern int angle_z;

extern uint8 mpu6050_init(void);

extern int16 mpu6050_ACCEL_X_data();
extern int16 mpu6050_ACCEL_Y_data();
extern int16 mpu6050_ACCEL_Z_data();

extern int16 mpu6050_GYRO_X_data();
extern int16 mpu6050_GYRO_Y_data();
extern int16 mpu6050_GYRO_Z_data();

extern int16 mpu6050_TEMP_OUT_data();
extern int Get_X_Angle();
extern int16 Angle_z();
#endif
