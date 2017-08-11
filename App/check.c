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
  camera_init(imgbuff);
  
  set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
  set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 PORTA_IRQHandler

}

void GetDeta()
{
  camera_get_img(); 
  img_extract(img, imgbuff, CAMERA_SIZE);
}

void GetPosition()
{
  
  MainBall.LastBallPosition=MainBall.CurrentBallPosition;
  MainBall.LastBallSpeed=MainBall.CurrentBallSpeed;
  
  unsigned int H=0;
  unsigned int W=0;
  unsigned int count=0;
  for(char i=0;i<CAMERA_H;i++)
  {
    for(char j=0;j<CAMERA_W;j++)
    {
      if(img[i][j])
      {
        H+=i;
        W+=j;
        count++;
      }
    }
  }
  
  if(count==0)
  {
    MainBall.CurrentBallPosition.W=40;
    MainBall.CurrentBallPosition.H=30;
  }
  else
  {
    MainBall.CurrentBallPosition.H=H/count;
    MainBall.CurrentBallPosition.W=W/count;
  }
  
  MainBall.CurrentBallSpeed.H=(MainBall.CurrentBallPosition.H - MainBall.LastBallPosition.H);
  MainBall.CurrentBallSpeed.W=(MainBall.CurrentBallPosition.W - MainBall.LastBallPosition.W);
}