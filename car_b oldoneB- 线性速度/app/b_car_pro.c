/************************
****A�������򣨲����ڼ�ʹ�ã�C
****����� 2015 2 15
****
*
*/

#include "common.h"
#include "include.h"

uint8 flag_b_car = 0;

void b_car_main()
{
  /******************************************/
    if ( flag_5ms )
    {
      flag_5ms = 0; 
       get_count();  
      //get_location();
    }
    
/*****************************************/
    if ( flag_10ms )
    {
      flag_10ms = 0;
                      
      //push(8,this_location);

     servo_set();//��֮ǰ�������ݽ��д���PD���ƺ����ö��
    }
    
/******************************************/
    if ( flag_30ms )
    {
      flag_30ms = 0;     
      speed_getcurrent();
      sendDataToScope();                //����һ֡     
    }
    
/*****************************************/
    if ( flag_60ms )
    {
      
      flag_60ms = 0;       

#if !FREECARS_MOTTO 
    speed_aim = 500;
      speed_set();      //���õ���ٶ�

      
#else
     //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10);
#endif
      
    sonar_detect();  
    }
       
/*****************************************/ 
    if ( flag_70ms )
    {
      flag_70ms = 0;
      //BEEP1(OFF);
    }
        
/*****************************************/
    if ( flag_80ms )
    {
      flag_80ms = 0;
      LCDTIME();
    }
        
/*****************************************/
    if ( flag_90ms )
    {
      flag_90ms = 0;
    }
        
/*****************************************/
    if ( flag_100ms )
    {
      flag_100ms = 0;
      
    }
/*****************************************/
    if ( flag_250ms )
    {
      flag_250ms = 0;

    }
/****************************************/
    if ( flag_500ms)
    {
      
      flag_500ms = 0;


    }
/****************************************/    
    if ( flag_1s)
    {
     flag_1s = 0;

     BEEP1(ON);
      
    }
}

void b_car_init()
{
  record_start();
}