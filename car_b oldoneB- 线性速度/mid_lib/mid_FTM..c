/***
***FTMģ���в��
�����
2014 11 22

***
*/

#include "common.h"
#include "include.h"



void PWM0_init()                 //FTM0ͨ���࣬8ͨ�����ڿ���PWM
{ 
  FTM_InitTypeDef ftm_init_struct;
  ftm_init_struct.FTM_Ftmx = FTM0;	//ʹ��FTM0ͨ��
  ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	//ʹ��PWMģʽ
  ftm_init_struct.FTM_PwmFreq = 1000;	//PWMƵ��10000Hz
  ftm_init_struct.FTM_PwmDeadtimeCfg = DEADTIME_CH23;
  ftm_init_struct.FTM_PwmDeadtimeVal=0;
  LPLD_FTM_Init(ftm_init_struct);
  
    LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch0, //ʹ��Ch0ͨ��
                      10, //��ʼ���Ƕ�0��
                      PTC1, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      );    
    LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch1, //ʹ��Ch0ͨ��
                      10, //��ʼ���Ƕ�0��
                      PTC2, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch2, //ʹ��Ch0ͨ��
                      10, //��ʼ���Ƕ�0��
                      PTC3, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch3, //ʹ��Ch0ͨ��
                      10, //��ʼ���Ƕ�0��
                      PTC4, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch4, //ʹ��Ch0ͨ��
                      10, //��ʼ���Ƕ�0��
                      PTD4, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch5, //ʹ��Ch0ͨ��
                      10, //��ʼ���Ƕ�0��
                      PTD5, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch6, //ʹ��Ch0ͨ��
                      10, //��ʼ���Ƕ�0��
                      PTD6, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch7, //ʹ��Ch0ͨ��
                      10, //��ʼ���Ƕ�0��
                      PTD7, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 
}/*��PWM���*/

/*
void ic_init(void)
{
  FTM_InitTypeDef ftm_init_struct;
  //����FTM1ģ������벶�����
  ftm_init_struct.FTM_Ftmx = FTM2;      //ʹ��FTM1ͨ��
  ftm_init_struct.FTM_Mode = FTM_MODE_IC;       //ʹ�����벶��ģʽ
  ftm_init_struct.FTM_ClkDiv = FTM_CLK_DIV128;  //������Ƶ��Ϊ����ʱ�ӵ�128��Ƶ
  ftm_init_struct.FTM_Isr = ic_isr;     //�����жϺ���
  //��ʼ��FTM1
  LPLD_FTM_Init(ftm_init_struct);
  //ʹ�����벶���Ӧͨ��,�����ز�������ж�
  LPLD_FTM_IC_Enable(FTM1, FTM_Ch0, PTB18, CAPTURE_RI);//�����ز���
  
  //ʹ��FTM0�ж�
  LPLD_FTM_EnableIrq(ftm_init_struct);
}
*/
void PWM1_init()                 //FTM1ͨ����2ͨ�����ڿ���PWM
{ 
  FTM_InitTypeDef ftm_init_struct;
  ftm_init_struct.FTM_Ftmx = FTM1;	//ʹ��FTM0ͨ��
  ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	//ʹ��PWMģʽ
  ftm_init_struct.FTM_PwmFreq = 50;	//PWMƵ��50hz
  ftm_init_struct.FTM_PwmDeadtimeCfg = DEADTIME_CH01;
  ftm_init_struct.FTM_PwmDeadtimeVal=0;
  LPLD_FTM_Init(ftm_init_struct);
  
  LPLD_FTM_PWM_Enable(FTM1, //ʹ��FTM0
                      FTM_Ch0, //ʹ��Ch0ͨ��
                      750, //ռ�ձ�
                      PTA8, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      );    
    LPLD_FTM_PWM_Enable(FTM1, //ʹ��FTM0
                      FTM_Ch1, //ʹ��Ch0ͨ��
                      750, //ռ�ձ�
                      PTA9, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 

}
/*
*��׽�������ж�
*/
/*
uint32 Freq;//Ƶ�ʲ���������û�ã��жϲ�������δ�������μ���
 void ic_isr(void)
  {
    uint32 cnt;
  //�ж��Ƿ�ΪFTM1��Ch0ͨ�����������ж�
  if(LPLD_FTM_IsCHnF(FTM1, FTM_Ch0))
  {
    //��ȡFTM1��Ch0ͨ������ֵ
    cnt=LPLD_FTM_GetChVal(FTM1, FTM_Ch0);   
    
    //��������Ƶ�ʡ���Ƶϵ��������ֵ��������Ƶ��
    //����Ƶ��=(����Ƶ��/���벶���Ƶ)/����ֵ
    Freq=(g_bus_clock/LPLD_FTM_GetClkDiv(FTM1))/cnt; 
    
    //���FTM1 COUNTER
    LPLD_FTM_ClearCounter(FTM1);
    //��������жϱ�־
    LPLD_FTM_ClearCHnF(FTM1, FTM_Ch0); 
  }
}
*/  