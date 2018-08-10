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
void servo_set()//PD设置舵机转角
{
  int32 result = 0;
   
  int32 pwm_duty = SERVO_PWM_MID + SERVO_PWM_REVISE;
  
  //比例项
  if ( this_location >= 0  )
  {
    result = - ( this_location / 50 ) * ( this_location / 50 ); //* P_servo;
  }
  else
  {
    result = ( this_location / 60 ) * ( this_location / 60 );
  }
  /***************积分
  if ( this_location < 180 && this_location > -180 )
  {
    i_sum = 0; //积分清零死区
  }
  i_sum += (int16) ( this_location *0.);//*0.005 ));//积分和速度挂钩
  //i_sum *= I_servo;
  if ( i_sum >= 200 )//饱和设置
  {
    i_sum = 200;
  }
  if ( i_sum <= -200 )
  {
    i_sum = -200;
  }
  push(14,i_sum);
  result += i_sum;
  */
  result += angle * 0.0;//微分项
  
  
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



/**华科代码，分析中
* @ brief: 设置舵机转向角度
*
@ para: int16_t sensor_offset 当前偏差
* int16_t p_steer_angle 舵机转向角度
* @ return： none
*
@ note: PD 算法

void set_steer_angle(int16_t sensor_offset, int16_t *p_steer_angle)
{
float P_value = 10.5;           //P系数
float D_value = 35;             //D系数
int16_t angle = 0;              //角度
int16_t offset_delta = 0;       //偏置三角？
int16_t angle_P_value = 0, angle_D_value = 0;
int8_t right_angle_flag = 0;    //正确的角度？
int16_t speed_now = 0;          //当前速度
static int16_t right_angle_time_count = -1;
static int8_t right_angle_flag_last = 0;
offset_delta = get_offset_delta(sensor_offset);
//get_pd(sensor_offset, offset_delta, &P_value, &D_value);
fuzzy_PD(sensor_offset, offset_delta, &P_value, &D_value);
right_angle_flag = get_right_angle_flag();
speed_now = get_car_speed();
if(right_angle_flag != 0 && right_angle_flag_last == 0)
{
if(speed_now > 390)
right_angle_time_count = 110;
else if(speed_now > 370)
right_angle_time_count = 102;
else if(speed_now > 350)
right_angle_time_count = 94;
else if(speed_now > 330)
right_angle_time_count = 86;
else if(speed_now > 310)
right_angle_time_count = 78;
else if(speed_now > 310)
right_angle_time_count = 70;
else
right_angle_time_count = 61;
}
if(right_angle_time_count >= 0)
{
right_angle_time_count--;
P_value = 13.5;
}
angle_P_value = (int16_t)(P_value * sensor_offset);
angle_D_value = (int16_t)(D_value * offset_delta);
if(sensor_offset >= 0)
{
if(angle_D_value > 550)
angle_D_value = 550;
else if(angle_D_value < -600)
angle_D_value = -600;
}
else
{
if(angle_D_value < -550)
angle_D_value = -550;
else if(angle_D_value > 600)
angle_D_value = 600;
}
angle = angle_P_value + angle_D_value;
set_final_angle(&angle);
*p_steer_angle = angle;
set_steer_pwm(angle);
gl_output[9] = angle;
gl_output[57] = offset_delta;
gl_output[22] = angle_P_value;
gl_output[23] = angle_D_value;
gl_output[55] = (int16_t) (P_value * 100);
gl_output[56] = (int16_t) (D_value * 100);
right_angle_flag_last = right_angle_flag;
}*/