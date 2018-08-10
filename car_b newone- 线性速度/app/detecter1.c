/*
**第一套赛道分析算法
***4电感，2横 2竖
李锐戈
2014 11 27
*/

#include "common.h"
#include "include.h"

#define NOLINE 10 //采到的值小于该值判定为电感丢线
#define K_DET1 0.01
#define MID_VALUE 2000

uint16 ind1,ind2,ind3,ind4;//定义四个处理的电感值
//该值已经处理好，可以直接分析
//4个值从左往右 横竖横竖





void mode_detect1()//模式识别代码
{
  
}


void detect1()  //设返回值为0则正对中线
{
  mode_detect1();//调用模式识别函数，
  if ( ind1 < NOLINE  && ind4 <NOLINE )//2个电感发生丢线
  {
    this_location = last_location;
  }
  else if (ind1 > NOLINE && ind2 >NOLINE)//两外电感均有线
  {
    this_location = ( int16 ) K_DET1 * ( ind4 - ind1 ) ; //简单相减，乘上比例归一化
  }
  else//有一个没线
  {
    if (ind1 < NOLINE )
    {
      this_location = ( ind4 - MID_VALUE ) * 2 ;
    }
    else
    {
      this_location = ( ind1 - MID_VALUE ) * 2 ;
    }
  }
  last_location = this_location ;
   
      
    
}