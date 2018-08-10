/****电机控制 H 文件
速度控制和测速
**********李锐戈
***********2014 11 30
*********
*/

#ifndef _MOTTO_H_
#define _MOTTO_H_


extern uint16 SPEED_MAX;
extern uint16 SPEED_MIN;

extern uint8 flag_stop;            //刹车标志位，置高则强行停车
extern int32 speed_pwm [2];        //前速度PWM 和后速度PWM
extern uint32 speed_aim ;//目标速度
extern uint32 speed_current;//瞬时速度
void motto_init();
void speed_set();//设置目标速度mm/s （m/s*1000），pid瞬时速度mm/s，比例后为PWM差值

#endif 