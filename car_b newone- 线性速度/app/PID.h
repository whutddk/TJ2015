/*************
***PID算法控制H文件
*********李锐戈
****最后修改2014 12 1
**
*/

#ifndef _PID_H_
#define _PID_H_


typedef int32 PID_OUT;
typedef int32 PID_SET;
typedef int32 PID_Feed;
typedef float PID_REF;
typedef int32 PID_ERR;

extern PID_REF Kp_1;          //
extern PID_REF Ki_1;          //
extern PID_REF Kd_1;          //
extern PID_REF Td_1;         //

extern PID_ERR PidError_1[2];       //
extern uint8 PID_count_1;        //小心溢出
extern PID_ERR PID_ErrSum_1;       //

extern PID_REF Kp_2 ;          //
extern PID_REF Ki_2 ;          //
extern PID_REF Kd_2 ;          //
extern PID_REF Td_2 ;         //




PID_OUT UpdataPID_OUT_1(PID_SET set, PID_OUT yout);
PID_OUT UpdatePID_Out_2(PID_SET set, PID_OUT yout);

#endif