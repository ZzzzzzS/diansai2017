#include "check.h"
#include "include.h"

void PORTA_IRQHandler();
void DMA0_IRQHandler();


void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 28;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
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
  
  set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
  set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //���� DMA0 ���жϷ�����Ϊ PORTA_IRQHandler

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
  
  if(count==0)
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

void  ConvertImg(uint8 image1[CAMERA_H][CAMERA_W], uint8 image2[CAMERA_H][CAMERA_W])
{
  int i=0,j=0;
  int x=0,y=0;
  float k1=-0.000023,k2=-0.000023;//-0.00000230,k2=-0.00000120;
  for(i=-60;i<60;i++)
    for(j=-80;j<80;j++)
    {
      x=(int)(i*(1+k1*i*i+k2*j*j))+60;
      y=(int)(j*(1+k1*i*i+k2*j*j))+80;
      //*(*(image2+(i+60)*160)+(j+80))=*(*(image1+x*160)+y);
      image2[i+60][j+80]=image1[x][y];
    }      
}