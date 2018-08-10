/**
* --------------基于"拉普兰德K60底层库V3"的工程（car_b）-----------------
* @file car_b.c
* @version 0.0
* @date 2013-9-29
* @brief 关于该工程的描述
*
* 版权所有:北京拉普兰德电子技术有限公司
* http://www.lpld.cn
* mail:support@lpld.cn
* 硬件平台:  LPLD K60 Card / LPLD K60 Nano
*
* 本工程基于"拉普兰德K60底层库V3"开发，
* 所有开源代码均在"lib"文件夹下，用户不必更改该目录下代码，
* 所有用户工程需保存在"project"文件夹下，以工程名定义文件夹名，
* 底层库使用方法见相关文档。 
*
*李锐戈 2015 1 24
*
*
*/
#include "include.h"
#include "common.h"



void main (void)
{
  interaction_init();   //人机交互初始化
  LCD_init();      
  servo_init();         //舵机控制初始化
  lpt_init();           //脉冲计数初始化
  uart0_isr_init();     //0号蓝牙初始化
  sensors_init();       //打开8个电感ADC并使能
  motto_init();         //电机控制初始化
  pit0us_init();       //超声波测距
  pit1ms_init();        //主函数计时
  signal_init();        //信号初始化
  gpio_key_init();      //起跑按键选项初始化
  
  //调试阶段，屏蔽扫面，采用之前采集的数据
  //ScanNorma(2000);     //扫面标定
  flag_a_car = 1;
  key_select();          //起跑按键选项
  light_all();
  delay(4000000);
  out_all();
  while(1)
  {   
    if (!flag_stop)
    {
      while(flag_a_car)
      {
        a_car_main();
      }
      
    }
    else
    {
      LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10);
      LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1,SERVO_PWM_MID + SERVO_PWM_REVISE);
    }
  }  
}






//beep_long();
