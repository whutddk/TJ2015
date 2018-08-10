/*  24L01 B车接收 C 文件
***
***
***2015 1 4 王佳龙
2015 1 12 李锐戈 屏蔽错误语句
*/


#include "common.h"
#include "include.h"

uint8 RX_buff[32];


/* Nrf24L01_RX_buff
* 用于获得接收数据
* 还未调用,需在接收初始化中调用
* 返回值: 
*     无      
*/

 
void Nrf24L01_RX_buff()
{
  //RX_buff[32];
}


/*Nrf24L01_RX_Cheek
*用于校检接收数据是否正确
*还未调用，需在接收函数后调用
*返回值 正确返回1，有误返回0
*/

uint8 Nrf24L01_RX_Check()
{
  if(RX_buff[0] == 0xaa && RX_buff[2] == 0xbb && RX_buff[4] == 0xcc
                       &&RX_buff[6] == 0xdd&&RX_buff[8] == 0xee)
    return 1;
  else
    return 0;
    
}
