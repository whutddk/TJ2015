/**����ƫ�����
*
*ǰ����ƫ�����
*�����
2015 3 19
*/

include "common.h"
include "include.h"

uint16 location[4] = {0,0,0,0};
uint16 angle = 0;

void calculate1()//˫��ͬ���㷨
{
	if ( front_miss == 0 )//ǰ��û�ж���
	{
		location[4] = front_location[4] * 0.4 +back_location[4] *0.6; //λ��ƫ��ʹ��ǰ���е�Ȩ�أ������ж�ӦP
		angle = front_location[4] - back_location[4];//�����������ƣ������ж�ӦD

		    this_location = (int32)(location [0] * 0.05//��0���Ѿ�ƽ��������ֵ��Ȩ��
               + location [1] * 0.05 //��1���Ѿ�ƽ��������ֵ��Ȩ��
                 + location [2] * 0.05 //��1���Ѿ�ƽ��������ֵ��Ȩ��
                   + location [3] * 0.15 //��1���Ѿ�ƽ��������ֵ��Ȩ��
                    + location [4] * 0.70);//��2����ǰAD��ֵ���������ƽ����
 
  /*****************************************/
	if ( this_location >= 1000 )
	{ this_location = 1000; }
	if ( this_location <= -1000 )
	{ this_location = -1000; }
 /******************************************/
	location [0] = location[1];
	location [1] = location[2];
	location [2] = location [3];
	location [3] = this_location;
	}
	else if ( back_miss ==0 ) //����û���ߣ���ǰ���Ѿ�����
	{
		location[4] = back_location[4] ; //λ��ƫ��ʹ�ú��У������ж�ӦP
		angle = 0;//�����������ƣ������ж�ӦD
	}
	else //ȫ����
	{
		speed_aim = 0;
	}
}


