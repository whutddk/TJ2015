/********超声波模块 H文件****************
*******李锐戈 2015 2 6
*
*
*/

#ifndef _SONAR_H_
#define _SONAR_H_

#define TRIO_PT PTC
#define TRIO_PIN GPIO_Pin12
#define TRIO_NUM 12

#define ECHO_PT PTC
#define ECHO_PIN GPIO_Pin13
#define ECHO_NUM 13

void sonar_init();
void sonar_detect();
void sonar_ISR();









#endif