/************************
****A�������򣨲����ڼ�ʹ�ã�C
****����� 2015 2 14
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
      detecter();                //�����ж�  
      get_count();              //��������
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
      
      servo_set();                      //��֮ǰ�������ݽ��д���PD���ƺ����ö��
 
    }
    
/******************************************/
    if ( flag_30ms )
    {
      flag_30ms = 0;     
      speed_getcurrent();
      sendDataToScope();                //����һ֡     
      
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

#if !FREECARS_MOTTO 
    
      speed_set();      //���õ���ٶ�

      
#else
     //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10);
#endif
      
    //sonar_detect();  
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
//���Խ׶Σ�����ɨ�棬����֮ǰ�ɼ��궨������
     //ScanNorma(1);     //ɨ��궨

     //BEEP1(ON);
      
    }
}


void a_car_init()
{
  record_start();
  record_detecter_init();
}