/*******
*******UART�в�⣬�����������¿⣬ʹ�����ʹ��
******
******/
#include "common.h"
#include "include.h"

/*
    ������
      �������ţ�ÿ��UARTx��Ӧ��ͬ��TxPin
    ȡֵ��
      UART0-PTA2��PTA14��*PTB17
      UART1-PTE0��*PTC4
      UART2-*PTD3
      UART3-PTE4��PTB11��*PTC17
      UART4-PTE24��*PTC15
      UART5-PTD9��*PTE8
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */

/*
    ������
      �������ţ�ÿ��UARTx��Ӧ��ͬ��RxPin
    ȡֵ��
      UART0-PTA1��PTA15��*PTB16
      UART1-PTE1��*PTC3
      UART2-*PTD2
      UART3-PTE5��PTB10��*PTC16
      UART4-PTE25��*PTC14
      UART5-PTD8��*PTE9
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */

void uart0_init()
{
  UART_InitTypeDef uart_init_struct;/*���ں�*/
  uart_init_struct.UART_Uartx = UART0; //ʹ��UARTx
  uart_init_struct.UART_BaudRate = 9600; /*���ò�����(9600)*/
  uart_init_struct.UART_RxPin = PTA15;  //��������ΪPTE9
  uart_init_struct.UART_TxPin = PTA14;  //��������ΪPTE8
  uart_init_struct.UART_RxIntEnable = FALSE;
  //uart_init_struct.UART_RxPin=PTD6;
  //uart_init_struct.UART_TxPin=PTD7;
  //��ʼ��UART
  LPLD_UART_Init(uart_init_struct);
}

void uart0_isr_init()
{
  UART_InitTypeDef uart_init_struct;/*���ں�*/
  uart_init_struct.UART_Uartx = UART0; //ʹ��UARTx
  uart_init_struct.UART_BaudRate = 9600; /*���ò�����(9600)*/
  uart_init_struct.UART_RxPin = PTA15;  //��������ΪPTE9
  uart_init_struct.UART_TxPin = PTA14;  //��������ΪPTE8
  uart_init_struct.UART_RxIntEnable = TRUE;
  uart_init_struct.UART_RxIsr = uart0_isr;
  //uart_init_struct.UART_RxPin=PTD6;
  //uart_init_struct.UART_TxPin=PTD7;
  //��ʼ��UART
  LPLD_UART_Init(uart_init_struct);
  LPLD_UART_EnableIrq(uart_init_struct);
}

