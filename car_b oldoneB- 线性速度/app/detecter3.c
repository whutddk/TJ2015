/******
*������ѭ���㷨
*��������λ�ò�ֵ
*����� 2015 2 12
*
*/

/*******************************************


����˼���������λ���ڴ��������²������䣬



*******************************************/
/*
INDUCTOR1 :������
INDUCTOR2 �����ڵ��
INDUCTOR3 �����ڵ��
INDUCTOR4 ��������
*/

#include "common.h"
#include "include.h"

int32 location[5] = {0,0,0,0,0};//�з���
int32 this_location = 0;
int32 debug_max_location = -1000;
int32 debug_min_location = 1000;

int8 flag_curve = 1;//�����־λ��Ϊ�˼���,ѡ�����
int8 flag_miss =0;//���߼��� 
int8 flag_changeback = 0 ;//���л���ǰ��еı�־λ��
int8 flag_mode = 0;

void mode_detecter()
{
  out_all();//�����е�
  LED7(flag_curve);
  /*********ֱ��********ʮ�ֽ̲�********/
  /*****�ڵ�ж��ߣ���2�����д�����ֵ******************/
  if ( ( (INDUCTOR2 < 100 && INDUCTOR3 < 100 ) 
      && ( (INDUCTOR1 >100)&&(INDUCTOR4 > 100) ) ) 
        || (INDUCTOR2 > 300  && INDUCTOR3 > 300 
            && (INDUCTOR2 - INDUCTOR3 < 100 || INDUCTOR3 - INDUCTOR2 < 100 ))
          || (INDUCTOR1 > 150 && INDUCTOR4 > 150 ))
  {
    LED1(ON);
    flag_miss =0;
    location[4] = ( INDUCTOR1 - INDUCTOR4 )  ;//(-136~~+262)
    Kd_1 = 0.;
    //���ô������ʹ��this����locationӰ�춪��ͣ��
    if ( location[4] >=0 )
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
    else
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
  }
  
   
  
  /*****************�Ҵ���**********************************/
  /****************************************************/
  else if (( INDUCTOR4 - INDUCTOR1 > 150 
            && INDUCTOR3 - INDUCTOR2 > 100)
           || ( INDUCTOR4 - INDUCTOR1 > 200 && INDUCTOR3 - INDUCTOR2 > 50))
  {
    LED2(ON);
    LED5(ON);
    flag_miss =0;    

    location[4] =( 0 - INDUCTOR3 - INDUCTOR4 ) / 1.5 ;
    flag_mode = 1;
        //���ô������ʹ��this����locationӰ�춪��ͣ��
    if ( location[4] >=0 )
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
    else
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }    Kd_1 = 0.05;
  }
  else if ( INDUCTOR1 < 100
           && INDUCTOR2 < 100 
             && INDUCTOR3 < 100
               && INDUCTOR4 > 120 
                 )
  {
    LED2(ON);
    LED6(ON);
    flag_miss =0;
    location[4] = ( INDUCTOR4 /2 - 1000 );
        //���ô������ʹ��this����locationӰ�춪��ͣ��
    if ( location[4] >=0 )
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
    else
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
    Kd_1 = 0.05;
  }
  
   
  /***************�����*********************/
    else if ( ( INDUCTOR1 - INDUCTOR4 > 150 
            && INDUCTOR2 - INDUCTOR3 > 100)
             || (INDUCTOR1 - INDUCTOR4 > 200 && INDUCTOR2 - INDUCTOR3 > 50))
  {
    LED3(ON);
    LED5(ON);
    flag_miss =0;
    location[4] = (INDUCTOR1 + INDUCTOR2)/1.5 ;//(+209~~+1331)
        //���ô������ʹ��this����locationӰ�춪��ͣ��
    if ( location[4] >=0 )
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
    else
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
    Kd_1 = 0.05;
  }
  else if ( INDUCTOR1 > 120
           && INDUCTOR2 < 100 
             && INDUCTOR3 < 100
               && INDUCTOR4 < 100 
                 )
  {
    LED3(ON);
    LED6(ON);
    flag_miss =0;
    Kd_1 = 0.05;
    location[4] = (INDUCTOR1/ (-2) +1000 ); //(94~~978)
        //���ô������ʹ��this����locationӰ�춪��ͣ��
    if ( location[4] >=0 )
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
    else
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
  }
 /*****************��ֱ����*************************/
  else if ( INDUCTOR2 > 200 && INDUCTOR3 < 120)
  {
   flag_miss =0;
    location [0] 
      = location [1]
        = location [2]
          = location [3]
            = location [4]
              = 1000;
    Kd_1 = 0.05;
        //���ô������ʹ��this����locationӰ�춪��ͣ��
    
    {
     speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
  }
  /*****************��ֱ����*************************/
   else if ( INDUCTOR2 < 120 && INDUCTOR3 > 200)
  {
    flag_miss =0;    
    location [0] 
      = location [1]
        = location [2]
          = location [3]
            = location [4]
              = - 1000;
    Kd_1 = 0.05;
        //���ô������ʹ��this����locationӰ�춪��ͣ��
   
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
  }
  /******************����***************************/
  else if ( INDUCTOR1 < 100 && INDUCTOR2 < 100
          && INDUCTOR3 < 100 && INDUCTOR4 < 100 )
  {
    if ( flag_curve ==1 )//������
    {
      flag_miss++;
      Kd_1 = 0.05;
      if (flag_miss >= 20)
      {
        speed_aim = 0;
      }
    }
   /* else //ǰ���ģʽ
    {
      flag_curve = 1;
    }*/
  }
  
  else   
  { common_situation();
    //���ô������ʹ��this����locationӰ�춪��ͣ��
    speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
  }
}

void detecter()
{
    mode_detecter();
    
/***************��ǰ����е�����********************** 
    
    if ( location[4] > 400 || location[4] < -400 ) //ת��뾶�ϴ�
    {
      flag_curve = 1;
    }
    */
/***************�Ӻ��л��е�ǰ���*********************/
    if ( location [4] < 300 && location[4] > -300  ) //��ֵ�ж�Ϊֱ��
    {
      //******************Ԥ����************************
      if ( flag_changeback == 1 )//�˴�Ϊǰ���ֵ
      {
        if  ( (location[3] - location[4] < 150 && location[3] > location[4] )
          || (location[4] - location[3] < 150 && location[4] > location[3] )) //ǰ���в�ֵ����
        {
          flag_changeback = 0;
          flag_curve = 0 ;
        }
        else //��ֵ������
        {
          location[4] = location[3];//ʹ����һ�ε�λ��ֵ
          flag_changeback = 0 ;
          flag_curve = 1;           //���������
        }
      }
      else //�˴�Ϊ����ֵ
      {
         flag_changeback = 1 ;
         flag_curve = 0;
      }
      
    }
    

/**************ͨ������Ȩ�����ı�������**********************/
  
 this_location = (int32)(location [0] * 0.05//��0���Ѿ�ƽ��������ֵ��Ȩ��
               + location [1] * 0.05 //��1���Ѿ�ƽ��������ֵ��Ȩ��
                 + location [2] * 0.05 //��1���Ѿ�ƽ��������ֵ��Ȩ��
                   + location [3] * 0.15 //��1���Ѿ�ƽ��������ֵ��Ȩ��
                    + location [4] * 0.70);//��2����ǰAD��ֵ���������ƽ����
 
 /*****************************************/
 if ( this_location >= 1000 )
   this_location = 1000;
 if ( this_location <= -1000 )
   this_location = -1000;
 /******************************************/
 location [0] = location[1];
 location [1] = location[2];
 location [2] = this_location;
 location [3] = location [4];
       push(6,speed_aim);
       push(11,flag_curve);
   //push(10,location [4]);
}

void common_situation()
{
  uint8 i = 0; //��ʱ����֮���޸�����//���ߵ����
    float j = 1;
  
  light_all();
  flag_miss = 0; 
  flag_mode = 0;
    if (INDUCTOR1 < 85 )
    {
      INDUCTOR1 = 0;
      i ++;
    }
    if (INDUCTOR2 < 85 )
    {
      INDUCTOR2 = 0;
      i ++;
    }
    if (INDUCTOR3 < 85 )
    {
      INDUCTOR3 = 0;
      i ++;
    }
    if (INDUCTOR4 < 85 )
    {
      INDUCTOR4 = 0;
      i ++;
    }
    switch ( i )
    {
    case ( 0 ): j=0.7;Kp_1 = 0.01; //(252)
    break;
    case ( 1 ): j=3;Kp_1 = 0.01;//(-37~~696)
    break;
    case ( 2 ): 
      { j = 5 ;Kp_1 = 0.01;//(170~~1688)
    break; } 
    case ( 3 ): j=5;Kp_1 = 0.01;//(0~~1500)
    break;
    default   : j=1;
    }
    location[4] = ( int32 )(( INDUCTOR1 - INDUCTOR4 + INDUCTOR2 - INDUCTOR3 ) * j );
}


   