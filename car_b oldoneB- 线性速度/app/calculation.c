/**赛道偏差计算
*
*前后电感偏差计算
*李锐戈
2015 3 19
*/

include "common.h"
include "include.h"

uint16 location[4] = {0,0,0,0};
uint16 angle = 0;

void calculate1()//双排同步算法
{
	if ( front_miss == 0 )//前排没有丢线
	{
		location[4] = front_location[4] * 0.4 +back_location[4] *0.6; //位置偏差使用前后电感的权重，控制中对应P
		angle = front_location[4] - back_location[4];//曲线延伸趋势，控制中对应D

		    this_location = (int32)(location [0] * 0.05//【0】已经平滑化处理值及权重
               + location [1] * 0.05 //【1】已经平滑化处理值及权重
                 + location [2] * 0.05 //【1】已经平滑化处理值及权重
                   + location [3] * 0.15 //【1】已经平滑化处理值及权重
                    + location [4] * 0.70);//【2】当前AD差值，加入参与平滑化
 
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
	else if ( back_miss ==0 ) //后排没丢线，但前排已经丢线
	{
		location[4] = back_location[4] ; //位置偏差使用后电感，控制中对应P
		angle = 0;//曲线延伸趋势，控制中对应D
	}
	else //全丢线
	{
		speed_aim = 0;
	}
}


