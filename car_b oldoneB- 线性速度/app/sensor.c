/***AD软件采集C文件
**李锐戈 2014 11 25
*2015 2 11李锐戈 重新映射后电感
*/

#include "common.h"
#include "include.h"

/***从从左往右 
B7        B6        B5        B4        B2        B3        B0       B1 

ADC1_SE13 ADC1_SE12 ADC1_SE11 ACD1_SE10 ADC0_SE12 ADC0_SE13 ADC0_SE8 ADC0_SE9
AD13      AD12      AD11      AD10           AD12      AD13      AD8      AD9

后左内 后左外       后右外     后右内       前左外    前左内   前右内   前右外
*/



int16 AD[8]={0};    //传感器转换结果归一化,为避免浮点运算，*100

void sensors_init()
{
  //打开两个ADC
  ADC_Init_solf(ADC0,SE_12BIT);
  ADC_Init_solf(ADC1,SE_12BIT);
  
  //通道使能（设置管脚）
  LPLD_ADC_Chn_Enable(ADC0, AD8);//B0 右外
  LPLD_ADC_Chn_Enable(ADC0, AD9);//B1 右内
  LPLD_ADC_Chn_Enable(ADC0, AD12);//B2 左内
  LPLD_ADC_Chn_Enable(ADC0, AD13);//B3  //前方电感左外
  
  LPLD_ADC_Chn_Enable(ADC1, AD10);//B4
  LPLD_ADC_Chn_Enable(ADC1, AD11);//B5
  LPLD_ADC_Chn_Enable(ADC1, AD12);//B6
  LPLD_ADC_Chn_Enable(ADC1, AD13);//B7  //后方电感
  //
}

void Get_AD_data(void) //获取电感值并归一化（100）
{ 
  
  int i=0,j=0,k=0;
  uint16 AD_temp=0;
  uint32 AD_sum[8];//交换，求平均用的临时变量
  uint16 AD_data[8][DET_NUM];//每个通道采样取N个值的存放位置
  uint16 AD_average[8];//四个传感器滤波后的值
  
  
  
  for(j=0;j<DET_NUM;j++)
  {
    AD_data[0][j]=LPLD_ADC_Get(ADC0, AD8);//前右外
    AD_data[1][j]=LPLD_ADC_Get(ADC0, AD9);//前右内
    AD_data[2][j]=LPLD_ADC_Get(ADC0, AD12);//前左内
    AD_data[3][j]=LPLD_ADC_Get(ADC0, AD13);//前左外
    
    AD_data[4][j]=LPLD_ADC_Get(ADC1, AD10);// 后右内
    AD_data[5][j]=LPLD_ADC_Get(ADC1, AD11);//后右外
    AD_data[6][j]=LPLD_ADC_Get(ADC1, AD13); //后左内
    AD_data[7][j]=LPLD_ADC_Get(ADC1, AD12);//后左外
  }
  
  
  
  
  /******比较法*********/
  for(i=0;i<8;i++)                   //4个电感     
  {
    for(j=0;j<DET_NUM-1;j++)                //N个数据“选择排序”
    {
      for(k=j+1;k<DET_NUM;k++)
      {
        if(AD_data[i][j] > AD_data[i][k])  //前面的比后面的大  则进行交换
        {
          AD_temp = AD_data[i][j];
          
          AD_data[i][j] = AD_data[i][k];
          
          AD_data[i][k] = AD_temp;
        }
      }
    }
  }
  /*****去掉最大值最小值,求平均值********/
  for(i=0; i<8; i++)
  {
    AD_sum[i] = 0;
    for(j=1;j<DET_NUM-1;j++)
    {
      AD_sum[i] += AD_data[i][j];
    }
    
  }
  AD_average[0] = AD_sum[0]/(DET_NUM-2);
  AD_average[1] = AD_sum[1]/(DET_NUM-2);
  AD_average[2] = AD_sum[2]/(DET_NUM-2);
  AD_average[3] = AD_sum[3]/(DET_NUM-2);
  AD_average[4] = AD_sum[4]/(DET_NUM-2);
  AD_average[5] = AD_sum[5]/(DET_NUM-2);
  AD_average[6] = AD_sum[6]/(DET_NUM-2);
  AD_average[7] = AD_sum[7]/(DET_NUM-2);
  
  //稳定算法，通过之前归一化的值
  //能够适应不同质量的电源
  for(i=0;i<8;i++)
  {    
    AD[i]=(AD_average[i]-min_AD[i])*1000/(max_AD[i]-min_AD[i]);
    
    AD[i]=AD[i]>1000?1000:AD[i];       
    AD[i]=AD[i]<0?0:AD[i]; 
  } 
  
  
  /****************发送AD_average***************************/
  //push(0,AD_average[3]);
  //push(1,AD_average[2]);
  //push(2,AD_average[1]);
  //push(3,AD_average[0]);
  //push(0,max_AD[3]);
  //push(1,max_AD[2]);//right
  //push(2,max_AD[1]);//left
  //push(3,max_AD[0]);
  //push(4,min_AD[4]);
  //push(5,min_AD[5]);//right
  //push(6,min_AD[6]);//left
  //push(7,min_AD[7]);
  
}




