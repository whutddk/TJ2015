/*  24L01 B������ H �ļ�
***
***
***2015 1 4 ������
2015 1 12 ����� ��������
*/

#ifndef _B_CAR_RX_H_
#define _B_CAR_RX_H_


/********************************************************************/

extern uint8 RX_buff[32];

void Nrf24L01_TX_buff();
void Nrf24L01_RX_buff();
uint8 Nrf24L01_RX_Check();

#endif