/*
**�ڶ���Ѱ���㷨
��ֵ/����
***�����2014 11 28

�����2015 2 4 
�ı���λ�ò��Է��������õ���˼�룬
����������thislocation����
��ĳЩ��Ҫģʽʶ�������ǿ������
ͨ���ı�3ֵ��Ȩ�ظı�thislocation�ı仯������

****
***********
*/

#include "common.h"
#include "include.h"

int32 location[3] = {0,0,0};//�з���
int32 this_location = 0;


int8 flag_cross = 0;//�����䷽���ж�λ0 -1 1
int8 flag_curve = 0;//�����־λ��Ϊ�˼���,ѡ�����
int8 flag_miss =0;//���߼��� 
int8 flag_changeback = 0 ;//���л���ǰ��еı�־λ��


/**********************ģʽʶ������*************************************
1������ģʽ��
2��ʮ�ֽ��棺���� �����������ڵ�����󡣴�����������
  ֱ���䣺���� ���д��������ޣ��ڵ��һ������һ����С������ѡ����У����ڵ�нϴ�����ת��׼��
3�����п���״̬������֮����ƽ������
4�������ж��� ���� ��ǰ�ں��У����������ҶԳƣ��ڵ�к�С�� ����תǰ���
5������ ������ �ĸ����ֵ��С ����ǰ��� ת���У����У�������ͣ������
6��������� ����ֵ����
***********************************************************************/
/*********************��־λ����*************************************
flag_cross ��ȡֵ-1 0 +1 10�ֱ������ֱ��׼����ֱ�У����������������ƴ�������ֱ��׼�����Ѿ�ͨ�����
flag_curve �������־λ��ȡֵ0 1 ��λΪ���� ��ѡ��ǰ��У�������٣���λΪ���䣬ѡ����У��������
flag_miss : ���߼����������ں���ʱ������++���ﵽ��ֵ��ͣ��������������ģʽʶ��ɹ�ʱ��λ��
**********************************************************************/
/*********************��ֵ�궨���*************************************
LINE_ABOVE ���������Ϸ���ֵ
LINE_MISS ��������ֵ
LINE_MID ����������������ֵ
INDUCTOR1 :������
INDUCTOR2 �����ڵ��
INDUCTOR3 �����ڵ��
INDUCTOR4 ��������

*****/
void mode_detect2()//һ����־λ��flag_cross 0�����ж���-1��ת��1��ת
{ 
  out_all();//�����е�
  LED6(flag_curve);
  
  if (flag_curve == 0 && flag_changeback ==1)//���ڻ���״̬
  {
    common_situtation();
    if (location[2] - location[1] >= 50 || location[2] - location[1] <= -50)
    {
      flag_curve = 1 ;//������Ч����ʧһ�������ж�
      flag_changeback =0;////������Ч����ʧһ�������ж�
      location[2] = location[1];//�����ж�������
    }
  }
  
  
  /*********����ģʽǰ���*******************************************************/
  /*********����δ���ߣ��ڵ�в������� �������־λ��λ**********************************
  if (  (flag_curve == 0 ) && ( INDUCTOR1 > LINE_MISS ) 
      && ( INDUCTOR4 > LINE_MISS ) && ( INDUCTOR2 < LINE_ABOVE )
      && ( INDUCTOR3 < LINE_ABOVE ) )
  {
    LED1(ON);//����1
    flag_miss = 0;
    this_location =  (INDUCTOR1 - INDUCTOR4 ) / 2;
    
  }*/
  

   /*************������ж�********************************************/
  /*******�ڵ�в�ֵ������ֵ��һ�����ж���*****************************
  else if ( ((INDUCTOR1 < LINE_MISS )|| ( INDUCTOR4 <LINE_MISS ) ) 
           && ( ( ( INDUCTOR2 - INDUCTOR3 > DEFFER ) && ( INDUCTOR2 > INDUCTOR3 ) )|| ( ( INDUCTOR3 - INDUCTOR2 > DEFFER ) && ( INDUCTOR2 < INDUCTOR3 ) ) ) )
  {
    LED3(ON);
    flag_miss = 0;  
    flag_curve = 1;
    common_situtation();
    location[2] += ( (INDUCTOR2 - INDUCTOR3) ? 500 : -500 );
  }*/
  
   /*************ʮ�ֽ���*************************************************/
  /*******���в����ߣ����ڵ�������߷�Χ***********************************************/
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
    location[1] = 0;//�ٻ��˲������ƴ��
  }
  /*************ֱ����*************************************************/
  /********���ж��ߣ��ڵ������һ��������****************************/
    else if ( ( INDUCTOR1 < LINE_MISS ) && ( INDUCTOR4 < LINE_MISS ) 
             && ( ( INDUCTOR2 > LINE_MID ) || ( INDUCTOR3 > LINE_MID ) ))
    {
      flag_miss = 0;
      if ( flag_curve == 1 ) //�����Ѿ��򿪣���Ҫ��ת
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
      else //����δ����
      {
        flag_curve = 1;
        flag_cross = ( ( INDUCTOR2 < INDUCTOR3 ) ? -1 : 1 );
      }
    }
  
  /*****************��ȫ�����ж�************************
  else if ( ( INDUCTOR1 < LINE_MISS ) && ( INDUCTOR2 < LINE_MISS ) && ( INDUCTOR3 < LINE_MISS ) && ( INDUCTOR4 < LINE_MISS ))
  {
    light_all();
    if ( flag_curve == 0 )
    {
      flag_curve = 1;
      location[2] = location[1];
      flag_miss ++;
    }
      /*************����ģʽ********************************************/
  /*******���в����ߣ����ڵ��������******************************
    else if ( (flag_curve == 1 ) )
    {
      if ( (flag_miss == 1 ) &&  (INDUCTOR2 < LINE_MISS ) && ( INDUCTOR3 < LINE_MISS ) && ( INDUCTOR1 > LINE_MID && INDUCTOR4 > LINE_MID) )//�ڵ��ͬʱ�����������
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
        LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10);//ͣ����
        LED8(ON);
      }
    }
  }*/
  else//��ȫδ֪���
  {
    common_situtation();
  }

    
    
}

void detect2()
{
  mode_detect2();
  
/**************ͨ������Ȩ�����ı�������**********************/
  
 this_location = (int32)(location [0] * 0.3//��0���Ѿ�ƽ��������ֵ��Ȩ��
               + location [1] * 0.3 //��1���Ѿ�ƽ��������ֵ��Ȩ��
               + location [2] * 0.4);//��2����ǰAD��ֵ���������ƽ����
 
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
    uint8 i = 0; //��ʱ����֮���޸�����
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