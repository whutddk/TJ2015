/*
**传感器（硬件部分头文件）
***主要为AD采集
****同时放置了定长队列的头文件
李锐戈
2014 11 25
2015 1 10 李锐戈
*/
#ifndef _SENSOR_H_
#define _SENSOR_H_

#define QUEMAX 10             /*队列长度*/
#define QUEUE_INIT 1000       /*初始化队列的值（起跑为直道，应该中值）*/


extern int16 AD[8];    //传感器转换结果归一化,为避免浮点运算，*100





typedef struct queue//该队列为定长
{
  uint16 data[QUEMAX];
  uint8 front;
  uint8 rear;
}que;

void point_move(que *q);//队头队尾移动
void queue_int( que *q );//对建立的一个队列进行初始化
uint16 update_que( que *q , uint16 data_in );//入队和出队一次

void sensors_init();
void Get_AD_data(); //获取电感值并归一化（100）


#endif