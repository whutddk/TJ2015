/****������ƴ��� H �ļ�
***��Ҫ�ж����ʼ��
***���PD����
****�����
2014 11 26
*/

#ifndef _SERVO_H_
#define _SERVO_H_

#define SERVO_PWM_MAX 1000
#define SERVO_PWM_MIN 500
#define SERVO_PWM_MID 750

#define SERVO_PWM_REVISE (-10) //�����еƫ������PWM

void servo_init();//�����Ż�
void servo_set();//PD���ö��ת��
extern uint16 pwm_show;
extern float P_servo;
extern float I_servo;

#endif