/***�����ۼ������� C �ļ�
***�����
***2014 11 28
2015 2 14 ����� ����������ӳ��
*/

#include "common.h"
#include "include.h"

void lpt_init()
{
  LPTMR_InitTypeDef lpt_inittype;
  lpt_inittype.LPTMR_Mode = LPTMR_MODE_PLACC;
  lpt_inittype.LPTMR_PluseAccInput = LPTMR_ALT2;
  lpt_inittype.LPTMR_IntEnable = FALSE ;
  lpt_inittype.LPTMR_Isr = NULL;
  LPLD_LPTMR_Init(lpt_inittype); 
}

//uint16 pluse_count_h = 0; //�����������λ
uint32 pluse_count_l = 0; //�����������λ

void get_count()//��Ҫ����ѭ���ڲ��ϵ���
{
  pluse_count_l += LPLD_LPTMR_GetPulseAcc(); //����ֱ�Ӳ���LPTMR��getpulse����
  LPLD_LPTMR_ResetCounter() ;
    
    lpt_init();

}



