/*****
****快速反馈系统 H 文件
******用于灯光，蜂鸣器控制
****
****2014 11 28 李锐戈
2014 12 30 李锐戈
*/

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

/*****E28开锁存*
**右灯
A6 A5 A4 A7
**
**左灯
A12 A13 A11 A10
**
**A17 板载灯
A16有源蜂鸣器
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
void light_all();//开所有灯
void out_all();//关所有灯



#endif