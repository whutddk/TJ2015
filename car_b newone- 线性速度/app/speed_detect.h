/***********�ٶȿ��ƺͼ��H�ļ�
**************
*************2014 12 14 �����
2015 2 14 ����� ����ֻ��32λ��λ
*/

#ifndef __SPEED_DETECT_H__
#define __SOEED_DETECT_H__

//����ֱ��//55mm
//�����ܳ�PI*D = 3.14159*55MM=172.78745
//�����ܳ�PI*D = 3.14159*56MM=175.92904

#define WHELL_C 174
#define SPEED_AVE_TIME 60


//extern uint16 pluse_h_sta;//��ʼ��λ
//extern uint32 pluse_l_sta ;//��ʼ��λ
//extern uint32 solfwave_sta;//��ʼ�ĳ��������ʱ�䣩
//extern uint16 speed_ave;//ƽ���ٶ�
//extern uint8 flag_speed;//�ų���ʼһ��


void speed_count();//ȫ�Զ��ٶȲ���

 
void speed_getcurrent();//˲ʱ�ٶ�





#endif 