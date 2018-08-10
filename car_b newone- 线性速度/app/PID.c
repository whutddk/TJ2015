/*****PID算法C文件
***李锐戈
******最后修改2015 1 24
********
****
*/

#include "common.h"
#include "include.h"


/******************舵机控制部分************************/
/********500**********750**********1000**************/

/*********-50************0***********50**********/
#if 1                   
//位置ID控制算法

PID_REF Kp_1 = 6;          //比例
PID_REF Ki_1 = 0.0;          //积分
PID_REF Kd_1 = 0.05;          //微分
PID_REF Td_1 = 0.3;         //时间

PID_ERR PidError_1[2]={0,0};       //差值
uint8  PID_count_1 = 0;        //小心溢出
PID_ERR PID_ErrSum_1 = 0;       //积分和

//
//
//

PID_OUT UpdataPID_OUT_1(PID_SET set, PID_OUT yout)
{
  PID_OUT out = 0;
  PID_OUT reduce = 0;
  
  if (PID_count_1 > 1)
  {
  
 
    PidError_1[1] = set - yout;             //差值项
    PID_ErrSum_1 += PidError_1[1] * Td_1 * Ki_1;  //积分项
  
    if(PID_ErrSum_1 >= 250)
    {
      PID_ErrSum_1 =250;
    }
    if (PID_ErrSum_1 <= -250)
    {     
      PID_ErrSum_1 = -250;
    }
  
  
    out = (PID_OUT) ( PidError_1[1] * PidError_1[1] / 1500 );       //加比例项
    
    if (PidError_1[1] < 0)
    {
      out = 0- out;
    }
    out += PID_ErrSum_1;                    //加积分项
  
    reduce = ( PID_OUT )( Kd_1 * ( PidError_1[1] - PidError_1[0] ) / Td_1 );      //求微分项
    out += reduce;                        //加微分项
  
    if( out >=250 )
    {
      out =250;
    }
    if ( out <= -250 )
    {
      out = -250;
    }
    PidError_1[0] = PidError_1[1];            //差值保存
    return ( out );                       //返回PID结果
   }
 
    else
  {
    PID_count_1 ++;                         //第N次PID
    return 0;
   }
}

#endif

#if 1

//增量式PID控制

PID_REF Kp_2 =1.1;          //已经整定完毕
PID_REF Ki_2 = 2.1;          //
PID_REF Kd_2 =0.003;          //
PID_REF Td_2 = 0.06;         //

PID_ERR PidError[3] = {0x0,0x0,0x0};       //
//PID_OUT PidOut;            //

PID_OUT UpdatePID_Out_2(PID_SET set,PID_OUT yout)
{
  PID_OUT out;
  PidError[2] = set - yout;
  
  out = (int32 )(Kp_2 * ( PidError[2] - PidError[1] ) );
  out += Ki_2 * PidError[2] * Td_2;
  out += Kd_2 * ( PidError[2] -2 *PidError[1] +PidError[0] ) / Td_2;
  
  PidError[0] = PidError[1];
  PidError[1] = PidError[2];
  return out;
}
#endif 


#if 0
//积分分离PID控制

PID_REF Kp = 0.1;          //
PID_REF Ki = 0.1;          //
PID_REF Kd = 0.1;          //
PID_REF Td = 0.01;         //

PID_ERR PidError[2];       //
long PID_Count = 0;        //
long PID_ErrSum = 0;       //
long PID_MinErr = 0x100;   //阈值

ID_OUT UpdatePID_Out(PID_SET set ,PID_OUT yout)
{
  PID_OUT out;
  PID_OUT reduce;
  
  if(PID_Count <= 1)
  {
    return 0;
  }
  
  PidError[1] = set - yout;
  if (PidError < PID_MinErr)
  {
    PidError[0] < PidError[1];
    out = 0;
    return out;
    
  }
  PID_ErrSum +=PidError[1] * Ts * Ki;
  
  out = Kp * PidError[1];
  out += PID_ErrSum;
  
  reduce = Kd * (PidError[1] - PidError[0]) / Ts;
  out += reduce;
  
  PID_Count ++;
  PidError[0] = PidError[1];
  return (out);
}

#endif

#if 0

//抗积分饱和PID控制
PID_REF Kp = 0.1;          //
PID_REF Ki = 0.1;          //
PID_REF Kd = 0.1;          //
PID_REF Td = 0.01;         //

PID_ERR PidError[2];       //
long PID_Count = 0;        //
long PID_ErrSum = 0;       //
long PID_MaxOut = 0x100;   //阈值

PID_OUT UpdataPID_Out(PID_SET set,PID_OUT yout)
{
  PID_OUT out;
  PID_OUT reduce;
  
  if ( PID_Count <= 1)
  {
    return 0;
  }
  
  PidError[1] = set - yout;
  PID_ErrSum += PidError[1] * Ts * Ki;
  
  out = Kp * PidError[1];
  out += PID_ErrSum;
  
  reduce =Kd * ( PidError[1] - PidError[0] ) / Ts;
  PID_Count ++;
  PidError[0] = PidError[1];
  
  out > PID_Maxout ? PID_MaxOut : out;      //上限设置，判断上次输出值，
                                            //决定是否更新输出
  //如果（k-1）>Max，增加负的error，反之，增加正的error
  return (out);
}

#endif

#if 0
//梯度积分PID控制算法

PID_REF Kp = 0.1;          //
PID_REF Ki = 0.1;          //
PID_REF Kd = 0.1;          //
PID_REF Td = 0.01;         //

PID_ERR PidError[2];       //
long PID_Count = 0;
long PID_ErrSum = 0;

//
//
//

PID_OUT UpdatePID_OUT(PID_SET set , PID_OUT yout)
{
  PID_OUT out;
  PID_OUT reduce;
  
  if (PID_Count <= 1)
  {
    return 0;
  }
  
  PidError[1] = set - yout;
  PID_ErrSum += ( PidError[1] + PidError[0] /2 * Ts * Ki); //梯度ID积分
  
  out = Kp *PidError[1];
  out += PID_ErrSum;
  
  reduce =Kd * (PidError)[1] - PidError[0]) / Ts;
  out += reduce ;
  
  PID_Count ++;
  PidError[0] = PidError[1];
  return (out);
  
}

#endif

#if 0
//带死区的PID控制

PID_REF Kp = 0.1;          //
PID_REF Ki = 0.1;          //
PID_REF Kd = 0.1;          //
PID_REF Td = 0.01;         //

PID_ERR PidError[2];       //
long PID_Count = 0;        //
long PID_Error = 0;        //

long PID_MinErr = 0x100;   //阈值

ID_OUT UpdatePID_Out(PID_SET set ,PID_OUT yout)
{
  PID_OUT out;
  PID_OUT reduce;
  
  if (PID_Count <= 1)
  {
    return 0;
    
  }
  
  PidError[1] = set -yout;
  PID_ErrSum += PidError[1] * Ts * Ki;
  
  out = Kp * PidError[1];
  
  if ( PidEror > PID _MinErr)
  {
    out +=PID_ErrSum;
  }
  
  reduce = Kd * ( PidError[1] - PidError[0]) / Ts;
  out += reduce;
  
  PID_Count ++;
  PidError[0] = PidError[1];
  return (out);
}


#endif