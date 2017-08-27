/**********����˵��*********/
    /****����****/
/*system.c:ϵͳ��ʼ��,���Ƶ�
    SystemInit()        ���ϵͳ��ʼ��
    GetSystemReady()    ���ϵͳ��ʽ����ǰ�ĸ���׼����ѡ��ģʽ��
    SystemUpdate()      ϵͳ��������ʱ��ѭ�����൱��while(1)
    MainLoop()          ϵͳ��������ʱ���ж�,�൱��LPTMR_IQRHandler()

check.c:����ͷ��ʼ��,�ɼ�,�ҵ��
    CheckInit()         ����ͷ��ʼ��
    GetDeta()           ����ͷ�ɼ�ͼ��
    ConvertImg()        ��͸�ӱ仯����ͼ��
    GetPosition()       �����������λ��
    PORTA_IRQHandler()  ����ͷ�ɼ����ж�,��
    DMA0_IRQHandler()   ����ͷDMA�ɼ��ж�,��

control.c:�����ʼ��,�������,PID����,PID����������
    ControlInit()       �����ʼ��
    PIDInit()           PID������ʼ��,����������������
    ControlOut()        ���յ������
    PIDControl(servo *Base)             ����ʽPID����,���ǲ��õ���λ��ʽ
    PIDControlPositional(servo *Base)   λ��ʽPID����,���Ǿ��ǲ�������PID

PositionControl.c:����Ҫ��Ķ���·��,�ж��Ƿ�Ŀ���,�趨Ŀ����
    PathInit()          ��ʼ����õĹ涨·��
    AimPositionInit()   ��ʼ��9��Ŀ����λ��
    CalculatePosition() ���㵱ǰλ�ú�Ŀ��λ�õ����,��ǰ�ٶȵ�
    SetPID(Servo* Base) ����λ������޸�PID��ֵ,������������÷ֶ�PID
    SetAimPosition()    �ж��Ƿ񵽴��,���趨�µ�Ŀ���
    AtPositionNonBlocking(position base)����Ŀ����Χ�����̷���true
    AtPosition(position base) ����Ŀ���,����Ŀ���С��Χ���ȶ�2��ŷ���true

peripheral.c:����,OLED����,�����ǵ�ƽ�ȸ��ӹ��ܵ�
    OLED_Interface()    ϵͳ����ǰOLED��ʾ����
    AdvanceFunction2ConfigInterface() ѡ�з��ӹ���2���趨·������
    System_Interface()  ϵͳ��������ʱ��ʾ�Ľ���
    ResetGyro()         �����ǵ�ƽ����
    GetTouch()          �ɼ�����������Ϣ
    GetRemoteControl()  �ɼ�ң������Ϣ
    uart4_handler()      �жϽ���������Ϣ
    SystemReset()       ϵͳ��λ,ûʲô��
    System_Error(char Error_Number) ϵͳ�������ϵĴ�����,ûʲô��,�����ö��Կ�����OLED����ʾ����

OLED.c:      OLED��Ļ��
OLED_Fonts.h:OLED�����
mpu6050.c:   �����ǿ�
touch.c:     ��������*/

    /****���ݽṹ****/
/*������Ҫ��data.h��*/



