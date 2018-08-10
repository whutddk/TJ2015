/******电机控制 C 文件
速度控制和测速
***********李锐戈
***********2014 11 30
最后修改 2015 2 11 李锐戈 发动机重新映射
*************
*/

#include "common.h"
#include "include.h"

/***
***使用PWM2 PWM4
   C2      C4
   CH1     CH3
***
***
*/
//调试阶段，最大PWMduty被限制为300
void motto_init()
{
  PWM0_init();//电机PWM初始化
}

int32 speed_pwm [2]={0,0};
uint8 flag_stop = 0;            //刹车标志位，置高则强行停车
uint32 speed_aim = 0;//目标速度
uint32 speed_current = 0;//瞬时速度

void speed_set()//设置目标速度m/ms （m/s），pid瞬时速度mm/s，比例后为PWM差值
{
  speed_pwm [1] = (UpdatePID_Out_2(speed_aim,speed_current) + speed_pwm[0] ); //前速度加PID后增量
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






