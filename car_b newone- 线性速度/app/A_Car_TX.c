/*  24L01 fA������ C �ļ�
***
***
***2015 1 4 ������
2015 1 12 ����� ���δ������
*/

#include "common.h"
#include "include.h"


uint8 TX_buff[32];

/*
* Nrf24L01_TX_buff
* ���ڻ�÷�������
* ��δ����,���ڷ��ͳ�ʼ���е���
* ����ֵ: 
*     ��      
*/

 
void Nrf24L01_TX_buff()
{
  //TX_buff[16] ={ 0xaa, 0x00 ,0xbb ,0x00 ,0xcc ,0x00 ,0xdd } ;
  TX_buff[1] = 0;
  TX_buff[3] = 0;
  TX_buff[5] = 0;
}


/* Nrf24L01_RX_buff
* ���ڻ�ý�������
* ��δ����,���ڽ��ճ�ʼ���е���
* ����ֵ: 
*     ��      
*/

