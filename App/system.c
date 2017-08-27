#include "include.h"
#include "system.h"

void MainLoop();

void SystemInit()
{
  DisableInterrupts;      //��ʼ��ǰ�ر������ж�(��ʵû��Ҫ)
  OLED_Init();
  AimPositionInit();
  PIDInit();
  ControlInit();
  OLED_Print(Position(Line2),"�����ʼ�����");
  DELAY_MS(500);
  init_LED();
  Init_Key();
  PathInit();
  UART_Init();
  gpio_init(PTA8,GPO,0);
  while(!mpu6050_init()); //һֱ�ȴ���ʼ��
  OLED_Print(Position(Line3),"�����ǳ�ʼ�����");
  lptmr_timing_ms(50);    //�趨�ж�ʱ��
  set_vector_handler(LPTMR_VECTORn, MainLoop);//�趨�жϷ�����
  EnableInterrupts;
  disable_irq(LPTMR_IRQn);    //�ȹر��ж�
  StepMotorInit();            //���������ʼ��
  OLED_CLS();
  OLED_Print(Position(Line1),"����ˮƽУ׼");
  ResetGyro();                //����ˮƽ
  OLED_CLS();
  OLED_Print(Position(Line4),"У׼���");
  
  
  
}

void GetSystemReady()
{
  /*while(1)
  {
    printf("%d %d %d\n", mpu6050_ACCEL_X_data(), mpu6050_ACCEL_Y_data(),mpu6050_ACCEL_Z_data());
    
  }*/
  
  CheckInit();        //��ʼ������ͷ,��Ϊ֮ǰ�߲���������������ͷ,��������ͷ��ʼ������
  OLED_Print(Position(Line1),"����ͷ��ʼ�����");
  DELAY_MS(500);
  OLED_Interface();   //OLEDѡ��ģʽ
  OLED_CLS();
  MainBall.CurrentAimPosition=PathBase.StoredPath[PathBase.Function][PathBase.CurrentPositionCounter];
  MainBall.CurrentBallPosition.H=0; //�Ȱ���������
  OLED_Print(Position(Line1),"ϵͳ׼������");
  OLED_Print(Position(Line2),"�����С��");
  while(MainBall.CurrentBallPosition.H==0)//�������һֱ����,֤��һֱû�з���,��һֱ�ȴ�
  {
    GetDeta();//�ɼ�ͼ��
    ConvertImg(img,imgFixed);//�任ͼ��
    GetPosition();//�ҵ����λ��
  }
  OLED_CLS();
  OLED_Print(Position(Line1),"��ʼ!");
  if(PathBase.Function==UserControl)//�ж����Զ���·�����ټ�һ����ʾ�Ļ�
  {
    OLED_Print(Position(Line3),"���ô�����������");
    OLED_Print(Position(Line4),"�ı�С��Ŀ��λ��");
    MainBall.CurrentAimPosition=PathBase.AimPosition[Line2Middle];
  }
  enable_irq(LPTMR_IRQn);//��ʼ�����ж�,��ʼ�����
}

void SystemUpdate()
{
  GetDeta();//�ɼ�ͼ��
  ConvertImg(img,imgFixed);//ת��ͼ��
  //vcan_sendimg(imgbuff, sizeof(imgbuff));//����ͼ��,ɽ����λ�� 
  //vcan_sendimg(imgFixed, sizeof(imgFixed));//����ͼ��,��������λ��
  if(sendflag)//�����������Ƿ�����Ϣ,Ĭ�ϲ�����,Ҳ��ò�Ҫ����
  {
  printf("position: %d %d  ",MainBall.CurrentBallPosition.H,MainBall.CurrentBallPosition.W);
  printf("Error %d %d  ",ServoBase[H].PidBase.ErrorPosition[Now_Error],ServoBase[W].PidBase.ErrorPosition[Now_Error]);
  printf("speed %d %d\n",MainBall.CurrentBallSpeed.H,MainBall.CurrentBallSpeed.W);
  }
  GetPosition();//���������
  CalculatePosition();//��������
  PIDControlPositional(&ServoBase[W]);//PID����W��
  PIDControlPositional(&ServoBase[H]);//PID����H��
  ControlOut();//��������
}

void MainLoop()
{
  if(PathBase.Function!=UserControl)//�жϲ����Զ���·�����Զ��趨·��
    SetAimPosition();//�趨·��
  LED_Interface();  //led����ʾ,ûʲô��
  if(PathBase.Function==UserControl)//������Զ���·���ͽ��մ�������Ϣ
  {
    GetRemoteControl();//����ң����
    GetTouch();//���մ�����
  }
  System_Interface();//OLED��ʾ����
  LPTMR_Flag_Clear();//���жϱ�־λ
}