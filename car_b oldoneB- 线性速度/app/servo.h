/****舵机控制代码 H 文件
***主要有舵机初始化
***舵机PD控制
****李锐戈
2014 11 26
*/

#ifndef _SERVO_H_
#define _SERVO_H_

#define SERVO_PWM_MAX 1000
#define SERVO_PWM_MIN 500
#define SERVO_PWM_MID 750

#define SERVO_PWM_REVISE (-10) //舵机机械偏差修正PWM

void servo_init();//可以优化
void servo_set();//PD设置舵机转角
extern uint16 pwm_show;
extern float P_servo;
extern float I_servo;

#endif