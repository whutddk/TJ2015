#ifndef _SELECTION_H_
#define _SELECTION_H_

/*****使用宏定义选择功能
李锐戈
2014 11 25
2015 1 14
*****
*/

#ifndef OFF
#define OFF 0
#endif

#ifndef ON
#define ON 1
#endif

#define DETECT1 OFF
#define DETECT2 ON
#define POSITION ON
#define FREECARS_MOTTO OFF

#define NRF24L01R OFF
#define NRF24L01T OFF



/*****************push_list******************
0 AD_average[0]
1 AD_average[1]
2 AD_average[2]
3 AD_average[3]
4 AD                      
5 pwm_dutySERVO
6 ,speed_aim
7 
8 last_location
9 MOTTO_PWM
10 MOTTO_PID_OUT
*/



#endif