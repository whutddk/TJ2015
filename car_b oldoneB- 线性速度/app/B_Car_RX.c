/*  24L01 B������ C �ļ�
***
***
***2015 1 4 ������
2015 1 12 ����� ���δ������
*/


#include "common.h"
#include "include.h"

uint8 RX_buff[32];


/* Nrf24L01_RX_buff
* ���ڻ�ý�������
* ��δ����,���ڽ��ճ�ʼ���е���
* ����ֵ: 
*     ��      
*/

 
void Nrf24L01_RX_buff()
{
  //RX_buff[32];
}


/*Nrf24L01_RX_Cheek
*����У����������Ƿ���ȷ
*��δ���ã����ڽ��պ��������
*����ֵ ��ȷ����1�����󷵻�0
*/

uint8 Nrf24L01_RX_Check()
{
  if(RX_buff[0] == 0xaa && RX_buff[2] == 0xbb && RX_buff[4] == 0xcc
                       &&RX_buff[6] == 0xdd&&RX_buff[8] == 0xee)
    return 1;
  else
    return 0;
    
}
