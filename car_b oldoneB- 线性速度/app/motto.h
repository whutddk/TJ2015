/****������� H �ļ�
�ٶȿ��ƺͲ���
**********�����
***********2014 11 30
*********
*/

#ifndef _MOTTO_H_
#define _MOTTO_H_


extern uint16 SPEED_MAX;
extern uint16 SPEED_MIN;

extern uint8 flag_stop;            //ɲ����־λ���ø���ǿ��ͣ��
extern int32 speed_pwm [2];        //ǰ�ٶ�PWM �ͺ��ٶ�PWM
extern uint32 speed_aim ;//Ŀ���ٶ�
extern uint32 speed_current;//˲ʱ�ٶ�
void motto_init();
void speed_set();//����Ŀ���ٶ�mm/s ��m/s*1000����pid˲ʱ�ٶ�mm/s��������ΪPWM��ֵ

#endif 