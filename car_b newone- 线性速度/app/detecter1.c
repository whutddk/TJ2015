/*
**��һ�����������㷨
***4��У�2�� 2��
�����
2014 11 27
*/

#include "common.h"
#include "include.h"

#define NOLINE 10 //�ɵ���ֵС�ڸ�ֵ�ж�Ϊ��ж���
#define K_DET1 0.01
#define MID_VALUE 2000

uint16 ind1,ind2,ind3,ind4;//�����ĸ�����ĵ��ֵ
//��ֵ�Ѿ�����ã�����ֱ�ӷ���
//4��ֵ�������� ��������





void mode_detect1()//ģʽʶ�����
{
  
}


void detect1()  //�践��ֵΪ0����������
{
  mode_detect1();//����ģʽʶ������
  if ( ind1 < NOLINE  && ind4 <NOLINE )//2����з�������
  {
    this_location = last_location;
  }
  else if (ind1 > NOLINE && ind2 >NOLINE)//�����о�����
  {
    this_location = ( int16 ) K_DET1 * ( ind4 - ind1 ) ; //����������ϱ�����һ��
  }
  else//��һ��û��
  {
    if (ind1 < NOLINE )
    {
      this_location = ( ind4 - MID_VALUE ) * 2 ;
    }
    else
    {
      this_location = ( ind1 - MID_VALUE ) * 2 ;
    }
  }
  last_location = this_location ;
   
      
    
}