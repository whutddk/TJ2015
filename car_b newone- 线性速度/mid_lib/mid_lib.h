/*****
******�в����ͷ�ļ��������Լ�д���в��ĺ����ڴ�����
�����
2014 11 16
����� 2015 2 14 ����������ֻ��32λ�ĵ�λ������ʹ�ã����ۿ��� 
*****/

#ifndef _MID_LIB_H_
#define _MID_LIB_H_


#include "common.h"
#include "include.h"


/*����ʹ�����ð��������ںţ������ʣ��Ƿ�ʹ�ý����ж�
******
****
**
*
����ȫ��Ĭ��*/
void uart0_init();
void uart0_isr_init();
void uart_isr(void);
/*�������LPLD��*/

/*ADC��ʼ����������� ADC�ţ�λ��***/
void ADC_Init_solf ( ADC_Type *Adcx , uint8 BitMode );
/*ADC��ʼ����Ӳ������
******************
******************
*****************
��ʱ�޷�ʹ��
****************
**************
*/

/*�������LPLD��*/

/*FTM_PWMʹ�����ã���
******
****
**
*
���ſɵ�����
pin--FTMxͨ����Ӧ������
 *      FTM0
 *       FTM_Ch0-PTA3\PTC1
 *       FTM_Ch1-PTA4\PTC2
 *       FTM_Ch2-PTA5\PTC3
 *       FTM_Ch3-PTA6\PTC4
 *       FTM_Ch4-PTA7\PTD4
 *       FTM_Ch5-PTA0\PTD5
 *       FTM_Ch6-PTA1\PTD6
 *       FTM_Ch7-PTA2\PTD7*/

/*������FTM0��ͨ������ʼ����5000����ռ�ձ�*/
void PWM0_init();                 //FTM0ͨ���࣬8ͨ�����ڿ���PWM
void PWM1_init();                 //FTM���ڿ��Ƶ�������Կ��ǽ���
/*
�ı�ռ�ձ���LPLD�Ŀ�
*/

//void ic_init();//���벶׽��
//void ic_isr();//������δ�������μ���
/*      FTM1
 *       FTM_Ch0-PTA8\PTA12\PTB0
 *       FTM_Ch1-PTA9\PTA13\PTB1
 *      FTM2
 *       FTM_Ch0-PTA10\PTB18
 *       FTM_Ch1-PTA11\PTB19
 *    capture_edge--�����Ե����
 *      |__CAPTURE_RI    --�����ز���
 *      |__CAPTURE_FA    --�½��ز���
 *      |__CAPTURE_RIFA  --�����½��ز���
 *
*/

/*********************************
**PIT��ʱ������
***********************************/
extern uint32 solfware_count;//����ܼ�ʱ
extern uint8 flag_delay_complete;
extern uint8 sonar_count;


void pit0us_init();//100US���� ���������
void pit1ms_init();//5ms���ڵ�вɼ��ͱ�׼�ӳ�
void pit2ms_init();//mS
void pit3us_init(uint32 Periodus);//US
void pit0us_isr();//���ڳ�����
void pit1ms_isr();//����������ʱ
void pit2ms_isr();//��������ܼ�ʱ
void pit3us_isr();//
void delay(uint32 time_us);//��׼��ʱ������us
void disable_all_isr();
void enbale_all_isr();


/*****
***24L01
***
*/

//extern uint8 Flag_Smitte;

//uint8 LPLD_Nrf24L01_Init();//��ʼ��24L01

//uint8 LPLD_Nrf24L01_TxModeInit();//��ʼ������ģʽ

//void nrf24l01_RX_init();//��ʼ������ģʽ

//void nrf24l01_checksend();//��鷢�ͱ�־λ�����Ϊ�棬�ͷ���32Ϊbuf�е�����

//void porte_handle(void);//�����ж�



/***
****LPTMR
****
*/

//extern uint16 pluse_count_h ; //�����������λ
extern uint32 pluse_count_l ; //���������

void lpt_init(void);//�������C5��
void get_count();//����
#endif