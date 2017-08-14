/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��MPU6050.h
 * ����         ��MPU6050����ͷ�ļ�
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
**********************************************************************************/	


#ifndef __MPU6050_H__
#define __MPU6050_H__

//****************************************
#define   I2C_n   I2C1
#define   baud_n   400 * 1000
extern uint8 data;
extern int g_angle_x;
//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	        0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	        0x3B    //X����ٶ�  ���ٶ�
#define	ACCEL_XOUT_L	        0x3C
#define	ACCEL_YOUT_H	        0x3D    //X����ٶ�
#define	ACCEL_YOUT_L	        0x3E
#define	ACCEL_ZOUT_H	        0x3F    //X����ٶ�
#define	ACCEL_ZOUT_L	        0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43    //X����ٶ�  ������
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45    //X����ٶ�
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47    //X����ٶ�
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	        0x68	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ



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
