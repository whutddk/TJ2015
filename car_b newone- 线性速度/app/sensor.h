/*
**��������Ӳ������ͷ�ļ���
***��ҪΪAD�ɼ�
****ͬʱ�����˶������е�ͷ�ļ�
�����
2014 11 25
2015 1 10 �����
*/
#ifndef _SENSOR_H_
#define _SENSOR_H_

#define QUEMAX 10             /*���г���*/
#define QUEUE_INIT 1000       /*��ʼ�����е�ֵ������Ϊֱ����Ӧ����ֵ��*/


extern int16 AD[8];    //������ת�������һ��,Ϊ���⸡�����㣬*100





typedef struct queue//�ö���Ϊ����
{
  uint16 data[QUEMAX];
  uint8 front;
  uint8 rear;
}que;

void point_move(que *q);//��ͷ��β�ƶ�
void queue_int( que *q );//�Խ�����һ�����н��г�ʼ��
uint16 update_que( que *q , uint16 data_in );//��Ӻͳ���һ��

void sensors_init();
void Get_AD_data(); //��ȡ���ֵ����һ����100��


#endif