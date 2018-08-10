/****calibration.c
***���ڵ�й�һ���궨
***��ͷ�ļ�ͳһ��detecter_all.h
***
***�����2015 1 10 ����
����� 2015 1 27
***
*/

#include "common.h"
#include "include.h"


//������Ծ�̬���ݣ��������
uint16 max_AD[8]={880,420,600,787,1473,1496,1574,1935}; //INDUCTOR8   INDUCTOR INDUCTOR INDUCTOR  INDUCTOR7  INDUCTOR   INDUCTOR6   INDUCTOR5   
uint16 min_AD[8]={0,0,0,0,0,0,0,0};//�����Сֵ

/****************************************/
//�� ����ScanNorma(void)
//�� �ܣ���̬��ȡ��ֵ
//˵ ����ɨ�������Сֵ���洢��max_AD[] min_AD[]
//��1���ӵ��Խ׶ε��ã���Ҫ�˻���������
//ע�⣬������ǿ���������룬���������Դ���
/****************************************/
void ScanNorma(uint16 times)
{
    uint16 i,j;
    uint16 AD_valu[8];
   
    for(i=0;i<times;i++) //1200����
    {
       AD_valu[0] = LPLD_ADC_Get(ADC0, AD8);  //B0 ͨ��      //ǰ�����
       AD_valu[1] = LPLD_ADC_Get(ADC0, AD9);  //B1 ͨ��     
       AD_valu[2] = LPLD_ADC_Get(ADC0, AD12);  //B2 ͨ��     
       AD_valu[3] = LPLD_ADC_Get(ADC0, AD13);  //B3 ͨ�� 
       
       AD_valu[4] = LPLD_ADC_Get(ADC1, AD10);  //B4 ͨ��      //�󷽵��
       AD_valu[5] = LPLD_ADC_Get(ADC1, AD11);  //B5 ͨ��     
       AD_valu[6] = LPLD_ADC_Get(ADC1, AD13);  //B6 ͨ��     
       AD_valu[7] = LPLD_ADC_Get(ADC1, AD12);  //B7 ͨ�� 
       
       
       for(j=0;j<8;j++) 
       {    
           if(AD_valu[j] >= max_AD[j])  
             max_AD[j] = AD_valu[j];
          
           if( AD_valu[j] <= min_AD[j] )
             min_AD[j] = AD_valu[j];
       }
    }  

}