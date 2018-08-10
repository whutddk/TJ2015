/****舵机控制代码 C 文件
***主要有舵机初始化
***舵机PD控制
****李锐戈
2014 11 26
2015 2 11 李锐戈 舵机接口重新映射
*/
#include "common.h"
#include "include.h"

void servo_init()//可以优化
{
  PWM1_init();
}

int16 i_sum = 0;
uint16 pwm_show;//传递pwm值给液晶
float P_servo = 50;
float I_servo = 0.2;
float D_servo = 0.0;
int32 error[2] = {0,0};
void servo_set()//PD设置舵机转角
{
  int32 result = 0;
  
  int32 pwm_duty = SERVO_PWM_MID + SERVO_PWM_REVISE;
  
  error[1] = this_location;
  
  //比例项
  if ( this_location >= 0  )
  {
    result = - ( this_location / 48 ) * ( this_location / 48 ); //* P_servo;
  }
  else
  {
    result = ( this_location / 60 ) * ( this_location / 60 );
  }
  
  result += D_servo * ( error[1] - error[0] ) / 0.03;//微分项
  
  
  pwm_duty += result;
  push(12,result);
  
  /******************限制幅值***************/
  
  if ( pwm_duty < SERVO_PWM_MIN + SERVO_PWM_REVISE )
  {
    pwm_duty = SERVO_PWM_MIN + SERVO_PWM_REVISE;
  }
  if ( pwm_duty > SERVO_PWM_MAX + SERVO_PWM_REVISE )
  {
    pwm_duty = SERVO_PWM_MAX + SERVO_PWM_REVISE;
  }
  pwm_show = pwm_duty;
  
  /****************设置舵机***************************/
  
  LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1, (uint32)pwm_duty);
  
  /****************发送PWM***************************/
  
}

//改用增量式控制舵机
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
  
  /******************限制幅值***************/
  
  if ( Aresult < SERVO_PWM_MIN + SERVO_PWM_REVISE )
  {
    Aresult = SERVO_PWM_MIN + SERVO_PWM_REVISE;
  }
  if ( Aresult > SERVO_PWM_MAX + SERVO_PWM_REVISE )
  {
    Aresult = SERVO_PWM_MAX + SERVO_PWM_REVISE;
  }
  
  /****************设置舵机***************************/
  
  LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1, (uint32)Aresult);
  
}