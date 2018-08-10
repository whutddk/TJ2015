/*****
****快速反馈系统 C 文件
******用于灯光，蜂鸣器控制
****
****2014 11 28 李锐戈
2015 1 24 李锐戈
*/
#include "common.h"
#include "include.h"


void signal_init()        //将所有信号被部分初始化
{
  GPIO_InitTypeDef gpio_inittype;
  gpio_inittype.GPIO_PTx = PTE;
  gpio_inittype.GPIO_Pins = GPIO_Pin25 + GPIO_Pin26 + GPIO_Pin27 + GPIO_Pin28;
  gpio_inittype.GPIO_Dir = DIR_OUTPUT;
  gpio_inittype.GPIO_Output = OUTPUT_L;
  gpio_inittype.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_inittype);

  gpio_inittype.GPIO_PTx = PTA;
  gpio_inittype.GPIO_Pins =  GPIO_Pin5 + GPIO_Pin6 + GPIO_Pin7  
                             + GPIO_Pin16 + GPIO_Pin17;
  gpio_inittype.GPIO_Dir = DIR_OUTPUT;
  gpio_inittype.GPIO_Output = OUTPUT_L;
  gpio_inittype.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_inittype);
  
  gpio_inittype.GPIO_PTx = PTC;
  gpio_inittype.GPIO_Pins = GPIO_Pin11;
  gpio_inittype.GPIO_Dir = DIR_OUTPUT;
  gpio_inittype.GPIO_Output = OUTPUT_H;
  gpio_inittype.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_inittype);
  
  
  //out_all();
}


void light_all()
{
  
  LED0(ON);
  LED1(ON);
  LED2(ON);
  LED3(ON);
  LED4(ON);
  LED5(ON);
  LED6(ON);
  LED7(ON);
  LED8(ON);
}

void out_all()
{
  LED0(OFF);
  LED1(OFF);
  LED2(OFF);
  LED3(OFF);
  LED4(OFF);
  LED5(OFF);
  LED6(OFF);
  LED7(OFF);
  LED8(OFF);
}
