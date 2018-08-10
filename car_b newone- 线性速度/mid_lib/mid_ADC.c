/*******
*******ADC�в�⣬�����������¿⣬ʹ�����ʹ��
******
******/
#include "common.h"
#include "include.h"




void ADC_Init_solf ( ADC_Type *Adcx , uint8 BitMode  )
{
  ADC_InitTypeDef adc_init_struct;
  adc_init_struct.ADC_Adcx = Adcx;             /**ADC��*/
  adc_init_struct.ADC_BitMode = BitMode;      /*����*/
  adc_init_struct.ADC_CalEnable = TRUE;        /*��ó�ʼ��Ϊ��*///ʹ�ܳ�ʼ��У��
  adc_init_struct.ADC_HwAvgSel = HW_DISAVG;      
  adc_init_struct.ADC_SampleTimeCfg = SAMTIME_SHORT;    //�̲���ʱ��
  adc_init_struct.ADC_CalEnable = TRUE; //ʹ�ܳ�ʼ��У��
  adc_init_struct.ADC_DmaEnable = FALSE;        //��ʹ��DMA����
  adc_init_struct.ADC_DiffMode=ADC_SE;
  adc_init_struct.ADC_LongSampleTimeSel = LSAMTIME_20EX;
  adc_init_struct.ADC_PgaGain =  PGA_1GAIN;
  adc_init_struct.ADC_MuxSel=MUX_ADXXA;
    
    
  LPLD_ADC_Init(adc_init_struct);      
}
/*ADCӲ��������DMA����//ֻ��4ADʱ��Ч
******��ʱ�޷�ʹ�ã���ADCͨ����DMA��ʼ��ַ�޷����
***************
**************
void ADC_Init_hard ( ADC_Type *Adcx ��uint8  Req��uint32 *aim_Addr)//ǿ��12λ�ɼ�����DMA
{
   **********************************************
  //Step 1.����ADC0��ADC1�Ĳ���
  //ADC0-A
  adc0_init_struct.ADC_Adcx = ADC0;
  adc0_init_struct.ADC_BitMode = SE_12BIT;      //12λ����
  adc0_init_struct.ADC_CalEnable = TRUE;        //ʹ�ܳ�ʼ��У��
  adc0_init_struct.ADC_HwAvgSel = HW_4AVG;      //ʹ��4��Ӳ��У׼
  adc0_init_struct.ADC_HwTrgCfg = HW_TRGA;      //����A��ΪӲ������
  adc0_init_struct.ADC_DmaEnable = TRUE;        //ʹ��DMA����
  LPLD_ADC_Init(adc0_init_struct);      //��ʼ��ADC0-A��ͨ��
  //ADC0-B��ֻ�����ò�ͬ�����ĳ�Ա����
  adc0_init_struct.ADC_HwTrgCfg = HW_TRGB;      //����B��ΪӲ������
  LPLD_ADC_Init(adc0_init_struct);      //��ʼ��ADC0-B��ͨ��
  //ʹ��ADC0��ͨ��DAD1��AD14�����Ÿ��ù���
  LPLD_ADC_Chn_Enable(ADC0, DAD1);
  LPLD_ADC_Chn_Enable(ADC0, AD14);
  //ʹ��ADC0�����ת��ͨ��
  LPLD_ADC_EnableConversion(ADC0, DAD1, 0, FALSE);
  LPLD_ADC_EnableConversion(ADC0, AD14, 1, FALSE);
  
  //ADC1A
  adc1_init_struct.ADC_Adcx = ADC1;
  adc1_init_struct.ADC_BitMode = SE_12BIT;
  adc1_init_struct.ADC_CalEnable = TRUE;
  adc1_init_struct.ADC_HwAvgSel = HW_4AVG;
  adc1_init_struct.ADC_HwTrgCfg = HW_TRGA;
  adc1_init_struct.ADC_DmaEnable = TRUE;
  LPLD_ADC_Init(adc1_init_struct);
  //ADC1B
  adc1_init_struct.ADC_HwTrgCfg = HW_TRGB;
  LPLD_ADC_Init(adc1_init_struct);
  LPLD_ADC_Chn_Enable(ADC1, AD10);
  LPLD_ADC_Chn_Enable(ADC1, AD11);
  LPLD_ADC_EnableConversion(ADC1, AD10, 0, FALSE);
  LPLD_ADC_EnableConversion(ADC1, AD11, 1, FALSE);
    
  **********************************************
  //Step 2.����DMA CH0��DMA CH1���ֱ���ADC0��ADC1��DMA����
  //DMA CH0
  dma0_init_struct.DMA_CHx = DMA_CH0;           //ʹ��Ch0ͨ��
  dma0_init_struct.DMA_Req = ADC0_DMAREQ;       //DMA����ԴΪADC0
  dma0_init_struct.DMA_MajorLoopCnt = 2;        //��ѭ������2��,��ΪҪѭ��ADC0��AB����ͨ��
  dma0_init_struct.DMA_MinorByteCnt = 2;        //��ѭ�������ֽڼ���������ADC����Ϊ12λ����˴���2�ֽڣ�
  dma0_init_struct.DMA_SourceAddr = (uint32)&(ADC0->R[0]);       //Դ��ַ��ADC0����Ĵ���A��ַ
  dma0_init_struct.DMA_SourceDataSize = DMA_SRC_16BIT;   //Դ��ַ�������ݿ��16λ
  dma0_init_struct.DMA_SourceAddrOffset = 4;    //Դ��ַƫ��Ϊ4���ֽڣ���ΪADC0->R�Ĵ�Ϊ32λ��A�鴫����ɺ��ƶ���B��
  dma0_init_struct.DMA_LastSourceAddrAdj = -8;  //��ѭ�������ڵ�ַΪ-8���ֽڣ���Ϊ��ѭ��Ϊ2�μ�������˵�ַƫ����8���ֽ�
  dma0_init_struct.DMA_DestAddr = (uint32)&Result;       //Ŀ�ĵ�ַ��������Ľ����������ͷ��ַ
  dma0_init_struct.DMA_DestDataSize = DMA_DST_16BIT;     //Ŀ�ĵ�ַ�������ݿ��16λ
  dma0_init_struct.DMA_DestAddrOffset = 2;      //Ŀ�ĵ�ַƫ��Ϊ2���ֽڣ���ΪResultΪ16λ����
  dma0_init_struct.DMA_LastDestAddrAdj = -4;    //Ŀ�ĵ�ַ�����ڵ�ַΪ-4���ֽ�
  dma0_init_struct.DMA_AutoDisableReq = FALSE;   //�����Զ��������󣬼�������ѭ��������������
  //��ʼ��DMA
  LPLD_DMA_Init(dma0_init_struct);
  //ʹ��DMA����
  LPLD_DMA_EnableReq(DMA_CH0);
  
  //DMA CH1�����û�����ͬ
  dma1_init_struct.DMA_CHx = DMA_CH1;   
  dma1_init_struct.DMA_Req = ADC1_DMAREQ;       
  dma1_init_struct.DMA_MajorLoopCnt = 2;        
  dma1_init_struct.DMA_MinorByteCnt = 2; 
  dma1_init_struct.DMA_SourceAddr = (uint32)&(ADC1->R[0]);       
  dma1_init_struct.DMA_SourceDataSize = DMA_SRC_16BIT;  
  dma1_init_struct.DMA_SourceAddrOffset = 4;
  dma1_init_struct.DMA_LastSourceAddrAdj = -8;
  dma1_init_struct.DMA_DestAddr = (uint32)&Result+4;       //Ŀ�ĵ�ַ������������ͷ2��Ԫ�ش�ADC0�Ľ�������Ҫƫ��4���ֽ�ȡ��3��Ԫ�صĵ�ַ
  dma1_init_struct.DMA_DestDataSize = DMA_DST_16BIT;  
  dma1_init_struct.DMA_DestAddrOffset = 2;
  dma1_init_struct.DMA_LastDestAddrAdj = -4;
  dma1_init_struct.DMA_AutoDisableReq = FALSE;   
  //��ʼ��DMA
  LPLD_DMA_Init(dma1_init_struct);
  //ʹ��DMA����
  LPLD_DMA_EnableReq(DMA_CH1);
    
  **********************************************
  //Step 3.����PDB�����ڴ���ADC
  pdb_init_struct.PDB_CounterPeriodMs = 100;    //PDB���������ڣ����������4��ͨ��ÿ�ɼ�һ�εļ��
  pdb_init_struct.PDB_LoadModeSel = LOADMODE_0;
  pdb_init_struct.PDB_ContinuousModeEnable = TRUE;      //ʹ����������ģʽ����ֻ��Ҫ��ʼ����һ�Σ��Ժ�PDB�ͻ���������
  pdb_init_struct.PDB_TriggerInputSourceSel = TRIGGER_SOFTWARE; //�������ģʽ��������Ҫ������ģ�鴥��PDB����
  //��ʼ��PDB
  LPLD_PDB_Init(pdb_init_struct);
  //����PDBԤ��������
  //ʹ��ADC0-A���Ԥ��������
  LPLD_PDB_AdcTriggerCfg(ADC0, PRETRIG_EN_A|PRETRIG_DLY_A, 0);  
  //ʹ��ADC0-B���Ԥ�������ܣ���ʹ��Back to Backģʽ
  LPLD_PDB_AdcTriggerCfg(ADC0, PRETRIG_BB_B|PRETRIG_EN_B|PRETRIG_DLY_B, 0);
  //ʹ��ADC1-A���Ԥ�������ܣ���ʹ��Back to Backģʽ
  LPLD_PDB_AdcTriggerCfg(ADC1, PRETRIG_BB_A|PRETRIG_EN_A|PRETRIG_DLY_A, 0);
  //ʹ��ADC1-B���Ԥ�������ܣ���ʹ��Back to Backģʽ
  LPLD_PDB_AdcTriggerCfg(ADC1, PRETRIG_BB_B|PRETRIG_EN_B|PRETRIG_DLY_B, 0);
  //�������PDB��ʼ����
  LPLD_PDB_SoftwareTrigger();
  } 
}*/




