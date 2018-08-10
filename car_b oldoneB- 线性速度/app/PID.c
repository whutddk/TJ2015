/*****PID�㷨C�ļ�
***�����
******����޸�2015 1 24
********
****
*/

#include "common.h"
#include "include.h"


/******************������Ʋ���************************/
/********500**********750**********1000**************/

/*********-50************0***********50**********/
#if 1                   
//λ��ID�����㷨

PID_REF Kp_1 = 6;          //����
PID_REF Ki_1 = 0.0;          //����
PID_REF Kd_1 = 0.05;          //΢��
PID_REF Td_1 = 0.3;         //ʱ��

PID_ERR PidError_1[2]={0,0};       //��ֵ
uint8  PID_count_1 = 0;        //С�����
PID_ERR PID_ErrSum_1 = 0;       //���ֺ�

//
//
//

PID_OUT UpdataPID_OUT_1(PID_SET set, PID_OUT yout)
{
  PID_OUT out = 0;
  PID_OUT reduce = 0;
  
  if (PID_count_1 > 1)
  {
  
 
    PidError_1[1] = set - yout;             //��ֵ��
    PID_ErrSum_1 += PidError_1[1] * Td_1 * Ki_1;  //������
  
    if(PID_ErrSum_1 >= 250)
    {
      PID_ErrSum_1 =250;
    }
    if (PID_ErrSum_1 <= -250)
    {     
      PID_ErrSum_1 = -250;
    }
  
  
    out = (PID_OUT) ( PidError_1[1] * PidError_1[1] / 1500 );       //�ӱ�����
    
    if (PidError_1[1] < 0)
    {
      out = 0- out;
    }
    out += PID_ErrSum_1;                    //�ӻ�����
  
    reduce = ( PID_OUT )( Kd_1 * ( PidError_1[1] - PidError_1[0] ) / Td_1 );      //��΢����
    out += reduce;                        //��΢����
  
    if( out >=250 )
    {
      out =250;
    }
    if ( out <= -250 )
    {
      out = -250;
    }
    PidError_1[0] = PidError_1[1];            //��ֵ����
    return ( out );                       //����PID���
   }
 
    else
  {
    PID_count_1 ++;                         //��N��PID
    return 0;
   }
}

#endif

#if 1

//����ʽPID����

PID_REF Kp_2 =1.1;          //�Ѿ��������
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
//���ַ���PID����

PID_REF Kp = 0.1;          //
PID_REF Ki = 0.1;          //
PID_REF Kd = 0.1;          //
PID_REF Td = 0.01;         //

PID_ERR PidError[2];       //
long PID_Count = 0;        //
long PID_ErrSum = 0;       //
long PID_MinErr = 0x100;   //��ֵ

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

//�����ֱ���PID����
PID_REF Kp = 0.1;          //
PID_REF Ki = 0.1;          //
PID_REF Kd = 0.1;          //
PID_REF Td = 0.01;         //

PID_ERR PidError[2];       //
long PID_Count = 0;        //
long PID_ErrSum = 0;       //
long PID_MaxOut = 0x100;   //��ֵ

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
  
  out > PID_Maxout ? PID_MaxOut : out;      //�������ã��ж��ϴ����ֵ��
                                            //�����Ƿ�������
  //�����k-1��>Max�����Ӹ���error����֮����������error
  return (out);
}

#endif

#if 0
//�ݶȻ���PID�����㷨

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
  PID_ErrSum += ( PidError[1] + PidError[0] /2 * Ts * Ki); //�ݶ�ID����
  
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
//��������PID����

PID_REF Kp = 0.1;          //
PID_REF Ki = 0.1;          //
PID_REF Kd = 0.1;          //
PID_REF Td = 0.01;         //

PID_ERR PidError[2];       //
long PID_Count = 0;        //
long PID_Error = 0;        //

long PID_MinErr = 0x100;   //��ֵ

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