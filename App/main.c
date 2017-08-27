/**********工程说明*********/
    /****函数****/
/*system.c:系统初始化,控制等
    SystemInit()        完成系统初始化
    GetSystemReady()    完成系统正式启动前的各种准备，选择模式等
    SystemUpdate()      系统正常运行时的循环，相当于while(1)
    MainLoop()          系统正常运行时的中断,相当于LPTMR_IQRHandler()

check.c:摄像头初始化,采集,找点等
    CheckInit()         摄像头初始化
    GetDeta()           摄像头采集图像
    ConvertImg()        逆透视变化矫正图像
    GetPosition()       计算球的坐标位置
    PORTA_IRQHandler()  摄像头采集场中断,勿动
    DMA0_IRQHandler()   摄像头DMA采集中断,勿动

control.c:舵机初始化,舵机控制,PID控制,PID参数调整等
    ControlInit()       舵机初始化
    PIDInit()           PID参数初始化,调参在这个函数里调
    ControlOut()        最终电机控制
    PIDControl(servo *Base)             增量式PID控制,我们采用的是位置式
    PIDControlPositional(servo *Base)   位置式PID控制,我们就是采用这种PID

PositionControl.c:储存要求的多种路径,判断是否到目标点,设定目标点等
    PathInit()          初始化存好的规定路径
    AimPositionInit()   初始化9个目标点的位置
    CalculatePosition() 计算当前位置和目标位置的误差,当前速度等
    SetPID(Servo* Base) 根据位置误差修改PID的值,在这个函数设置分段PID
    SetAimPosition()    判断是否到达点,并设定新的目标点
    AtPositionNonBlocking(position base)到达目标点大范围内立刻返回true
    AtPosition(position base) 到达目标点,且在目标点小范围内稳定2秒才返回true

peripheral.c:蓝牙,OLED界面,陀螺仪调平等附加功能等
    OLED_Interface()    系统启动前OLED显示界面
    AdvanceFunction2ConfigInterface() 选中发挥功能2的设定路径界面
    System_Interface()  系统正常运行时显示的界面
    ResetGyro()         陀螺仪调平函数
    GetTouch()          采集触摸屏的信息
    GetRemoteControl()  采集遥控器信息
    uart4_handler()      中断接收蓝牙信息
    SystemReset()       系统软复位,没什么用
    System_Error(char Error_Number) 系统发生故障的处理函数,没什么用,就是让断言可以在OLED上显示出来

OLED.c:      OLED屏幕库
OLED_Fonts.h:OLED字体库
mpu6050.c:   陀螺仪库
touch.c:     触摸屏库*/

    /****数据结构****/
/*数据主要在data.h中*/



