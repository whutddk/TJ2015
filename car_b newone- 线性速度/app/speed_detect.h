/***********速度控制和检测H文件
**************
*************2014 12 14 李锐戈
2015 2 14 李锐戈 、、只有32位低位
*/

#ifndef __SPEED_DETECT_H__
#define __SOEED_DETECT_H__

//车轮直径//55mm
//车轮周长PI*D = 3.14159*55MM=172.78745
//车轮周长PI*D = 3.14159*56MM=175.92904

#define WHELL_C 174
#define SPEED_AVE_TIME 60


//extern uint16 pluse_h_sta;//起始高位
//extern uint32 pluse_l_sta ;//起始低位
//extern uint32 solfwave_sta;//起始的程序计数（时间）
//extern uint16 speed_ave;//平均速度
//extern uint8 flag_speed;//排除起始一次


void speed_count();//全自动速度测试

 
void speed_getcurrent();//瞬时速度





#endif 