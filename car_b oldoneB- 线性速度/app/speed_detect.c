/***********�ٶȿ��ƺͼ��C�ļ�
**************
*************2014 12 14 �����
2014 12 30 �����
*/

#include "common.h"
#include "include.h"


//uint16 pluse_h_sta = 0;//��ʼ��λ
uint32 pluse_l_sta = 0;//��ʼ��λ
uint32 solfwave_sta = 0;//��ʼ�ĳ������(ʱ��)
uint16 speed_ave =0;//ƽ���ٶ�
uint8 flag_speed = 0;//�ų���ʼһ��


void speed_count()//ȫ�Զ�ƽ���ٶȲ��Ժ�����ֻ��Ҫ�������������
{
  if (flag_speed)
  {
    speed_ave = ( (pluse_count_l - pluse_l_sta) )//������
                / ( solfware_count - solfwave_sta )//��λʱ��������(MS)
                  /200//��λʱ��Ȧ��
                  * WHELL_C;//mmÿms  m/s
  }
   else
    
  {
    pluse_l_sta = pluse_count_l; 
    solfwave_sta = solfware_count;
    flag_speed =1;
  }
}


/******˲ʱ�ٶ� SPEED_AVE_TIME��Ӧ�����***************/
/******��motto_set�������Զ�����***************/

uint32 pluse_get[2] = {0,0};

void speed_getcurrent()
{
  uint32 temp;
  pluse_get[1] = pluse_count_l ;
  temp = pluse_get[1] - pluse_get[0]; 
  pluse_get[0] = pluse_get[1];
  speed_current = (uint32) ((temp / 200. *40 / 106. *1000* WHELL_C/ SPEED_AVE_TIME   ));//m/s*1000 = mm/s
  //push(5,speed_current);
}

