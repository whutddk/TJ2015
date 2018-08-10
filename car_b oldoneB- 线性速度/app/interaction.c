/******�˻����� C �ļ�
*****����LCD5110 ���� ���뿪��
*����� 2014 12 30
*
******/

#include "common.h"
#include "include.h"

/**

D7 D9   D8      D11 D10//����
CLK C6    DIN C7   DC C9   CE C8   RST C10
*/

void interaction_init()
{
  //���̳�ʼ��,����
  GPIO_InitTypeDef gpio_inittype;
  gpio_inittype.GPIO_PTx = PTD;
  gpio_inittype.GPIO_Pins = GPIO_Pin7 | GPIO_Pin8 | GPIO_Pin9 | GPIO_Pin10 | GPIO_Pin11;
  gpio_inittype.GPIO_Dir = DIR_INPUT;
  gpio_inittype.GPIO_Output = OUTPUT_H;
  gpio_inittype.GPIO_PinControl = IRQC_DIS | INPUT_PULL_UP ;//����
  LPLD_GPIO_Init(gpio_inittype);
  
  //LCD5110
  gpio_inittype.GPIO_PTx = PTC;
  gpio_inittype.GPIO_Pins = GPIO_Pin6 + GPIO_Pin7 + GPIO_Pin8 + GPIO_Pin9 + GPIO_Pin10 ;
  gpio_inittype.GPIO_Dir = DIR_OUTPUT;
  gpio_inittype.GPIO_Output = OUTPUT_H;
  gpio_inittype.GPIO_PinControl = IRQC_DIS ;
  LPLD_GPIO_Init(gpio_inittype);
 
}


uint8 keyboard_detect() //���̰������Ժ��������ú����޵ȴ��ҽ��ȴ�һ������
{
  uint8 result = 0;
  while(1)
  {
    if (PTD7_I)
    {
      delay(5000);
      if(!PTD7_I)
      {
        result = 1;
        while(!PTD7_I);
        break;
      }
    }
    if (!PTD9_I)
    {
      delay(5000);
      if(!PTD9_I)
      {
        result = 2;
        while(!PTD9_I);
        break;
      }
    }
    if (!PTD8_I)
    {
      delay(5000);
      if(!PTD8_I)
      {
        result = 5;
        while(!PTD8_I);
        break;
      }
    }
    if (!PTD11_I)
    {
      delay(5000);
      if(!PTD11_I)
      {
        result = 3;
        while(!PTD11_I);
        break;
      }
    }
    if (!PTD10_I)
    {
      delay(5000);
      if(!PTD10_I)
      {
        result = 4;
        while(!PTD10_I);
        break;
      }
    }
  }
  return result;
}

/*��Ҫ̫�࣬û��ô��ʱ������*/
//����0Ϊ�������ֶ�����Ԥ��
//ǰ��ģʽ������� //��ģʽ��������
//�������Ƿ����
//�����ų��Լ�

/*
void program_switch()//����LCD���ѡ����׳���
{ 
  uint8 twinkle = 0;
  
  while(1)
  {
           if(twinkle == 1)
        {
             
          twinkle = 0 ;
   
            LCD_set_XY(0, 0) ;
           
            for(twinkle = 0 ; twinkle < 83 ;twinkle ++)//��ʱ
                  {  LCD_write_byte(0, 1);   }   //������Ϊ��˸��
        }
        else
        {
 
             twinkle = 1 ; 
 
              LCD_set_XY(0, 0) ;
              LCD_write_char('T');
              LCD_write_char('E');
              LCD_write_char('S');
              LCD_write_char('T');           
        }
       if ( PTD8_I == 0)
       {
         break;
       }
        
  }
}*/

/*********************************************************** 
�������ƣ�LCDTIME
�������ܣ�Һ����ʾ��
��ڲ�����c	:  ��ʾ���ַ�
���ڲ������� 
�� ע�� 
***********************************************************/
void LCDTIME(void)
{
  uint8 show_temp0, show_temp1, show_temp2, show_temp3;
  LCD_set_XY(0, 0) ;
  LCD_write_char('D');
  LCD_write_char('D');
  LCD_write_char('K');

             /**************
              �ڶ�����ʾ����
             **************/
  if ( this_location >= 0 )
  {
    show_temp0 = (uint8) ((this_location/1000)  + 48 );
    show_temp1 = (uint8) (((this_location%1000)/100) +48 ) ;
    show_temp2 = (uint8) (((this_location%100)/10)  + 48 ); 
    show_temp3 = (uint8) ((this_location%10)  + 48 );

    LCD_set_XY(0, 1) ;
    LCD_write_char('l');
    LCD_write_char('o');
    LCD_write_char('c');
    LCD_write_char('a');
    LCD_write_char('t');
    LCD_write_char('i');
    LCD_write_char('o');
    LCD_write_char(show_temp0);
    LCD_write_char(show_temp1);
    LCD_write_char(show_temp2);
    LCD_write_char(show_temp3);
  }
  else
  {
    show_temp0 = (uint8) (((0-this_location) /1000)  + 48 );
    show_temp1 = (uint8) ((((0-this_location)%1000)/100) +48 ) ;
    show_temp2 = (uint8) ((((0-this_location)%100)/10)  + 48 ); 
    show_temp3 = (uint8) (((0-this_location)%10)  + 48 );

    LCD_set_XY(0, 1) ;
    LCD_write_char('l');
    LCD_write_char('o');
    LCD_write_char('c');
    LCD_write_char('a');
    LCD_write_char('t');
    LCD_write_char('i');
    LCD_write_char('o');
    LCD_write_char('-');
    LCD_write_char('-');
    LCD_write_char(show_temp0);
    LCD_write_char(show_temp1);
    LCD_write_char(show_temp2);
    LCD_write_char(show_temp3);
  }
             /**************
              ��������ʾ����
            **************/

  {
    show_temp0 = (uint8) ((pwm_show/1000)  + 48 );
    show_temp1 = (uint8) (((pwm_show%1000)/100) +48 ) ;
    show_temp2 = (uint8) (((pwm_show%100)/10)  + 48 ); 
    show_temp3 = (uint8) ((pwm_show%10)  + 48 );

    LCD_set_XY(0, 2) ;
    LCD_write_char('p');
    LCD_write_char('w');
    LCD_write_char('m');
    LCD_write_char(':');
    LCD_write_char(' ');
    LCD_write_char(' ');
    LCD_write_char(' ');
    LCD_write_char(show_temp0);
    LCD_write_char(show_temp1);
    LCD_write_char(show_temp2);
    LCD_write_char(show_temp3);
  }          

}
