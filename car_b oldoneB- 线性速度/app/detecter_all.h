/*所有寻线代码的头文件
*主要针对于1号车8电感模型
**
***2014 11 26 李锐戈
2015 1 24 李锐戈
****
*/

#ifndef _DETECTER_ALL_H_
#define _DETECTER_ALL_H_


 
extern int32 location[5];//有符号
extern int32 this_location;

extern uint16 max_AD[8];//归一化（100）
extern uint16 min_AD[8];
extern int16 angle;


#define DET_NUM 5

#define LINE_ABOVE_UP  600    //电感在线正上方且垂直 DATA > Ta
#define LINE_ABOVE_DOWN  500    //DATA < Ta

#define LINE_MISS_UP   100    //电感丢线 DATA > Ta
#define LINE_MISS_DOWN 85       //DATA < Ta


#define LINE_MID1_UP    110   //线在赛道正中 DATA > Ta
#define LINE_MID2_UP    400


extern uint16 SPEED_MAX;
extern uint16 SPEED_MIN;


#define DEFFER1  300
#define DEFFER2  100
#define INDUCTOR1 AD[3]
#define INDUCTOR2 AD[2]
#define INDUCTOR3 AD[1]
#define INDUCTOR4 AD[0]
#define INDUCTOR5 AD[7]
#define INDUCTOR6 AD[6]
#define INDUCTOR7 AD[4]
#define INDUCTOR8 AD[0]


extern uint16 AD_data[8][DET_NUM];//每个通道取N个值的存放位置
extern uint16 AD_average[8];//四个传感器滤波后的值
extern uint16 max_AD[8]; //存放最大采样值数组
extern uint16 min_AD[8];//存放最小值
extern int8 flag_cross;
extern int8 flag_curve;
extern int16 Front_INDUCTOR;
void mode_detecter();
void Get_AD_data();
void ScanNorma(uint16 times);
void detecter();
void common_situation();




#endif