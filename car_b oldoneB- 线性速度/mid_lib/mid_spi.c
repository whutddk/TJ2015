/***
***spi���ÿ���Ҫfor24l01��SD��
�����
2014 11 22
***
*/

/********************************************
 * ˵��: 
 * Ӳ������˵��:
 * K60��Ƭ������        NRF24L01����
 * 
 *     INT    -PTE6  -----> IRQ
 *     CE     -PTE5  -----> CE
 *     CS     -PTE4 -----> CSN
 *     SCK    -PTE2 -----> SCK
 *     MOSI   -PTE1 -----> MOSI
 *     MISO   -PTE3 <----- MISO
 *

 * ͨ���޸�NRF24L01_WORKMODE�ı䷢�ͺͽ��շ�ʽ
 ********************************************/
#include "common.h"
#include "include.h"
   
/* 
//ѡ����뷽ʽ ������ǰ������NRF24L01�Ĺ�����ʽ
#define NRF24L01_RX_WORKMODE      (0) //���ͳ���
#define NRF24L01_TX_WORKMODE      (1) //���ճ���
#define NRF24L01_WORKMODE         NRF24L01_TX_WORKMODE 

uint8 rx_buf[NRF24L01_PLOAD_LEN] = {0x00};     //���ջ�����
uint8 tx_buf[NRF24L01_PLOAD_LEN] = {0x00};     //���ͻ�����





void nrf24l01_RX_init()
{
  GPIO_InitTypeDef gpio_init_struct;
   //�жϺ�������
  gpio_init_struct.GPIO_PTx = PTE;        //PORTE
  gpio_init_struct.GPIO_Pins = GPIO_Pin6; //����6
  gpio_init_struct.GPIO_Dir = DIR_INPUT;  //����
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_DOWN|IRQC_FA;  //�ڲ�����|�½����ж�
  gpio_init_struct.GPIO_Isr = porte_handle;      //�жϺ���
    
  LPLD_GPIO_Init(gpio_init_struct);
  LPLD_GPIO_EnableIrq(gpio_init_struct); //�ڲ�����,ʹ��PORTE6��ΪNRF24L01��IRQ�ж�
  LPLD_Nrf24L01_RxModeInit();
}   
uint8 Flag_Smitte = 0; //���ͱ�־��

void nrf24l01_checksend()
{ int i; 
    if(Flag_Smitte)
    {
      for(i = 0 ;i <32 ;i++)//���÷��͵�32���ֽ�����
      {
        tx_buf[i] = i;
      }
      if(LPLD_Nrf24L01_SendFrame(tx_buf,NRF24L01_PLOAD_LEN))
      {
        
      }
      else
      {
       
      }
      Flag_Smitte = 0;
    }
   
}

//nrf24l01�����ж�
void porte_handle()
{   
  LPLD_Nrf24L01_RecvFrame(rx_buf, NRF24L01_PLOAD_LEN);
}
*/
/********************************************************************/
