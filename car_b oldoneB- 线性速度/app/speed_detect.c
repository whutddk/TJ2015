/***********速度控制和检测C文件
**************
*************2014 12 14 李锐戈
2014 12 30 李锐戈
*/

#include "common.h"
#include "include.h"


//uint16 pluse_h_sta = 0;//起始高位
uint32 pluse_l_sta = 0;//起始低位
uint32 solfwave_sta = 0;//起始的程序计数(时间)
uint16 speed_ave =0;//平均速度
uint8 flag_speed = 0;//排除起始一次


void speed_count()//全自动平均速度测试函数，只需要在启动电机后开启
{
  if (flag_speed)
  {
    speed_ave = ( (pluse_count_l - pluse_l_sta) )//脉冲数
                / ( solfware_count - solfwave_sta )//单位时间脉冲数(MS)
                  /200//单位时间圈数
                  * WHELL_C;//mm每ms  m/s
  }
   else
    
  {
    pluse_l_sta = pluse_count_l; 
    solfwave_sta = solfware_count;
    flag_speed =1;
  }
}


/******瞬时速度 SPEED_AVE_TIME对应世间段***************/
/******在motto_set（）中自动调用***************/

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

