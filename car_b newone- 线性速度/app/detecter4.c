/****第四代赛道检测程序
*用于8电感同步检测
***********李锐戈
***********2015 3 7
***/

/*******************************************


电容思想控制赛道位置在大多数情况下不可跳变，



*******************************************/
/*
INDUCTOR1 :前左外电感
INDUCTOR2 ：前左内电感
INDUCTOR3 ：前右内电感
INDUCTOR4 ：前右外电感
*/

/*
INDUCTOR5 :后左外电感
INDUCTOR6 ：后左内电感
INDUCTOR7 ：后右内电感
INDUCTOR8 ：后右外电感
*/

#include "common.h"
#include "include.h"

int32 location[5] = {0,0,0,0,0};//有符号
int32 back_location[5] = {0,0,0,0,0};//有符号
int32 front_location[5] = {0,0,0,0,0};//有符号
int32 this_location = 0;
int8 flag_curve = 1;//入弯标志位，为了减速,选择后电感
int8 flag_frontmiss = 0;
int8 flag_backmiss = 0;
int32 last_front_location;
int32 last_back_location;
int32 front_INDUCTOR_a;
void back_mode_detecter()//后电感位置判定
{
//  uint8 i = 0; //临时变量之后修改命名//丢线电感数
//  float j = 1;
  static int8 flag_miss =0;//丢线计数
  
  //out_all();//关所有灯
  /*********直道********十字教叉********/
  /*****内电感丢线，且2个外电感大于中值******************/
  if ( front_INDUCTOR_a>500&&(( (INDUCTOR6 < 100 && INDUCTOR7 < 100 ) 
                               && ( (INDUCTOR5 >100)&&(INDUCTOR8 > 100) ) ) 
                              || (INDUCTOR6 > 300  && INDUCTOR7 > 300 
                                  && (INDUCTOR6 - INDUCTOR7 < 100 || INDUCTOR7 - INDUCTOR6 < 100 ))             //这里有问题
                                || (INDUCTOR5 > 150 && INDUCTOR8 > 150 &&INDUCTOR6<200&&INDUCTOR7<200)))
  {
    flag_miss =0;
    back_location[4] = ( INDUCTOR5 - INDUCTOR8 );
    if(back_location[4]<0){back_location[4]=back_location[4]/1.1;}
    else{back_location[4]=back_location[4]/1.3;}
    last_back_location=back_location[4];
    out_all();
    //light_all();
  }
  /*********直道中的特殊情况****************/
  else if(front_INDUCTOR_a>500&&INDUCTOR5>500&&INDUCTOR6<30&&INDUCTOR7<30&&INDUCTOR8<100&&INDUCTOR8>50)   //右侧内
  {
    back_location[4] = ( INDUCTOR5 - INDUCTOR8 )/1.6;out_all();
  } 
  else if(front_INDUCTOR_a>500&&(INDUCTOR5>700&&INDUCTOR6<20&&INDUCTOR7<20&&INDUCTOR8<50)||(INDUCTOR5>700&&INDUCTOR6>100&&INDUCTOR6<200&&INDUCTOR7<80&&INDUCTOR8<65))              //这里有问题
  { 
    back_location[4] = ( INDUCTOR5 - INDUCTOR8 )+100;out_all();
  }
  //右侧外
  
  /*****************右大弯**********************************/
  /****************************************************/
  else if ((front_INDUCTOR_a<20&&INDUCTOR5<20&&INDUCTOR8>30&&INDUCTOR7<80&&(INDUCTOR7>INDUCTOR6)&&INDUCTOR7>30&&INDUCTOR8>50&&INDUCTOR8<200)
           ||(front_INDUCTOR_a<20&&INDUCTOR5<30&&INDUCTOR6<40&&INDUCTOR7>90&&INDUCTOR8>50&&INDUCTOR7<500&&INDUCTOR8<500)
             ||(front_INDUCTOR_a<10&&INDUCTOR5<20&&INDUCTOR6<20&&INDUCTOR7>100&&INDUCTOR8>200&&INDUCTOR7<500&&INDUCTOR8<500)
               ||(INDUCTOR5>15&&INDUCTOR5<60&&INDUCTOR6>10&&INDUCTOR6<25&&INDUCTOR7>400&&INDUCTOR7<600&&INDUCTOR8>250&&INDUCTOR8<400 )
                 ||(INDUCTOR5>20&&INDUCTOR5<65&&INDUCTOR6<30&&INDUCTOR7>130&&INDUCTOR7<220&&INDUCTOR8>350&&INDUCTOR8<550)
                   ||(INDUCTOR5>20&&INDUCTOR5<65&&INDUCTOR6>45&&INDUCTOR6<80&&INDUCTOR7>350&&INDUCTOR7<700&&INDUCTOR8>300&&INDUCTOR8<500)
                     ||(INDUCTOR5>50&&INDUCTOR5<150&&INDUCTOR6>45&&INDUCTOR6<150&&INDUCTOR7>220&&INDUCTOR7<550&&INDUCTOR8>230&&INDUCTOR8<400))
  {
    flag_miss =0;
    back_location [4] =  - 1000;
  }
  
  else if (( INDUCTOR8 - INDUCTOR5 > 250 
            && INDUCTOR7 - INDUCTOR6 > 100)
           || ( INDUCTOR8 - INDUCTOR5 > 200 && INDUCTOR7 - INDUCTOR6 > 150) 
             ||INDUCTOR8>500&&INDUCTOR7>300&&INDUCTOR6<50&&INDUCTOR5<200
               ||INDUCTOR5>100&&INDUCTOR6<50&&INDUCTOR7-INDUCTOR6>300&&INDUCTOR8-INDUCTOR5>50 )
  {
    flag_miss =0;
    back_location[4] = (int32)( ( 0 - INDUCTOR7 - INDUCTOR8 ) / 1.5) ;
    last_back_location=back_location[4];
    out_all();
    //light_all();
  }
  
  else if ( INDUCTOR5 < 100 && INDUCTOR6 < 50 && INDUCTOR7 < 50&& INDUCTOR8 > 500 
           )
  {
    flag_miss =0;
    back_location[4] = -INDUCTOR8 ;
    last_back_location=back_location[4];
    out_all();
    //light_all();
  }
  
  else if ( INDUCTOR5 < 50
           && INDUCTOR6 < 50 
             && INDUCTOR7 < 50
               && INDUCTOR8 > 700
                 )
  {
    flag_miss =0;
    back_location[4] = -1000;
    last_back_location=back_location[4];
    out_all();
    //light_all();
  }
  else if((INDUCTOR5<40&&INDUCTOR6<40&&INDUCTOR7>100&&INDUCTOR7<300&&INDUCTOR8<40)
          ||(INDUCTOR5<20&&INDUCTOR6<20&&INDUCTOR7>60&&INDUCTOR7<250&&INDUCTOR8<20))
  {
    flag_miss =0;
    back_location [4] = - 800;
    last_back_location=back_location[4];
    out_all();
  }
  
  /***************左大弯*********************/
  else if(INDUCTOR5>300&&INDUCTOR6>70&&INDUCTOR6<250&&INDUCTOR7<30&&INDUCTOR8<40)     //弯道外侧特殊情况
  {
    flag_miss =0;
    back_location [4] =  800;
    out_all();
  }
  else if ( ( front_INDUCTOR_a<20&&INDUCTOR5>50&&INDUCTOR5<200&&INDUCTOR6>30&&INDUCTOR6<80&&(INDUCTOR5>INDUCTOR6)&&INDUCTOR7<20&&INDUCTOR8<30)
           ||(front_INDUCTOR_a<20&&INDUCTOR5>200&&INDUCTOR6>200&&INDUCTOR7<30&&INDUCTOR8<30))
  {
    flag_miss =0;
    back_location [4] =  800;
  out_all();
  }
  else if ( ( INDUCTOR5 - INDUCTOR8 > 250 
             && INDUCTOR6 - INDUCTOR7 > 100)
           || (INDUCTOR5 - INDUCTOR8 > 200 && INDUCTOR6 - INDUCTOR7 > 150)
             || ( INDUCTOR5 > 500 && INDUCTOR6>300&&INDUCTOR7<50&&INDUCTOR8<210 ))
  {
    flag_miss =0;
    back_location[4] = (int32)((INDUCTOR5 + INDUCTOR6)/1.5) ;
    last_back_location=back_location[4];
    out_all();
    //light_all();
  }
  else if ( INDUCTOR5 > 500
           && INDUCTOR6 < 50 
             && INDUCTOR7 < 50
               && INDUCTOR8 < 100 
                 )
  {
    flag_miss =0;
    back_location[4] = (INDUCTOR5/32)*(INDUCTOR5/32); 
    last_back_location=back_location[4];
    out_all();
    //light_all();
  }
  else if((INDUCTOR5<40&&INDUCTOR6>100&&INDUCTOR6<300&&INDUCTOR7<40&&INDUCTOR8<40)
          ||(INDUCTOR5<20&&INDUCTOR6>70&&INDUCTOR6<250&&INDUCTOR7<20&&INDUCTOR8<20))
  {
    flag_miss =0;
    back_location [4] = 800;
    last_back_location=back_location[4];
    out_all();
  }
  /*****************左直角弯*************************/
  else if ((  INDUCTOR6 > 500 && INDUCTOR7<50 &&INDUCTOR8<150&&INDUCTOR5>600)
           ||(INDUCTOR6>400&&INDUCTOR7<80&&INDUCTOR8<100&&INDUCTOR5>700)
             ||(INDUCTOR6>350&&INDUCTOR8<70&&INDUCTOR7<30&&INDUCTOR5>750)
               ||(INDUCTOR5>200&&INDUCTOR7<10&&INDUCTOR6>80&&INDUCTOR8<10))
  {
    flag_miss =0;
    back_location [0] 
      = back_location [1]
        = back_location [2]
          = back_location [3]
            = back_location [4]
              = 1000;
    last_back_location=back_location[4];
    out_all();
    //light_all();
  }
  
  /*****************右直角弯*************************/
  else if ((  INDUCTOR7 > 500 && INDUCTOR6 < 50&&INDUCTOR5<150&&INDUCTOR8>600)
           ||(INDUCTOR7>400&&INDUCTOR6<80&&INDUCTOR5<100&&INDUCTOR8>700)
             ||(INDUCTOR7>350&&INDUCTOR6<30&&INDUCTOR5<80&&INDUCTOR8>750)
               ||(INDUCTOR7>200&&INDUCTOR6<10&&INDUCTOR5<10&&INDUCTOR8>300))
  {
    flag_miss =0;    
    back_location [0] 
      = back_location [1]
        = back_location [2]
          = back_location [3]
            = back_location[4]
              = - 1000;
    speed_aim=10;
    last_back_location=back_location[4];
    out_all();
    //light_all();
  }
  /***************右大弯中的特殊情况*********************/
  else if (INDUCTOR5-INDUCTOR8>200&&INDUCTOR6-INDUCTOR7>150)      //弯道内侧
  {
    flag_miss =0;
    back_location [4]=INDUCTOR5-INDUCTOR8;
    last_back_location=back_location[4]/2;
    out_all();
  }
  else if ((INDUCTOR5<5&&INDUCTOR6<25&&INDUCTOR7<30&&INDUCTOR8>50)  //弯道外侧
           ||(INDUCTOR5<15&&INDUCTOR6>20&&INDUCTOR6<60&&INDUCTOR7>200&&INDUCTOR7<350&&INDUCTOR8>140&&INDUCTOR8<350)
             ||(INDUCTOR5<5&&INDUCTOR6>15&&INDUCTOR6<45&&INDUCTOR7>100&&INDUCTOR7<250&&INDUCTOR8>30&&INDUCTOR8<65)
               ||(INDUCTOR5<20&&INDUCTOR6>20&&INDUCTOR6<50&&INDUCTOR7>100&&INDUCTOR7<250&&INDUCTOR8>100&&INDUCTOR8<350)
                 ||(INDUCTOR5<60&&INDUCTOR6<90&&INDUCTOR7>100&&INDUCTOR7<500&&INDUCTOR8>50&&INDUCTOR8<400)
                   ||(INDUCTOR5>300&&INDUCTOR5<450&&INDUCTOR6>100&&INDUCTOR6<220&&INDUCTOR7>500&&INDUCTOR7<700&&INDUCTOR8>300&&INDUCTOR8<410)
                     |(INDUCTOR5<10&&INDUCTOR6<10&&INDUCTOR7>200&&INDUCTOR7<450&&INDUCTOR8>80&&INDUCTOR8<200))
  {
    flag_miss =0;
    back_location[4]=-1000;
    out_all();
  }
  
  
  /***************左大弯中的特殊情况*********************/
  else if((INDUCTOR5>100&&INDUCTOR6>100&&INDUCTOR7<20&&INDUCTOR8<20)
          ||(INDUCTOR5>50&&INDUCTOR6>50&&INDUCTOR7<10&&INDUCTOR8<10)
            ||(INDUCTOR5>180&&INDUCTOR6>50&&INDUCTOR7<20&&INDUCTOR8<10)
              ||(INDUCTOR5<50&&INDUCTOR6<50&&INDUCTOR7<10&&INDUCTOR8<20&&INDUCTOR6>INDUCTOR7)
                ||(INDUCTOR5>300&&INDUCTOR5<550&&INDUCTOR6>25&&INDUCTOR6<60&&INDUCTOR7>10&&INDUCTOR7<30&&INDUCTOR8<20)
                  ||(INDUCTOR5>40&&INDUCTOR5<110&&INDUCTOR6>50&&INDUCTOR6<110&&INDUCTOR7<10&&INDUCTOR8<10)
                    ||(INDUCTOR5>90&&INDUCTOR5<200&&INDUCTOR6>50&&INDUCTOR6<150&&INDUCTOR7<20&&INDUCTOR8<25))
  {
    flag_miss =0;
    back_location[4]=1000;
  }
  else { back_location[4] = ( INDUCTOR5 - INDUCTOR8 )*1.5;light_all();}
//  /* else
//  {
//  //light_all();
//  if (INDUCTOR5 < 85 )
//  {
//  INDUCTOR5 = 0;
//  i ++;
//}
//  if (INDUCTOR6 < 85 )
//  {
//  INDUCTOR6 = 0;
//  i ++;
//}
//  if (INDUCTOR7 < 85 )
//  {
//  INDUCTOR7 = 0;
//  i ++;
//}
//  if (INDUCTOR8 < 85 )
//  {
//  INDUCTOR8 = 0;
//  i ++;
//}
//  switch ( i )
//  {
//case ( 0 ): j=0.7; //(252)
//  break;
//case ( 1 ): j=3;//(-37~~696)
//  break;
//case ( 2 ): 
//  { j = 5 ;//(170~~1688)
//  break; } 
//case ( 3 ): j=5;//(0~~1500)
//  break;
//  default   : j=1;
//}
//  back_location[4] = ( int32 )(( INDUCTOR5 - INDUCTOR8 + INDUCTOR6 - INDUCTOR7 ) * j );
//}*/
  /******************丢线***************************/
  if ( INDUCTOR5 < 30 && INDUCTOR6 < 30
      && INDUCTOR7 < 30 && INDUCTOR8 < 30 )
  {
    
    flag_miss++;
    if (flag_miss >= 50)
    {
      flag_backmiss = 1;
    }
  }
  else
  {
    flag_backmiss = 0;
  }
  
  
  if (back_location[4] > 1000)
  {back_location[4] = 1000;}
  if (back_location[4] < -1000)
  {back_location[4] = -1000;}
  
  back_location[0] = (int32) ( back_location[1] * 0.1
                              +back_location[2] *0.1 
                                +back_location[3] * 0.2
                                  +back_location[4] *0.6);
  back_location[1] = back_location[2];
  back_location[2] = back_location[3];
  back_location[3] = back_location[4];
}


void front_mode_detecter()//前电感位置判定
{
//  uint8 i = 0; //临时变量之后修改命名//丢线电感数
//  float j = 1;
  static int8 flag_miss =0;//丢线计数
  
  
  /*********直道及十字弯**************/
  if ( ( (INDUCTOR2 < 50 && INDUCTOR3 < 50 ) 
        && ( INDUCTOR1 >50 && INDUCTOR4 > 50 ) ) //1
      || (INDUCTOR2 < 50  && INDUCTOR3 < 50 && ((INDUCTOR1>200 && INDUCTOR4>10) || (INDUCTOR4>200&&INDUCTOR1>10))
          && (INDUCTOR1 - INDUCTOR4 < 80 || INDUCTOR4 - INDUCTOR1 < 80 ))//2
        || ( (INDUCTOR2 > 200 && INDUCTOR3 > 200 ) && (INDUCTOR1 >100)&&(INDUCTOR4 > 100) ) 
          /*|| ( INDUCTOR1 > 100  && INDUCTOR4 >100 )*/ 
          ||  ( INDUCTOR1 > 300 && INDUCTOR1 < 700 && INDUCTOR4 >60 && INDUCTOR2 < 250)//
            || ( INDUCTOR1 >60 && INDUCTOR4 > 300 && INDUCTOR4 <700 && INDUCTOR3 < 200))//
  {front_location[4] = ( INDUCTOR1 - INDUCTOR4 )/2;
  flag_miss = 0;
  last_front_location=front_location[4];
  //out_all();
  //light_all();
  }
  /*********左大弯*****************/
  else if ( ( INDUCTOR1 - INDUCTOR4 > 600 
             && INDUCTOR2 - INDUCTOR3 > 100)
           || (INDUCTOR1 - INDUCTOR4 > 500 && INDUCTOR2 - INDUCTOR3 > 200)
             )
  {
    front_location[4] = (int32) ( (INDUCTOR1 + INDUCTOR2)/1.5 ) ;
    flag_miss = 0;
    last_front_location=front_location[4];
    //out_all();
    //light_all();
  }
  
  else if (( INDUCTOR1 > 300 && INDUCTOR3 < 20
            && INDUCTOR2 < 20
              && INDUCTOR4 < 10 )
           )
  {front_location[4] = 1500 -  INDUCTOR1 ;
  flag_miss = 0;
  last_front_location=front_location[4];
  //out_all();
  //light_all();
  }
  
  else if  (INDUCTOR1 - INDUCTOR4 > 600) 
  {
    front_location[4] =(int32) ( INDUCTOR1 * 0.7 );
    flag_miss = 0;
    last_front_location=front_location[4];
    //out_all();
    //light_all();
  }
  
  /*********右大弯****************/
  else if ( ( INDUCTOR4 - INDUCTOR1 > 600 
             && INDUCTOR3 - INDUCTOR2 > 200)
           || (INDUCTOR4 - INDUCTOR1 > 500 && INDUCTOR3 - INDUCTOR2 > 200)
             )
  {front_location[4] =( int32 ) ( - (INDUCTOR3 + INDUCTOR4)/1.5 );
  //out_all();
  flag_miss = 0;
  //out_all();
  //light_all();
  last_front_location=front_location[4];
  }
  
  else if ( (INDUCTOR4 > 500 && INDUCTOR2 <20 
             && INDUCTOR3 <20     
               && INDUCTOR1 < 20) )                
  {
    front_location[4] = -1650 + INDUCTOR4 ;
    //light_all();
    flag_miss = 0;
    last_front_location=front_location[4];
    //out_all();
    //light_all();
  }
  
  else if ( INDUCTOR4 - INDUCTOR1 >600 )
  {
    front_location[4] =(int32)( -INDUCTOR4 * 0.7);
    flag_miss = 0;
    last_front_location=front_location[4];
    //out_all();
    //light_all();
  }
  //右直角
  else if ( ( INDUCTOR3 >500 && INDUCTOR2 <150 ) || (INDUCTOR2 <250 && INDUCTOR3 > 600 ) )
  {
    front_location[1] =
      front_location[2] = 
        front_location[3] =
          front_location[4] = -1000;
    speed_aim=0;
    //out_all();
    //light_all();
    last_front_location=front_location[4];
  }
  //左直角
  else if ( ( INDUCTOR2 >500 && INDUCTOR3 <150  )|| (INDUCTOR3 <250 && INDUCTOR2 > 600 )  )
  {
    front_location[1] =
      front_location[2] = 
        front_location[3] =
          front_location[4] = 1000;
    speed_aim=0;
    last_front_location=front_location[4];
    //out_all();
    //light_all();
  }
  else 
  {
    front_location[4]=last_front_location;
    //out_all();
    //light_all();
  }
  
//  /*else
//  {
//  //light_all();
//  if (INDUCTOR1 < 30 )
//  {
//  INDUCTOR1 = 0;
//  i ++;
//  
//}
//  if (INDUCTOR2 < 30 )
//  {
//  INDUCTOR2 = 0;
//  i ++;
//}
//  if (INDUCTOR3 < 30 )
//  {
//  INDUCTOR3 = 0;
//  i ++;
//}
//  if (INDUCTOR4 < 30 )
//  {
//  INDUCTOR4 = 0;
//  i ++;
//}
//  switch ( i )
//  {
//case ( 0 ): j=0.7; //(252)
//  break;
//case ( 1 ): j=2.5;//(-37~~696)
//  break;
//case ( 2 ): 
//  { j = 3;//(170~~1688)
//  break; } 
//case ( 3 ): j=3.5;//(0~~1500)
//  break;
//  default   : j=1;
//}
//  front_location[4] = ( int32 )(( INDUCTOR1 - INDUCTOR4 + INDUCTOR2 - INDUCTOR3 ) * j );
//}
//  */
  
  
  
  if (front_location[4] > 1000 )
  { front_location[4] = 1000;}
  if ( front_location[4] < -1000 )
  {front_location[4] = -1000;}
  
  
  
  front_location[0] = (int32) ( front_location[1] * 0.2
                               +front_location[2] *0.2 
                                 +front_location[3] * 0.3
                                   +front_location[4] *0.3 );
  front_location[1] = front_location[2];
  front_location[2] = front_location[3];
  front_location[3] = front_location[4];
  
}


void detecter()
{
  front_INDUCTOR_a=INDUCTOR1+INDUCTOR4;
  //front_mode_detecter();
  back_mode_detecter();
  if(front_INDUCTOR_a<200)
  {this_location=back_location[4]*1.1;}
  else
  {this_location=back_location[4];}
  
  if (this_location > 1000)
  {this_location = 1000;}
  if (this_location < -1000)
  {this_location = -1000;}
#if 1
  if (this_location <= 0)
  {
    speed_aim =(uint32) (( SPEED_MAX -SPEED_MIN ) / 1000 * this_location +SPEED_MAX * 0.5);
  }
  else
  {
    speed_aim = (uint32) ( ( SPEED_MIN -SPEED_MAX ) / 1000 * this_location +SPEED_MAX *0.5);
  }
#else
  if ( (this_location <= 1000 && this_location >=800)
     ||  (this_location >= -1000 && this_location <= -800)  )
  {
    speed_aim = SPEED_MID - 300;
  }
  else if ( (this_location < 800 && this_location >=600) 
     || (this_location >= -800 && this_location <= -600) )
  {
    speed_aim = SPEED_MID - 100;
  }
  else if ( (this_location < 600 && this_location >= 400) 
     || (this_location >= -600 && this_location <= -400) )
  {
    speed_aim = SPEED_MID - 50;
  }
  else if ( (this_location < 400 && this_location >= 100) 
     || (this_location >= -400 && this_location <= -100) )
  {
    speed_aim = SPEED_MID ;
  }  
  else if ( this_location < 100 && this_location > -100)
  {
    speed_aim = SPEED_MID +300;
  }
#endif 
  
  push(0,front_INDUCTOR_a);//ind1
  //push(1,INDUCTOR2);//ind2
  //push(2,INDUCTOR3);//ind3
  //push(3,INDUCTOR4);//ind4
  
//  push(4,INDUCTOR5);
//  push(5,INDUCTOR6);
//  push(6,INDUCTOR7);
//  push(7,INDUCTOR8);
//  push(10,this_location);
  
  //push(11,angle);
  //push(12,result);//代码在servo.c
  //push(13,speed_aim);
  //push(14,i_sum);
  //push(15,front_location[0]);
  push(16,back_location[0]);
  
}

