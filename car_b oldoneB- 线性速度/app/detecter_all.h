/*����Ѱ�ߴ����ͷ�ļ�
*��Ҫ�����1�ų�8���ģ��
**
***2014 11 26 �����
2015 1 24 �����
****
*/

#ifndef _DETECTER_ALL_H_
#define _DETECTER_ALL_H_


 
extern int32 location[5];//�з���
extern int32 this_location;

extern uint16 max_AD[8];//��һ����100��
extern uint16 min_AD[8];
extern int16 angle;


#define DET_NUM 5

#define LINE_ABOVE_UP  600    //����������Ϸ��Ҵ�ֱ DATA > Ta
#define LINE_ABOVE_DOWN  500    //DATA < Ta

#define LINE_MISS_UP   100    //��ж��� DATA > Ta
#define LINE_MISS_DOWN 85       //DATA < Ta


#define LINE_MID1_UP    110   //������������ DATA > Ta
#define LINE_MID2_UP    400


extern uint16 SPEED_MAX;
extern uint16 SPEED_MIN;


#define DEFFER1  300
#define DEFFER2  100
#define INDUCTOR1 AD[3]
#define INDUCTOR2 AD[2]
#define INDUCTOR3 AD[1]
#define INDUCTOR4 AD[0]
#define INDUCTOR5 AD[7]
#define INDUCTOR6 AD[6]
#define INDUCTOR7 AD[4]
#define INDUCTOR8 AD[0]


extern uint16 AD_data[8][DET_NUM];//ÿ��ͨ��ȡN��ֵ�Ĵ��λ��
extern uint16 AD_average[8];//�ĸ��������˲����ֵ
extern uint16 max_AD[8]; //���������ֵ����
extern uint16 min_AD[8];//�����Сֵ
extern int8 flag_cross;
extern int8 flag_curve;
extern int16 Front_INDUCTOR;
void mode_detecter();
void Get_AD_data();
void ScanNorma(uint16 times);
void detecter();
void common_situation();




#endif