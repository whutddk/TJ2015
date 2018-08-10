/***24L01 io SPI模拟程序 C 文件
***李锐戈  2015 01 01 
***
**
*/

#include "common.h"
#include "include.h"

uint8  TX_ADDRESS[NRF24L01_TX_ADR_LEN] = {0X34,0X43,0X10,0X10,0X01};
uint8  RX_ADDRESS[NRF24L01_RX_ADR_LEN] = {0X34,0X43,0X10,0X10,0X01};

uint16 spi_rw(uint8 uchar)
{
  uint8 bit_ctr;
  for (bit_ctr = 0; bit_ctr < 8;bit_ctr++)
  {
    MOSI = (uchar & 0x80);
    uchar = (uchar << 1);
    SCK = 1;
    uchar |= MISO ;
    SCK = 0;
  }
  return (uchar);
}

uint8 spi_read(uint8 reg)
{
  uint8 reg_val;
  CSN = 0;
  spi_rw(reg);
  reg_val = spi_rw(0);
  CSN = 1;
  return (reg_val);
}

uint16 spi_rw_reg(uint8 reg,uint8 value)
{
  uint16 status;
  CSN = 0;
  status = spi_rw(reg);
  spi_rw(value);
  CSN = 1;
  return (status);
}

uint16 spi_read_buf(uint8 reg ,uint8 *pbuf,uint8 uchars)
{
  uint16 status,uchar_ctr;
  
  CSN = 0;
  status = spi_rw(reg);
  
  for(uchar_ctr = 0;uchar_ctr<uchars;uchar_ctr++)
  {
    pbuf[uchar_ctr] = spi_rw(0);
  }
  CSN = 1;
  return (status);
}

uint16 spi_write_buf(uint8 reg,uint8 *pbuf,uint8 uchars)
{
  uint16 status,uchar_ctr;
  
  CSN = 0;
  status = spi_rw(reg);
  for (uchar_ctr = 0; uchar_ctr < uchars;uchar_ctr++)
    spi_rw(*pbuf++);
  CSN = 1;
  return (status);
}

void setRX_mode()
{
  CE = 0 ;
  spi_rw_reg(NRF24L01_WRITE_REG + NRF24L01_CONFIG , 0x0F);
  CE = 1 ;
  delay(130);
}

uint8 NRF_RXpacket(uint8 *rx_buff)
{
  uint8 revale = 0;
  uint8 sta;
  
  sta = spi_read(NRF24L01_STATUS);
  if (sta & 0x40)//第六位
  {
    CE = 0;
    spi_read_buf(NRF24L01_RD_RX_PLOAD,rx_buff,NRF24L01_PLOAD_LEN);
    revale = 1;
  }
  spi_rw_reg(NRF24L01_READ_REG + NRF24L01_STATUS,sta);
  return revale;
}

void NRF_TXpacket(uint8 *tx_buf)
{
  CE = 0;
  spi_write_buf(NRF24L01_WRITE_REG + NRF24L01_RX_ADDR_P0,TX_ADDRESS,NRF24L01_TX_ADR_LEN);
  spi_write_buf(NRF24L01_WR_TX_PLOAD,tx_buf,NRF24L01_PLOAD_LEN);
  spi_rw_reg(NRF24L01_WRITE_REG + NRF24L01_CONFIG,0x0e);
  CE = 1;
  delay(10);
}



void NRF_init()
{
  GPIO_InitTypeDef gpio_inittype;
  gpio_inittype.GPIO_PTx = PTE;
  gpio_inittype.GPIO_Pins = GPIO_Pin3;
  gpio_inittype.GPIO_Dir = DIR_INPUT;
  gpio_inittype.GPIO_PinControl = IRQC_DIS ;
  gpio_inittype.GPIO_Output = OUTPUT_L;
  LPLD_GPIO_Init(gpio_inittype);
  
  
  gpio_inittype.GPIO_PTx = PTE;
  gpio_inittype.GPIO_Pins = GPIO_Pin1 | GPIO_Pin2 | GPIO_Pin4 | GPIO_Pin7;
  gpio_inittype.GPIO_Dir = DIR_OUTPUT;
  gpio_inittype.GPIO_PinControl = IRQC_DIS ;
  gpio_inittype.GPIO_Output = OUTPUT_L;
  LPLD_GPIO_Init(gpio_inittype);
/*
  DDRE3 = 0;//INPUT
  DDRE1 = 1;//OUTPUT
  DDRE2 = 1;
  DDRE4 = 1;
  DDRE7 = 1;
*/ 
  
  delay(100);
  CE = 0;
  CSN = 1;
  SCK = 0;
  spi_write_buf(NRF24L01_WRITE_REG + NRF24L01_TX_ADDR,TX_ADDRESS,NRF24L01_TX_ADR_LEN);
  spi_write_buf(NRF24L01_WRITE_REG + NRF24L01_RX_ADDR_P0, RX_ADDRESS,NRF24L01_RX_ADR_LEN);
  spi_rw_reg(NRF24L01_WRITE_REG + NRF24L01_EN_AA,0x01);
  spi_rw_reg(NRF24L01_WRITE_REG + NRF24L01_EN_RXADDR,0x01);
  spi_rw_reg(NRF24L01_WRITE_REG + NRF24L01_RF_CH,40);
  spi_rw_reg(NRF24L01_WRITE_REG + NRF24L01_RX_PW_P0,NRF24L01_PLOAD_LEN);
  spi_rw_reg(NRF24L01_WRITE_REG + NRF24L01_RF_SETUP,0x0f);
  
}