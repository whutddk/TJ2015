/**
* --------------����"��������K60�ײ��V3"�Ĺ��̣�car_b��-----------------
* @file car_b.c
* @version 0.0
* @date 2013-9-29
* @brief ���ڸù��̵�����
*
* ��Ȩ����:�����������µ��Ӽ������޹�˾
* http://www.lpld.cn
* mail:support@lpld.cn
* Ӳ��ƽ̨:  LPLD K60 Card / LPLD K60 Nano
*
* �����̻���"��������K60�ײ��V3"������
* ���п�Դ�������"lib"�ļ����£��û����ظ��ĸ�Ŀ¼�´��룬
* �����û������豣����"project"�ļ����£��Թ����������ļ�������
* �ײ��ʹ�÷���������ĵ��� 
*
*����� 2015 1 24
*
*
*/
#include "include.h"
#include "common.h"



void main (void)
{
  interaction_init();   //�˻�������ʼ��
  LCD_init();      
  servo_init();         //������Ƴ�ʼ��
  lpt_init();           //���������ʼ��
  uart0_isr_init();     //0��������ʼ��
  sensors_init();       //��8�����ADC��ʹ��
  motto_init();         //������Ƴ�ʼ��
  pit0us_init();       //���������
  pit1ms_init();        //��������ʱ
  signal_init();        //�źų�ʼ��
  gpio_key_init();      //���ܰ���ѡ���ʼ��
  
  //���Խ׶Σ�����ɨ�棬����֮ǰ�ɼ�������
  //ScanNorma(2000);     //ɨ��궨
  flag_a_car = 1;
  key_select();          //���ܰ���ѡ��
  light_all();
  delay(4000000);
  out_all();
  while(1)
  {   
    if (!flag_stop)
    {
      while(flag_a_car)
      {
        a_car_main();
      }
      
    }
    else
    {
      LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10);
      LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1,SERVO_PWM_MID + SERVO_PWM_REVISE);
    }
  }  
}






//beep_long();
