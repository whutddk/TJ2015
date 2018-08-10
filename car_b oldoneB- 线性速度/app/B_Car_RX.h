/*  24L01 B车接收 H 文件
***
***
***2015 1 4 王佳龙
2015 1 12 李锐戈 增加声明
*/

#ifndef _B_CAR_RX_H_
#define _B_CAR_RX_H_


/********************************************************************/

extern uint8 RX_buff[32];

void Nrf24L01_TX_buff();
void Nrf24L01_RX_buff();
uint8 Nrf24L01_RX_Check();

#endif