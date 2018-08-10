/******
*第三代循迹算法
*赛道绝对位置差值
*李锐戈 2015 2 12
*
*/

/*******************************************


电容思想控制赛道位置在大多数情况下不可跳变，



*******************************************/
/*
INDUCTOR1 :左外电感
INDUCTOR2 ：左内电感
INDUCTOR3 ：右内电感
INDUCTOR4 ：右外电感
*/

#include "common.h"
#include "include.h"

int32 location[5] = {0,0,0,0,0};//有符号
int32 this_location = 0;
int32 debug_max_location = -1000;
int32 debug_min_location = 1000;

int8 flag_curve = 1;//入弯标志位，为了减速,选择后电感
int8 flag_miss =0;//丢线计数 
int8 flag_changeback = 0 ;//后电感回切前电感的标志位，
int8 flag_mode = 0;

void mode_detecter()
{
  out_all();//关所有灯
  LED7(flag_curve);
  /*********直道********十字教叉********/
  /*****内电感丢线，且2个外电感大于中值******************/
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
    //不好处理这里，使用this——location影响丢线停车
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
  
   
  
  /*****************右大弯**********************************/
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
        //不好处理这里，使用this——location影响丢线停车
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
        //不好处理这里，使用this——location影响丢线停车
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
  
   
  /***************左大弯*********************/
    else if ( ( INDUCTOR1 - INDUCTOR4 > 150 
            && INDUCTOR2 - INDUCTOR3 > 100)
             || (INDUCTOR1 - INDUCTOR4 > 200 && INDUCTOR2 - INDUCTOR3 > 50))
  {
    LED3(ON);
    LED5(ON);
    flag_miss =0;
    location[4] = (INDUCTOR1 + INDUCTOR2)/1.5 ;//(+209~~+1331)
        //不好处理这里，使用this——location影响丢线停车
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
        //不好处理这里，使用this——location影响丢线停车
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
 /*****************左直角弯*************************/
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
        //不好处理这里，使用this——location影响丢线停车
    
    {
     speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
  }
  /*****************右直角弯*************************/
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
        //不好处理这里，使用this——location影响丢线停车
   
    {
      speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
    }
  }
  /******************丢线***************************/
  else if ( INDUCTOR1 < 100 && INDUCTOR2 < 100
          && INDUCTOR3 < 100 && INDUCTOR4 < 100 )
  {
    if ( flag_curve ==1 )//后电感下
    {
      flag_miss++;
      Kd_1 = 0.05;
      if (flag_miss >= 20)
      {
        speed_aim = 0;
      }
    }
   /* else //前电感模式
    {
      flag_curve = 1;
    }*/
  }
  
  else   
  { common_situation();
    //不好处理这里，使用this——location影响丢线停车
    speed_aim = (uint32)(SPEED_MAX - ( SPEED_MAX-SPEED_MIN -SPEED_ERROR ) /1000. * location[4]
                    - SPEED_ERROR * ( flag_curve + flag_changeback ));
  }
}

void detecter()
{
    mode_detecter();
    
/***************从前电感切到后电感********************** 
    
    if ( location[4] > 400 || location[4] < -400 ) //转弯半径较大
    {
      flag_curve = 1;
    }
    */
/***************从后电感回切到前电感*********************/
    if ( location [4] < 300 && location[4] > -300  ) //差值判定为直道
    {
      //******************预回切************************
      if ( flag_changeback == 1 )//此次为前电感值
      {
        if  ( (location[3] - location[4] < 150 && location[3] > location[4] )
          || (location[4] - location[3] < 150 && location[4] > location[3] )) //前后电感差值允许
        {
          flag_changeback = 0;
          flag_curve = 0 ;
        }
        else //差值不允许
        {
          location[4] = location[3];//使用上一次的位置值
          flag_changeback = 0 ;
          flag_curve = 1;           //不允许回切
        }
      }
      else //此次为后电感值
      {
         flag_changeback = 1 ;
         flag_curve = 0;
      }
      
    }
    

/**************通过调整权重来改变灵敏度**********************/
  
 this_location = (int32)(location [0] * 0.05//【0】已经平滑化处理值及权重
               + location [1] * 0.05 //【1】已经平滑化处理值及权重
                 + location [2] * 0.05 //【1】已经平滑化处理值及权重
                   + location [3] * 0.15 //【1】已经平滑化处理值及权重
                    + location [4] * 0.70);//【2】当前AD差值，加入参与平滑化
 
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
  uint8 i = 0; //临时变量之后修改命名//丢线电感数
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


   