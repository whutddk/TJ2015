/************************
****A车主程序（测试期间使用）C
****李锐戈 2015 2 14
****
*
*/


#include "common.h"
#include "include.h"

uint8 flag_a_car = 0;
extern int8 flag_backmiss;
void a_car_main()
{
  /******************************************/
  if ( flag_5ms )
  {
    flag_5ms = 0;
    detecter();                //赛道判定  

    if (flag_backmiss == 1)
    { 
      LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10);
      LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1,SERVO_PWM_MID + SERVO_PWM_REVISE);
      speed_aim=0;
    }
    
  }
  
  /*****************************************/
  if ( flag_10ms )
  {
    flag_10ms = 0;
    get_count();              //计算脉冲
    
    
  }
  
  /******************************************/
  if ( flag_30ms )
  {
    flag_30ms = 0;     
    servo_set();                      //对之前赛道数据进行处理，PD控制后设置舵机
    
    
    //ScanNorma(1);
    //push(0,max_AD[0]);
    //push(1,max_AD[1]);//right
    //push(2,max_AD[2]);//left
    //push(3,max_AD[3]);
    //push(4,max_AD[4]);
    //push(5,max_AD[5]);
    //push(6,max_AD[6]);
    //push(7,max_AD[7]);
    
  }
  
  /*****************************************/
  if ( flag_60ms )
  {     
    flag_60ms = 0;          
    speed_getcurrent();
    speed_set();      //设置电机速度
    sendDataToScope();                //发送一帧     
  }
  
  /****************************************/    
  if ( flag_1s)
  {
    flag_1s = 0;
    //调试阶段，屏蔽扫面，采用之前采集标定的数据
    //ScanNorma(1);     //扫面标定
    
    //BEEP1(ON);
    
  }
}

//
//void a_car_init()
//{
//  record_start();
//  record_detecter_init();
//}