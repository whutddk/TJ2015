/*  24L01 A������ H �ļ�
***
***
***2015 1 4 ������
2015 1 12 ����� ��������
*/

#ifndef _A_CAR_TX_H_
#define _A_CAR_TX_H_

/********************************************************************/

extern uint8 TX_buff[32];


void Nrf24L01_TX_buff();
void Nrf24L01_RX_buff();
uint8 Nrf24L01_RX_Check();

#endif