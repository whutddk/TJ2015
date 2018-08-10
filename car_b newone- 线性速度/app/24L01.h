/***24L01 io SPIģ����� H �ļ�
***�����  2015 01 01 
***
**
*/

#ifndef _24L01_H__
#define _24L01_H__

#define CE  PTE7_O
#define CSN PTE4_O
#define SCK PTE2_O
#define MOSI PTE1_O

#define MISO PTE3_I


/********�û����޸�ֵ ��ʼ****LPLD******/
//ѡ��NRF24L01ʹ�õ�SPIģ��
#define NRF24L01_SPIX    (SPI1)

//ѡ��NRF24L01 MOSI����Ӧ��IO
#define NRF24L01_MOSI  (PTE1)

//ѡ��NRF24L01 MISO����Ӧ��IO
#define NRF24L01_MISO  (PTE3)

//ѡ��NRF24L01 SCK����Ӧ��IO
#define NRF24L01_SCK  (PTE2)

//ѡ��NRF24L01 PCS0����Ӧ��IO
#define NRF24L01_PCS0  (PTE4)

//ѡ��NRF24L01 CE����Ӧ��IO
#define NRF24L01_CE_PTX  (PTE)
#define NRF24L01_CE_IOX  (GPIO_Pin7)
#define NRF24L01_CE_H    LPLD_GPIO_Output_b(NRF24L01_CE_PTX,NRF24L01_CE_IOX,OUTPUT_H) 
#define NRF24L01_CE_L    LPLD_GPIO_Output_b(NRF24L01_CE_PTX,NRF24L01_CE_IOX,OUTPUT_L) 

// NRF24L01��ز�������
#define NRF24L01_PLOAD_LEN        (32) //�����غɳ���
#define NRF24L01_TX_ADR_LEN       (5)  //TX��ַ����
#define NRF24L01_RX_ADR_LEN       (5)  //RX��ַ����

// Nrf24L01_CheckID
#define NRF24L01_RX_ADDR_P0_RESET_ID (0xE7E7E7E7)
#define NRF24L01_RX_ADDR_P1_RESET_ID (0xC2C2C2C2)
#define NRF24L01_TX_ADDR_RESET_ID    (0xE7E7E7E7)
// NRF24L01ָ��
#define NRF24L01_READ_REG         0x00   // �����üĴ���
#define NRF24L01_WRITE_REG        0x20   // д���üĴ���
#define NRF24L01_RD_RX_PLOAD      0x61   // ��ȡRX FIFO�е�����
#define NRF24L01_WR_TX_PLOAD      0xA0   // ��TX FIFO��д������
#define NRF24L01_FLUSE_TX         0xE1   // ���TX FIFO�е����� Ӧ���ڷ���ģʽ��
#define NRF24L01_FLUSE_RX         0xE2   // ���RX FIFO�е����� Ӧ���ڽ���ģʽ��
#define NRF24L01_REUSE_TX_PL      0xE3   // ����ʹ����һ����Ч����
#define NRF24L01_NOP              0xFF   // �޲��� ���ڶ�STATUS�Ĵ���
//********************************************************************************************************************// 
// NRF24L01�Ĵ���(��ַ)
#define NRF24L01_CONFIG           0x00  //���÷���״̬��CRCУ��ģʽ�Լ����շ�״̬��Ӧ��ʽ
#define NRF24L01_EN_AA            0x01  //�Զ�Ӧ��������
#define NRF24L01_EN_RXADDR        0x02  //�����ŵ�����
#define NRF24L01_SETUP_AW         0x03  //�շ���ַ�������
#define NRF24L01_SETUP_RETR       0x04  //�Զ��ط�����������
#define NRF24L01_RF_CH            0x05  //�����ŵ��趨
#define NRF24L01_RF_SETUP         0x06  //�������ʡ����Ĺ�������
#define NRF24L01_STATUS           0x07  //״̬�Ĵ���
#define NRF24L01_OBSERVE_TX       0x08  //���ͼ�⹦��
#define NRF24L01_CD               0x09  //��ַ��� 
#define NRF24L01_RX_ADDR_P0       0x0A  //Ƶ��0�������ݵ�ַ
#define NRF24L01_RX_ADDR_P1       0x0B  //Ƶ��1�������ݵ�ַ
#define NRF24L01_RX_ADDR_P2       0x0C  //Ƶ��2�������ݵ�ַ
#define NRF24L01_RX_ADDR_P3       0x0D  //Ƶ��3�������ݵ�ַ
#define NRF24L01_RX_ADDR_P4       0x0E  //Ƶ��4�������ݵ�ַ
#define NRF24L01_RX_ADDR_P5       0x0F  //Ƶ��5�������ݵ�ַ
#define NRF24L01_TX_ADDR          0x10  //���͵�ַ�Ĵ���
#define NRF24L01_RX_PW_P0         0x11  //����Ƶ��0�������ݳ���
#define NRF24L01_RX_PW_P1         0x12  //����Ƶ��1�������ݳ���
#define NRF24L01_RX_PW_P2         0x13  //����Ƶ��2�������ݳ���
#define NRF24L01_RX_PW_P3         0x14  //����Ƶ��3�������ݳ���
#define NRF24L01_RX_PW_P4         0x15  //����Ƶ��4�������ݳ���
#define NRF24L01_RX_PW_P5         0x16  //����Ƶ��5�������ݳ���
#define NRF24L01_FIFO_STATUS      0x17  //FIFOջ��ջ��״̬�Ĵ�������
//NRF24L01״̬�Ĵ���ֵ
#define NRF24L01_STATUS_MAX_RT    0x10 //�ﵽ����ط�״̬
#define NRF24L01_STATUS_TX_DS     0x20 //���ͳɹ�
#define NRF24L01_STATUS_RX_DR     0x40 //���ճɹ�

uint16 spi_rw(uint8 uchar);
uint8 spi_read(uint8 reg);
uint16 spi_rw_reg(uint8 reg,uint8 value);
uint16 spi_read_buf(uint8 reg ,uint8 *pbuf,uint8 uchars);
uint16 spi_write_buf(uint8 reg,uint8 *pbuf,uint8 uchars);
void setRX_mode();
uint8 NRF_RXpacket(uint8 *rx_buff);
void NRF_TXpacket(uint8 *tx_buf);
void NRF_init();


#endif 