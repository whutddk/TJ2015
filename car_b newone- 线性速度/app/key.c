/*****
****开跑前选择参数
******
****
****2015 5 9 王佳龙
*/

#include "common.h"
#include "include.h"
uint16 SPEED_MAX = 1600;
uint16 SPEED_MIN = 1400;
uint16 SPEED_MID = 1000;
uint8 key_break = 1;      //按键循环标志位
uint8 switch_select = 1;  //干簧管循环标志位
void key_select()
{
  
  while(key_break)
  {
    if(PTD7_I == 0)            //左下键
    {
      key_delay();
      while(PTD7_I == 0);
      if(PTD7_I == 1)
      {
        key_delay();
        while(PTD7_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        SPEED_MIN=SPEED_MIN-100;
        SPEED_MID -= 100;
      }  
    }
    
    if(PTD8_I == 0)            //右下键
    {
      key_delay();
      while(PTD8_I == 0);
      if(PTD8_I == 1)
      {
        key_delay();
        while(PTD8_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        SPEED_MIN=SPEED_MIN-100;
        SPEED_MID -= 100;
      }  
    }
    
    if(PTD9_I == 0)             //左上键
    {
      key_delay();
      while(PTD9_I == 0);
      if(PTD9_I == 1)
      {
        key_delay();
        while(PTD9_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        SPEED_MAX=SPEED_MAX+100;
        SPEED_MID += 100;
      }  
    }
    
    if(PTD10_I == 0)            //中间键
    {
      key_delay();
      while(PTD10_I == 0);
      if(PTD10_I == 1)
      {
        key_delay();
        while(PTD10_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        key_break = 0;
      }  
    }
    
    if(PTD11_I == 0)            //右上键
    {
      key_delay();
      while(PTD11_I == 0);
      if(PTD11_I == 1)
      {
        key_delay();
        while(PTD11_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        SPEED_MAX=SPEED_MAX + 100;
        SPEED_MID += 100;
      }  
    }
  }
  LPLD_GPIO_Toggle_b(PTA, 7);
}

void gpio_key_init()
{
  GPIO_InitTypeDef gpio_init_struct;
  gpio_init_struct.GPIO_PTx = PTD;      
  gpio_init_struct.GPIO_Pins = GPIO_Pin7|GPIO_Pin8|GPIO_Pin9|GPIO_Pin10|GPIO_Pin11;     
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;        //输入
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_DIS; //内部上拉|不产生中断
  gpio_init_struct.GPIO_Output=OUTPUT_H;
  LPLD_GPIO_Init(gpio_init_struct);
}

void key_delay()
{
  uint16 n;
  for(n=1000;n>0;n--);
}
