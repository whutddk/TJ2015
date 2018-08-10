/******������� C �ļ�
�ٶȿ��ƺͲ���
***********�����
***********2014 11 30
����޸� 2015 2 11 ����� ����������ӳ��
*************
*/

#include "common.h"
#include "include.h"

/***
***ʹ��PWM2 PWM4
   C2      C4
   CH1     CH3
***
***
*/
//���Խ׶Σ����PWMduty������Ϊ300
void motto_init()
{
  PWM0_init();//���PWM��ʼ��
}

int32 speed_pwm [2]={0,0};
uint8 flag_stop = 0;            //ɲ����־λ���ø���ǿ��ͣ��
uint32 speed_aim = 0;//Ŀ���ٶ�
uint32 speed_current = 0;//˲ʱ�ٶ�

void speed_set()//����Ŀ���ٶ�m/ms ��m/s����pid˲ʱ�ٶ�mm/s��������ΪPWM��ֵ
{
  speed_pwm [1] = (UpdatePID_Out_2(speed_aim,speed_current) + speed_pwm[0] ); //ǰ�ٶȼ�PID������
  if(speed_pwm[1] >=5000)
  {
    speed_pwm[1] = 5000;
  }
  if(speed_pwm[1] <=10)
  {
    speed_pwm[1] = 10;
  }
  speed_pwm[0] = speed_pwm[1];
  
  LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, (uint32)(speed_pwm[0]));
  
 
}






