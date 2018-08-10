/*****
****干簧管检测
******
****
****2015 4 1 王佳龙
*/

#include "common.h"
#include "include.h"
uint8 switch_count=0,switch_flag=0;

void switch_init_gpio()
{
  GPIO_InitTypeDef gpio_init_struct;
  gpio_init_struct.GPIO_PTx = PTC;      
  gpio_init_struct.GPIO_Pins = GPIO_Pin13|GPIO_Pin12|GPIO_Pin10|GPIO_Pin9|GPIO_Pin8|GPIO_Pin7;     
  gpio_init_struct.GPIO_Dir = DIR_INPUT;        //输入
  gpio_init_struct.GPIO_Output=OUTPUT_H;
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_FA;     //内部上拉|下降沿中断
  gpio_init_struct.GPIO_Isr = portb_isr;        //中断函数
  LPLD_GPIO_Init(gpio_init_struct);
  LPLD_GPIO_EnableIrq(gpio_init_struct);             //使能中断
  /********两个中断会互相影响***********/
  /*gpio_init_struct.GPIO_PTx = PTA;      
  gpio_init_struct.GPIO_Pins = GPIO_Pin28|GPIO_Pin29;     
  gpio_init_struct.GPIO_Dir = DIR_INPUT;        //输入
  gpio_init_struct.GPIO_Output=OUTPUT_H;
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_FA;     //内部上拉|下降沿中断
  gpio_init_struct.GPIO_Isr = portb_isr;        //中断函数
  LPLD_GPIO_Init(gpio_init_struct);
  LPLD_GPIO_EnableIrq(gpio_init_struct);             //使能中断       */
}

void portb_isr()
{
  /*
  if(!LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin28))
  {
      switch_count ++;                            
  }
  
  if(!LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin29))
  {
      switch_count ++;                             
  }
  */
  if(!LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin13))
  {
      switch_count ++;                             
  }
  
  if(!LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin12))
  {
      switch_count ++;                             
  }
  
  if(!LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin10))
  {
      switch_count ++;                            
  }
  
  if(!LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin9))
  {
      switch_count ++;  
     
  }
  
    if(!LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin8))
  {

      switch_count ++;       
  }
  
    if(!LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin7))
  {
      switch_count ++;  
      
  }
 switch_delay();
  if (switch_count >= 3)  //switch_flag ++; 
                          
  {    
  //if((PTC7_I==1)&&(PTC8_I==1)&&(PTC9_I==1)&&(PTC10_I==1))
  //{     
    LPLD_GPIO_Toggle_b(PTA, 4);
    LPLD_GPIO_Toggle_b(PTA, 5);
    LPLD_GPIO_Toggle_b(PTA, 6);
    LPLD_GPIO_Toggle_b(PTA, 7);      
   //}
   }
  switch_count = 0;
}
void switch_delay()
{
  uint32 a,b,c;
  for (a=1010;a>0;a--)
    for(b=1000;b>0;b--)
      for(c=10;c>0;c--);
}