#include "check.h"
#include "include.h"

void PORTA_IRQHandler();
void DMA0_IRQHandler();


void PORTA_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 28;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif


}

void DMA0_IRQHandler()
{
    camera_dma();
}

void CheckInit()
{
  camera_init(imgbuff);//初始化摄像头
  
  set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
  set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 PORTA_IRQHandler
  
  NVIC_SetPriorityGrouping(6);//修改中断优先级等,这一行以下几行都勿动
  
  NVIC_SetPriority(PORTA_IRQn,0);
  NVIC_SetPriority(DMA0_IRQn,1);
  NVIC_SetPriority(LPTMR_IRQn,2);

}

void GetDeta()
{
  camera_get_img(); //采集图像
  img_extract(img, imgbuff, CAMERA_SIZE);//解压图像
}

void GetPosition()//重心法寻找目标点
{
  
  MainBall.LastBallPosition=MainBall.CurrentBallPosition;
  MainBall.LastBallSpeed=MainBall.CurrentBallSpeed;
  
  unsigned int H=0;
  unsigned int W=0;
  unsigned int count=0;
  for(char i=MINH;i<MAXH;i++)
  {
    for(char j=MINW;j<MAXW;j++)
    {
      if(!imgFixed[i][j])
      {
        //printf("      %d %d\n",i,j);
        H+=i;
        W+=j;
        count++;
      }
    }
  }
  
  if(count==0)//判断除数为零,既没找到点的特殊情况
  {
    MainBall.CurrentBallPosition=MainBall.LastBallPosition;
  }
  else
  {
    MainBall.CurrentBallPosition.H=H/count;
    MainBall.CurrentBallPosition.W=W/count;
  }
  
  MainBall.CurrentBallSpeed.H=(MainBall.CurrentBallPosition.H - MainBall.LastBallPosition.H);
  MainBall.CurrentBallSpeed.W=(MainBall.CurrentBallPosition.W - MainBall.LastBallPosition.W);
}

void  ConvertImg(uint8 image1[CAMERA_H][CAMERA_W], uint8 image2[CAMERA_H][CAMERA_W])//逆透视变换
{
  int i=0,j=0;
  int x=0,y=0;
  float k1=-0.000023,k2=-0.000025;//-0.00000230,k2=-0.00000120;//发现图不对可修改这两个参数来调整
  for(i=-60;i<60;i++)
    for(j=-80;j<80;j++)
    {
      x=(int)(i*(1+k1*i*i+k2*j*j))+60;
      y=(int)(j*(1+k1*i*i+k2*j*j))+80;
      //*(*(image2+(i+60)*160)+(j+80))=*(*(image1+x*160)+y);
      image2[i+60][j+80]=image1[x][y];
    }      
}