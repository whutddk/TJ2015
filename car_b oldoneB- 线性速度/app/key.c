/*****
****����ǰѡ�����
******
****
****2015 5 9 ������
*/

#include "common.h"
#include "include.h"
uint16 SPEED_MAX = 1100;
uint16 SPEED_MIN = 900;
uint8 key_break = 1;      //����ѭ����־λ
uint8 switch_select = 1;  //�ɻɹ�ѭ����־λ
void key_select()
{
  /*while(switch_select)
  {
  if(PTD7_I == 0)            //���¼�   ��ѡ��ɻɹ�
  {
  key_delay();
  while(PTD7_I == 0);
  if(PTD7_I == 1)
  {
  key_delay();
  while(PTD7_I == 0);
  LPLD_GPIO_Toggle_b(PTA, 7);
  switch_select = 0 ;
}  
}
  if(PTD8_I == 0)            //���¼�   ѡ��ɻɹ�
  {
  key_delay();
  while(PTD8_I == 0);
  if(PTD8_I == 1)
  {
  key_delay();
  while(PTD8_I == 0);
  LPLD_GPIO_Toggle_b(PTA, 7);
  switch_select = 0;
  switch_init_gpio();   //�ɻɹܼ���ʼ��
}  
}
}*/
  while(key_break)
  {
    if(PTD7_I == 0)            //���¼�
    {
      key_delay();
      while(PTD7_I == 0);
      if(PTD7_I == 1)
      {
        key_delay();
        while(PTD7_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        SPEED_MAX=SPEED_MAX-100;
        SPEED_MIN=SPEED_MIN-100;
      }  
    }
    
    if(PTD8_I == 0)            //���¼�
    {
      key_delay();
      while(PTD8_I == 0);
      if(PTD8_I == 1)
      {
        key_delay();
        while(PTD8_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        SPEED_MAX=SPEED_MAX-100;
        SPEED_MIN=SPEED_MIN-100;
      }  
    }
    
    if(PTD9_I == 0)             //���ϼ�
    {
      key_delay();
      while(PTD9_I == 0);
      if(PTD9_I == 1)
      {
        key_delay();
        while(PTD9_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        SPEED_MAX=SPEED_MAX+100;
        SPEED_MIN=SPEED_MIN+100;
        
      }  
    }
    
    if(PTD10_I == 0)            //�м��
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
    
    if(PTD11_I == 0)            //���ϼ�
    {
      key_delay();
      while(PTD11_I == 0);
      if(PTD11_I == 1)
      {
        key_delay();
        while(PTD11_I == 0);
        LPLD_GPIO_Toggle_b(PTA, 7);
        SPEED_MIN=SPEED_MIN+100;
        SPEED_MAX=SPEED_MAX+100;
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
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;        //����
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_DIS; //�ڲ�����|�������ж�
  gpio_init_struct.GPIO_Output=OUTPUT_H;
  LPLD_GPIO_Init(gpio_init_struct);
}

void key_delay()
{
  uint16 n;
  for(n=1000;n>0;n--);
}
