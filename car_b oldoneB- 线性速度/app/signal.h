/*****
****���ٷ���ϵͳ H �ļ�
******���ڵƹ⣬����������
****
****2014 11 28 �����
2014 12 30 �����
*/

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

/*****E28������*
**�ҵ�
A6 A5 A4 A7
**
**���
A12 A13 A11 A10
**
**A17 ���ص�
A16��Դ������
***/

#define LED0(OUTPUT)  LPLD_GPIO_Output_b(PTA, 17 ,OUTPUT)
#define LED1(OUTPUT)  LPLD_GPIO_Output_b(PTA, 6 ,OUTPUT)
#define LED2(OUTPUT)  LPLD_GPIO_Output_b(PTA, 5 ,OUTPUT)
#define LED3(OUTPUT)  LPLD_GPIO_Output_b(PTA, 4 ,OUTPUT)
#define LED4(OUTPUT)  LPLD_GPIO_Output_b(PTA, 7 ,OUTPUT)
#define LED5(OUTPUT)  LPLD_GPIO_Output_b(PTE, 25 ,OUTPUT)
#define LED6(OUTPUT)  LPLD_GPIO_Output_b(PTE, 26 ,OUTPUT)
#define LED7(OUTPUT)  LPLD_GPIO_Output_b(PTE, 27 ,OUTPUT)
#define LED8(OUTPUT)  LPLD_GPIO_Output_b(PTE, 28 ,OUTPUT)

#define BEEP1(OUTPUT) LPLD_GPIO_Output_b(PTA, 16 ,OUTPUT)


void signal_init();
void light_all();//�����е�
void out_all();//�����е�



#endif