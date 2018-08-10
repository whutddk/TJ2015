/*
*PIT�����в��
�����
2014 11 22
*
*/
#include "common.h"
#include "include.h"

void pit0us_init()//100us���� ���������
{
  PIT_InitTypeDef pit_init_struct;
  //����PIT0����
  pit_init_struct.PIT_Pitx = PIT0;
   pit_init_struct.PIT_PeriodS = 0;
   pit_init_struct.PIT_PeriodMs = 0;
  pit_init_struct.PIT_PeriodUs = 100;     //��ʱ����
  pit_init_struct.PIT_Isr = pit0us_isr;  //�����жϺ���
  //��ʼ��PIT0
  LPLD_PIT_Init(pit_init_struct); 
  
 LPLD_PIT_EnableIrq(pit_init_struct);
}

void pit1ms_init()      //5ms���ڵ�вɼ�����������ʱ
{
  PIT_InitTypeDef pit_init_struct;
  //����PIT0����
  pit_init_struct.PIT_Pitx = PIT1;
  pit_init_struct.PIT_PeriodS = 0;
  pit_init_struct.PIT_PeriodMs = 5;     //��ʱ����5ms
  pit_init_struct.PIT_PeriodUs = 0;
  pit_init_struct.PIT_Isr = pit1ms_isr;  //�����жϺ���
  //��ʼ��PIT0
  LPLD_PIT_Init(pit_init_struct); 
  
  LPLD_PIT_EnableIrq(pit_init_struct);
}

void pit2ms_init()       //����ʱ���ʱ1ms
{
  PIT_InitTypeDef pit_init_struct;
  //����PIT0����
  pit_init_struct.PIT_Pitx = PIT2;
  pit_init_struct.PIT_PeriodS = 0;
  pit_init_struct.PIT_PeriodMs = 1;     //��ʱ����
  pit_init_struct.PIT_PeriodUs = 0;
  pit_init_struct.PIT_Isr = pit2ms_isr;  //�����жϺ���
  //��ʼ��PIT2
  LPLD_PIT_Init(pit_init_struct); 
  
  LPLD_PIT_EnableIrq(pit_init_struct);
}

void pit3us_init(uint32 Periodus)
{
  PIT_InitTypeDef pit_init_struct;
  //����PIT3����
  pit_init_struct.PIT_Pitx = PIT3;
  pit_init_struct.PIT_PeriodS = 0;
  pit_init_struct.PIT_PeriodMs = 0;
  pit_init_struct.PIT_PeriodUs = Periodus;     //��ʱ����
  pit_init_struct.PIT_Isr = pit3us_isr;  //�����жϺ���
  //��ʼ��PIT0
  LPLD_PIT_Init(pit_init_struct);

LPLD_PIT_EnableIrq(pit_init_struct);  
}

uint8 sonar_count = 0 ;
void pit0us_isr()//����������жϺ���
{
  sonar_count ++ ;
 
}


/********************************************/
uint8 flag_5ms = 0;
uint8 flag_10ms = 0;
uint8 flag_30ms = 0;
uint8 flag_60ms = 0;
uint8 flag_70ms = 0;
uint8 flag_80ms = 0;
uint8 flag_90ms = 0;
uint8 flag_100ms = 0;
uint8 flag_250ms = 0;
uint8 flag_500ms = 0;
uint8 flag_1s = 0;
uint8 count = 0;

void pit1ms_isr()//��������ʱ�жϺ�������ż�⺯���ж�
{
  count ++;
  flag_5ms = 1;
  if (count % 2 == 0 )//����5ms��10ms
  {
    flag_10ms = 1;
  }
  if ( count % 6 == 0 )
  {
    flag_30ms = 1;
  }
  if ( count % 12 == 0 )
  {
    flag_60ms = 1;
  }
  if ( count % 14 == 0 )
  {
    flag_70ms = 1;
  }
  if ( count % 16 == 0 )
  {
    flag_80ms = 1;
  }
  if ( count % 18 == 0 )
  {
    flag_90ms = 1; 
  }
  if ( count % 20 == 0)
  {
    flag_100ms = 1;
    
  }
    if ( count % 50 == 0)
  {
    flag_250ms = 1;
  }
  if ( count % 100 == 0)
  {
    flag_500ms = 1;
  }
  if ( count % 200 == 0)
  {
    flag_1s = 1;
    count = 0;
  }
  Get_AD_data(); //��ȡ���ֵ����һ����100��
}

uint32 solfware_count = 0;//����ܼ�ʱ
void pit2ms_isr()
{
  solfware_count++;
}

void pit3us_isr()
{
  PIT_InitTypeDef pit_init_struct;//�ͷ�PIT3����
 
  flag_delay_complete = 1;
  
  pit_init_struct.PIT_Pitx = PIT3;
  LPLD_PIT_Deinit(pit_init_struct);
}

uint8 flag_delay_complete = 0;
void delay(uint32 time_us)
{
  flag_delay_complete = 0;
  pit3us_init(time_us);
  while(!flag_delay_complete);
  
}

void disable_all_isr()//�ر������ж�
{
  PIT_InitTypeDef pit_init_struct;
  pit_init_struct.PIT_Pitx = PIT1;
  LPLD_PIT_DisableIrq(pit_init_struct);
  pit_init_struct.PIT_Pitx = PIT2;
  LPLD_PIT_DisableIrq(pit_init_struct);
}

void enbale_all_isr()//�����ж�
{
  PIT_InitTypeDef pit_init_struct;
  pit_init_struct.PIT_Pitx = PIT1;
  LPLD_PIT_EnableIrq(pit_init_struct);
  pit_init_struct.PIT_Pitx = PIT2;
  LPLD_PIT_EnableIrq(pit_init_struct);
}