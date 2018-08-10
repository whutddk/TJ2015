/*  24L01 A车发送 H 文件
***
***
***2015 1 4 王佳龙
2015 1 12 李锐戈 增加声明
*/

#ifndef _A_CAR_TX_H_
#define _A_CAR_TX_H_

/********************************************************************/

extern uint8 TX_buff[32];


void Nrf24L01_TX_buff();
void Nrf24L01_RX_buff();
uint8 Nrf24L01_RX_Check();

#endif