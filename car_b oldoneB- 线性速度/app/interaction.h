/******人机交互 H 文件
*****包括LCD5110 键盘 拨码开关
*李锐戈 2014 12 30
*
******/

#ifndef _INTERACTION_H__
#define _INTERACTION_H__

void interaction_init();//初始化包括拨码开关，键盘，LCD
uint8 mode_switch();
uint8 keyboard_detect();
//void program_switch();
void LCDTIME(void);




#endif 