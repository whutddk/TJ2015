/***
***FTM模块中层库
李锐戈
2014 11 22

***
*/

#include "common.h"
#include "include.h"



void PWM0_init()                 //FTM0通道多，8通，用于控制PWM
{ 
  FTM_InitTypeDef ftm_init_struct;
  ftm_init_struct.FTM_Ftmx = FTM0;	//使能FTM0通道
  ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	//使能PWM模式
  ftm_init_struct.FTM_PwmFreq = 1000;	//PWM频率10000Hz
  ftm_init_struct.FTM_PwmDeadtimeCfg = DEADTIME_CH23;
  ftm_init_struct.FTM_PwmDeadtimeVal=0;
  LPLD_FTM_Init(ftm_init_struct);
  
    LPLD_FTM_PWM_Enable(FTM0, //使用FTM0
                      FTM_Ch0, //使能Ch0通道
                      10, //初始化角度0度
                      PTC1, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      );    
    LPLD_FTM_PWM_Enable(FTM0, //使用FTM0
                      FTM_Ch1, //使能Ch0通道
                      10, //初始化角度0度
                      PTC2, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //使用FTM0
                      FTM_Ch2, //使能Ch0通道
                      10, //初始化角度0度
                      PTC3, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //使用FTM0
                      FTM_Ch3, //使能Ch0通道
                      10, //初始化角度0度
                      PTC4, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //使用FTM0
                      FTM_Ch4, //使能Ch0通道
                      10, //初始化角度0度
                      PTD4, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //使用FTM0
                      FTM_Ch5, //使能Ch0通道
                      10, //初始化角度0度
                      PTD5, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //使用FTM0
                      FTM_Ch6, //使能Ch0通道
                      10, //初始化角度0度
                      PTD6, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      ); 
    LPLD_FTM_PWM_Enable(FTM0, //使用FTM0
                      FTM_Ch7, //使能Ch0通道
                      10, //初始化角度0度
                      PTD7, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      ); 
}/*方PWM输出*/

/*
void ic_init(void)
{
  FTM_InitTypeDef ftm_init_struct;
  //配置FTM1模块的输入捕获参数
  ftm_init_struct.FTM_Ftmx = FTM2;      //使能FTM1通道
  ftm_init_struct.FTM_Mode = FTM_MODE_IC;       //使能输入捕获模式
  ftm_init_struct.FTM_ClkDiv = FTM_CLK_DIV128;  //计数器频率为总线时钟的128分频
  ftm_init_struct.FTM_Isr = ic_isr;     //设置中断函数
  //初始化FTM1
  LPLD_FTM_Init(ftm_init_struct);
  //使能输入捕获对应通道,上升沿捕获进入中断
  LPLD_FTM_IC_Enable(FTM1, FTM_Ch0, PTB18, CAPTURE_RI);//上升沿捕获
  
  //使能FTM0中断
  LPLD_FTM_EnableIrq(ftm_init_struct);
}
*/
void PWM1_init()                 //FTM1通道，2通，用于控制PWM
{ 
  FTM_InitTypeDef ftm_init_struct;
  ftm_init_struct.FTM_Ftmx = FTM1;	//使能FTM0通道
  ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	//使能PWM模式
  ftm_init_struct.FTM_PwmFreq = 50;	//PWM频率50hz
  ftm_init_struct.FTM_PwmDeadtimeCfg = DEADTIME_CH01;
  ftm_init_struct.FTM_PwmDeadtimeVal=0;
  LPLD_FTM_Init(ftm_init_struct);
  
  LPLD_FTM_PWM_Enable(FTM1, //使用FTM0
                      FTM_Ch0, //使能Ch0通道
                      750, //占空比
                      PTA8, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      );    
    LPLD_FTM_PWM_Enable(FTM1, //使用FTM0
                      FTM_Ch1, //使能Ch0通道
                      750, //占空比
                      PTA9, //使用Ch0通道的PTC1引脚
                      ALIGN_LEFT        //脉宽左对齐
                      ); 

}
/*
*捕捉计数器中断
*/
/*
uint32 Freq;//频率测量，或许没用，中断不懂：如何触发，如何计数
 void ic_isr(void)
  {
    uint32 cnt;
  //判断是否为FTM1的Ch0通道产生捕获中断
  if(LPLD_FTM_IsCHnF(FTM1, FTM_Ch0))
  {
    //获取FTM1的Ch0通道计数值
    cnt=LPLD_FTM_GetChVal(FTM1, FTM_Ch0);   
    
    //根据总线频率、分频系数、计数值计算脉冲频率
    //脉冲频率=(总线频率/输入捕获分频)/计数值
    Freq=(g_bus_clock/LPLD_FTM_GetClkDiv(FTM1))/cnt; 
    
    //清空FTM1 COUNTER
    LPLD_FTM_ClearCounter(FTM1);
    //清除输入中断标志
    LPLD_FTM_ClearCHnF(FTM1, FTM_Ch0); 
  }
}
*/  