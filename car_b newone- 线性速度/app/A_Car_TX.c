/*  24L01 fA车发送 C 文件
***
***
***2015 1 4 王佳龙
2015 1 12 李锐戈 屏蔽错误语句
*/

#include "common.h"
#include "include.h"


uint8 TX_buff[32];

/*
* Nrf24L01_TX_buff
* 用于获得发送数据
* 还未调用,需在发送初始化中调用
* 返回值: 
*     无      
*/

 
void Nrf24L01_TX_buff()
{
  //TX_buff[16] ={ 0xaa, 0x00 ,0xbb ,0x00 ,0xcc ,0x00 ,0xdd } ;
  TX_buff[1] = 0;
  TX_buff[3] = 0;
  TX_buff[5] = 0;
}


/* Nrf24L01_RX_buff
* 用于获得接收数据
* 还未调用,需在接收初始化中调用
* 返回值: 
*     无      
*/

