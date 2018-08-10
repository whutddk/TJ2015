/****calibration.c
***用于电感归一化标定
***其头文件统一于detecter_all.h
***
***李锐戈2015 1 10 创建
李锐戈 2015 1 27
***
*/

#include "common.h"
#include "include.h"


//代入测试静态数据，方便调试
uint16 max_AD[8]={880,420,600,787,1473,1496,1574,1935}; //INDUCTOR8   INDUCTOR INDUCTOR INDUCTOR  INDUCTOR7  INDUCTOR   INDUCTOR6   INDUCTOR5   
uint16 min_AD[8]={0,0,0,0,0,0,0,0};//存放最小值

/****************************************/
//函 数：ScanNorma(void)
//功 能：动态获取最值
//说 明：扫面最大最小值并存储于max_AD[] min_AD[]
//在1分钟调试阶段调用，需要人机交互调用
//注意，必须有强制跳过代码，必须有重试代码
/****************************************/
void ScanNorma(uint16 times)
{
    uint16 i,j;
    uint16 AD_valu[8];
   
    for(i=0;i<times;i++) //1200待定
    {
       AD_valu[0] = LPLD_ADC_Get(ADC0, AD8);  //B0 通道      //前方电感
       AD_valu[1] = LPLD_ADC_Get(ADC0, AD9);  //B1 通道     
       AD_valu[2] = LPLD_ADC_Get(ADC0, AD12);  //B2 通道     
       AD_valu[3] = LPLD_ADC_Get(ADC0, AD13);  //B3 通道 
       
       AD_valu[4] = LPLD_ADC_Get(ADC1, AD10);  //B4 通道      //后方电感
       AD_valu[5] = LPLD_ADC_Get(ADC1, AD11);  //B5 通道     
       AD_valu[6] = LPLD_ADC_Get(ADC1, AD13);  //B6 通道     
       AD_valu[7] = LPLD_ADC_Get(ADC1, AD12);  //B7 通道 
       
       
       for(j=0;j<8;j++) 
       {    
           if(AD_valu[j] >= max_AD[j])  
             max_AD[j] = AD_valu[j];
          
           if( AD_valu[j] <= min_AD[j] )
             min_AD[j] = AD_valu[j];
       }
    }  

}