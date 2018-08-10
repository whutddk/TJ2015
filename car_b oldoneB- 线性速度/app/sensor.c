/***AD����ɼ�C�ļ�
**����� 2014 11 25
*2015 2 11����� ����ӳ�����
*/

#include "common.h"
#include "include.h"

/***�Ӵ������� 
B7        B6        B5        B4        B2        B3        B0       B1 

ADC1_SE13 ADC1_SE12 ADC1_SE11 ACD1_SE10 ADC0_SE12 ADC0_SE13 ADC0_SE8 ADC0_SE9
AD13      AD12      AD11      AD10           AD12      AD13      AD8      AD9

������ ������       ������     ������       ǰ����    ǰ����   ǰ����   ǰ����
*/



int16 AD[8]={0};    //������ת�������һ��,Ϊ���⸡�����㣬*100

void sensors_init()
{
  //������ADC
  ADC_Init_solf(ADC0,SE_12BIT);
  ADC_Init_solf(ADC1,SE_12BIT);
  
  //ͨ��ʹ�ܣ����ùܽţ�
  LPLD_ADC_Chn_Enable(ADC0, AD8);//B0 ����
  LPLD_ADC_Chn_Enable(ADC0, AD9);//B1 ����
  LPLD_ADC_Chn_Enable(ADC0, AD12);//B2 ����
  LPLD_ADC_Chn_Enable(ADC0, AD13);//B3  //ǰ���������
  
  LPLD_ADC_Chn_Enable(ADC1, AD10);//B4
  LPLD_ADC_Chn_Enable(ADC1, AD11);//B5
  LPLD_ADC_Chn_Enable(ADC1, AD12);//B6
  LPLD_ADC_Chn_Enable(ADC1, AD13);//B7  //�󷽵��
  //
}

void Get_AD_data(void) //��ȡ���ֵ����һ����100��
{ 
  
  int i=0,j=0,k=0;
  uint16 AD_temp=0;
  uint32 AD_sum[8];//��������ƽ���õ���ʱ����
  uint16 AD_data[8][DET_NUM];//ÿ��ͨ������ȡN��ֵ�Ĵ��λ��
  uint16 AD_average[8];//�ĸ��������˲����ֵ
  
  
  
  for(j=0;j<DET_NUM;j++)
  {
    AD_data[0][j]=LPLD_ADC_Get(ADC0, AD8);//ǰ����
    AD_data[1][j]=LPLD_ADC_Get(ADC0, AD9);//ǰ����
    AD_data[2][j]=LPLD_ADC_Get(ADC0, AD12);//ǰ����
    AD_data[3][j]=LPLD_ADC_Get(ADC0, AD13);//ǰ����
    
    AD_data[4][j]=LPLD_ADC_Get(ADC1, AD10);// ������
    AD_data[5][j]=LPLD_ADC_Get(ADC1, AD11);//������
    AD_data[6][j]=LPLD_ADC_Get(ADC1, AD13); //������
    AD_data[7][j]=LPLD_ADC_Get(ADC1, AD12);//������
  }
  
  
  
  
  /******�ȽϷ�*********/
  for(i=0;i<8;i++)                   //4�����     
  {
    for(j=0;j<DET_NUM-1;j++)                //N�����ݡ�ѡ������
    {
      for(k=j+1;k<DET_NUM;k++)
      {
        if(AD_data[i][j] > AD_data[i][k])  //ǰ��ıȺ���Ĵ�  ����н���
        {
          AD_temp = AD_data[i][j];
          
          AD_data[i][j] = AD_data[i][k];
          
          AD_data[i][k] = AD_temp;
        }
      }
    }
  }
  /*****ȥ�����ֵ��Сֵ,��ƽ��ֵ********/
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
  
  //�ȶ��㷨��ͨ��֮ǰ��һ����ֵ
  //�ܹ���Ӧ��ͬ�����ĵ�Դ
  for(i=0;i<8;i++)
  {    
    AD[i]=(AD_average[i]-min_AD[i])*1000/(max_AD[i]-min_AD[i]);
    
    AD[i]=AD[i]>1000?1000:AD[i];       
    AD[i]=AD[i]<0?0:AD[i]; 
  } 
  
  
  /****************����AD_average***************************/
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




