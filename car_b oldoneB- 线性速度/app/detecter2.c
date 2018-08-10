/*
**第二套寻线算法
差值/最大差
***李广鹏2014 11 28

李锐戈2015 2 4 
改变了位置测试方案，采用电容思想，
基本不允许thislocation跳变
在某些需要模式识别的区域强制跳变
通过改变3值的权重改变thislocation的变化灵敏度

****
***********
*/

#include "common.h"
#include "include.h"

int32 location[3] = {0,0,0};//有符号
int32 this_location = 0;


int8 flag_cross = 0;//特殊弯方向判定位0 -1 1
int8 flag_curve = 0;//入弯标志位，为了减速,选择后电感
int8 flag_miss =0;//丢线计数 
int8 flag_changeback = 0 ;//后电感回切前电感的标志位，


/**********************模式识别综述*************************************
1、正常模式：
2、十字交叉：特征 外电感正常，内电感增大。处理：不做处理
  直角弯：特征 外电感从正常到无，内电感一个增大，一个较小，处理：选择后电感，向内电感较大方向做转弯准备
3、后电感开启状态，内外之差求平均处理
4、出弯判定： 特征 当前在后电感，外电感正常且对称，内电感很小， 处理：转前电感
5、丢线 ：特征 四个电感值很小 处理：前电感 转后电感，后电感，计数后停车报警
6、其他情况 ：均值处理
***********************************************************************/
/*********************标志位类型*************************************
flag_cross ：取值-1 0 +1 10分别代表左直角准备，直行（不处理或舵机打角限制处理），右直角准备，已经通过弯道
flag_curve ：入弯标志位，取值0 1 复位为正常 ，选择前电感，电机高速，置位为入弯，选择后电感，电机低速
flag_miss : 丢线计数，当处于后电感时丢线则++，达到阈值则停车，当其余任意模式识别成功时复位，
**********************************************************************/
/*********************阈值宏定义表*************************************
LINE_ABOVE ：处于线上方阈值
LINE_MISS ：丢线阈值
LINE_MID ：线在赛道正中阈值
INDUCTOR1 :左外电感
INDUCTOR2 ：左内电感
INDUCTOR3 ：右内电感
INDUCTOR4 ：右外电感

*****/
void mode_detect2()//一个标志位，flag_cross 0正常判定，-1左转，1右转
{ 
  out_all();//关所有灯
  LED6(flag_curve);
  
  if (flag_curve == 0 && flag_changeback ==1)//处在回切状态
  {
    common_situtation();
    if (location[2] - location[1] >= 50 || location[2] - location[1] <= -50)
    {
      flag_curve = 1 ;//回切无效，损失一次赛道判定
      flag_changeback =0;////回切无效，损失一次赛道判定
      location[2] = location[1];//本次判定无数据
    }
  }
  
  
  /*********正常模式前电感*******************************************************/
  /*********外电感未丢线，内电感不在线上 ，入弯标志位复位**********************************
  if (  (flag_curve == 0 ) && ( INDUCTOR1 > LINE_MISS ) 
      && ( INDUCTOR4 > LINE_MISS ) && ( INDUCTOR2 < LINE_ABOVE )
      && ( INDUCTOR3 < LINE_ABOVE ) )
  {
    LED1(ON);//开灯1
    flag_miss = 0;
    this_location =  (INDUCTOR1 - INDUCTOR4 ) / 2;
    
  }*/
  

   /*************入大弯判定********************************************/
  /*******内电感差值大于阈值，一个外电感丢线*****************************
  else if ( ((INDUCTOR1 < LINE_MISS )|| ( INDUCTOR4 <LINE_MISS ) ) 
           && ( ( ( INDUCTOR2 - INDUCTOR3 > DEFFER ) && ( INDUCTOR2 > INDUCTOR3 ) )|| ( ( INDUCTOR3 - INDUCTOR2 > DEFFER ) && ( INDUCTOR2 < INDUCTOR3 ) ) ) )
  {
    LED3(ON);
    flag_miss = 0;  
    flag_curve = 1;
    common_situtation();
    location[2] += ( (INDUCTOR2 - INDUCTOR3) ? 500 : -500 );
  }*/
  
   /*************十字交叉*************************************************/
  /*******外电感不丢线，两内电感在中线范围***********************************************/
  else if (  ( INDUCTOR1 > LINE_MISS ) && ( INDUCTOR4  >  LINE_MISS  )  && ( INDUCTOR2  > LINE_MID ) && ( INDUCTOR3 > LINE_MID ) )
  {
    LED1(ON);
    flag_miss = 0;
    flag_cross = 0 ;
    location[2] = ( INDUCTOR1 - INDUCTOR4 ) ;
    /*if ( this_location > 150 )
      this_location =  150;
    if ( this_location < -150 )
      this_location = -150;
    */  
    location[0] = 0;
    location[1] = 0;//迟缓滤波，限制打角
  }
  /*************直角弯*************************************************/
  /********外电感丢线，内电感其中一个在线上****************************/
    else if ( ( INDUCTOR1 < LINE_MISS ) && ( INDUCTOR4 < LINE_MISS ) 
             && ( ( INDUCTOR2 > LINE_MID ) || ( INDUCTOR3 > LINE_MID ) ))
    {
      flag_miss = 0;
      if ( flag_curve == 1 ) //后电感已经打开，需要急转
      {
        /*this_location =( ( INDUCTOR2 < INDUCTOR3 ) ? 500 : -500 );
        BEEP1(ON);
        delay(60000);
        BEEP1(OFF);
        */
        location[0]=
          location[1]=
            location[2]=
              ( ( INDUCTOR2 < INDUCTOR3 ) ? -1000 : 1000 );
        LED7(ON);
      }
      else //后电感未开启
      {
        flag_curve = 1;
        flag_cross = ( ( INDUCTOR2 < INDUCTOR3 ) ? -1 : 1 );
      }
    }
  
  /*****************完全丢线判定************************
  else if ( ( INDUCTOR1 < LINE_MISS ) && ( INDUCTOR2 < LINE_MISS ) && ( INDUCTOR3 < LINE_MISS ) && ( INDUCTOR4 < LINE_MISS ))
  {
    light_all();
    if ( flag_curve == 0 )
    {
      flag_curve = 1;
      location[2] = location[1];
      flag_miss ++;
    }
      /*************后电感模式********************************************/
  /*******外电感不丢线，两内电感在线上******************************
    else if ( (flag_curve == 1 ) )
    {
      if ( (flag_miss == 1 ) &&  (INDUCTOR2 < LINE_MISS ) && ( INDUCTOR3 < LINE_MISS ) && ( INDUCTOR1 > LINE_MID && INDUCTOR4 > LINE_MID) )//内电感同时不对中则出弯
      {
        flag_curve = 0 ;
        flag_changeback = 1;
        common_situtation();
      }
      else // ( (INDUCTOR2 > LINE_MISS )\\ ( INDUCTOR3 > LINE_MISS ) )
      {
        common_situtation();
      }  
    }
    else 
    {
      flag_miss ++;
      location[2] = location[1];
      if (flag_miss == 10)
      {
        flag_stop = 1; 
        LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10);//停车！
        LED8(ON);
      }
    }
  }*/
  else//完全未知情况
  {
    common_situtation();
  }

    
    
}

void detect2()
{
  mode_detect2();
  
/**************通过调整权重来改变灵敏度**********************/
  
 this_location = (int32)(location [0] * 0.3//【0】已经平滑化处理值及权重
               + location [1] * 0.3 //【1】已经平滑化处理值及权重
               + location [2] * 0.4);//【2】当前AD差值，加入参与平滑化
 
 /*****************************************/
 if ( this_location >= 1000 )
   this_location = 1000;
 if ( this_location <= -1000 )
   this_location = -1000;
 /******************************************/
 location [0] = location[1];
 location [1] = this_location;

}

void common_situtation()
{
    uint8 i = 0; //临时变量之后修改命名
    float j = 1;
  
  LED2(ON);
  flag_miss = 0; 
    if (INDUCTOR1 > LINE_MISS )
      i ++;
    if (INDUCTOR2 > LINE_MISS )
      i ++;
    if (INDUCTOR3 > LINE_MISS )
      i ++;
    if (INDUCTOR4 > LINE_MISS )
      i ++;
    switch ( i )
    {
    case ( 4 ): j=0.6;Kd_1 = 0.02;break;
    case ( 3 ): j=0.7;Kd_1 = 0.02;break;
    case ( 2 ): 
      if ( ( INDUCTOR1 < LINE_MISS && INDUCTOR2 < LINE_MISS && INDUCTOR3 > LINE_MISS ) || ( INDUCTOR3 < LINE_MISS && INDUCTOR4 < LINE_MISS && INDUCTOR2 > LINE_MISS ))
      { j = 1.7 ;Kd_1 = 0.001;break; }
      else 
      { j=0.5;Kd_1 = 0.02; break; }
        
    case ( 1 ): j=2.5;Kd_1 = 0.; break;
    default   : j=1;
    }
    location[2] = ( int32 )(( INDUCTOR1 - INDUCTOR4 + INDUCTOR2 - INDUCTOR3 ) * j );
}