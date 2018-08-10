/****������ƴ��� C �ļ�
***��Ҫ�ж����ʼ��
***���PD����
****�����
2014 11 26
2015 2 11 ����� ����ӿ�����ӳ��
*/
#include "common.h"
#include "include.h"

void servo_init()//�����Ż�
{
  PWM1_init();
}

int16 i_sum = 0;
uint16 pwm_show;//����pwmֵ��Һ��
float P_servo = 50;
float I_servo = 0.2;
float D_servo = 0.0;
int32 error[2] = {0,0};
void servo_set()//PD���ö��ת��
{
  int32 result = 0;
  
  int32 pwm_duty = SERVO_PWM_MID + SERVO_PWM_REVISE;
  
  error[1] = this_location;
  
  //������
  if ( this_location >= 0  )
  {
    result = - ( this_location / 48 ) * ( this_location / 48 ); //* P_servo;
  }
  else
  {
    result = ( this_location / 60 ) * ( this_location / 60 );
  }
  
  result += D_servo * ( error[1] - error[0] ) / 0.03;//΢����
  
  
  pwm_duty += result;
  push(12,result);
  
  /******************���Ʒ�ֵ***************/
  
  if ( pwm_duty < SERVO_PWM_MIN + SERVO_PWM_REVISE )
  {
    pwm_duty = SERVO_PWM_MIN + SERVO_PWM_REVISE;
  }
  if ( pwm_duty > SERVO_PWM_MAX + SERVO_PWM_REVISE )
  {
    pwm_duty = SERVO_PWM_MAX + SERVO_PWM_REVISE;
  }
  pwm_show = pwm_duty;
  
  /****************���ö��***************************/
  
  LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1, (uint32)pwm_duty);
  
  /****************����PWM***************************/
  
}

//��������ʽ���ƶ��
int32 PID_error[3]={0,0,0};
float AP_2 = 0.;
float AI_2 = 0.;
float AD_2 = 0.;
float AT_2 = 0.03;
int32 Aresult = SERVO_PWM_MID + SERVO_PWM_REVISE;

void servo_PID2()
{
  float out = 0;
  
  PID_error[2] = this_location;
  
  out  = AP_2 * ( PID_error[2] - PID_error[1]);
  out += AI_2 * ( PID_error[2] * AT_2 );
  out += AD_2 * ( PID_error[2] - 2 * PID_error[1] + PID_error[0]) / AT_2;
  
  PID_error[0] = PID_error[1];
  PID_error[1] = PID_error[2];
  
  Aresult += (int32)out;
  
  /******************���Ʒ�ֵ***************/
  
  if ( Aresult < SERVO_PWM_MIN + SERVO_PWM_REVISE )
  {
    Aresult = SERVO_PWM_MIN + SERVO_PWM_REVISE;
  }
  if ( Aresult > SERVO_PWM_MAX + SERVO_PWM_REVISE )
  {
    Aresult = SERVO_PWM_MAX + SERVO_PWM_REVISE;
  }
  
  /****************���ö��***************************/
  
  LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1, (uint32)Aresult);
  
}