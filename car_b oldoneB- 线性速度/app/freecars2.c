

/*
name：  FreeCars上位机示波器例程
author：FreeCars军哥
Date:   2014-10-22
site:   Http://FreeCars.taobao.com
QQ群：  384273254，149168724 
版权：  此代码为FreeCars上位机协议代码，允许任意使用，也允许用于商业用途，但请保留此段文字！
tips:   强烈建议小伙伴们使用FreeCars出品的蓝牙模块套装，无线上位机从这里开始！
*/

#include "common.h"
#include "include.h"

uint8 uSendBuf[UartDataNum*2]={0};
uint8 FreeCarsDataNum=UartDataNum*2;

double UartData[9] = {0};
SerialPortType SerialPortRx;

/*
向某个通道缓冲区填充数据
chanel：通道
data  ：数据-32768~32767
*/
void push(uint8 chanel,uint16 data)
{
    uSendBuf[chanel*2]=data/256;
    uSendBuf[chanel*2+1]=data%256;
}


/*
轮询法发送一帧数据
消耗时间与数据长度有关
不可以放在中断里面周期性调用
消耗时间计算看帮助文档
*/
void sendDataToScope()
{
  uint8 i,sum=0; 
  //使用轮询的方式发送数据，当数据未发送，程序停在此处直到发送完成
  LPLD_UART_PutChar(FreeCarsUARTPort,251);
  LPLD_UART_PutChar(FreeCarsUARTPort,109);
  LPLD_UART_PutChar(FreeCarsUARTPort,37);
  sum+=(251);      //全部数据加入校验
  sum+=(109);
  sum+=(37);
  for(i=0;i<FreeCarsDataNum;i++)
  {
    LPLD_UART_PutChar(FreeCarsUARTPort,uSendBuf[i]);
    sum+=uSendBuf[i];         //全部数据加入校验
  }
 LPLD_UART_PutChar(FreeCarsUARTPort,sum);
}

void uart0_isr(void)//接收中断
{
  int i,b,d1;
  uint32 d;
  
  //if((UART_S1_REG(UART0) & UART_S1_RDRF_MASK))//是接收中断
  {
    SerialPortRx.Data = LPLD_UART_GetChar(UART0);  
    
    if( SerialPortRx.Stack < UartRxBufferLen )
    {
      SerialPortRx.Buffer[SerialPortRx.Stack++] = SerialPortRx.Data;
      
      if(   SerialPortRx.Stack >= UartRxDataLen  //UartRxDataLen个数为一帧
         && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen]  ==0xff //校验字头
           && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+1]==0x55
             && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+2]==0xaa
               && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+3]==0x10 )
      {   //double data 9个通道数据校验
        SerialPortRx.Check = 0;
        b = SerialPortRx.Stack - UartRxDataLen; //起始位
        for(i=b; i<SerialPortRx.Stack-1; i++)  //除校验位外的位进行校验
        {
          SerialPortRx.Check += SerialPortRx.Buffer[i];//校验
        }
        
        if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
        {   //校验成功，进行数据解算
          for(i = 0; i<9; i++)
          {
            d = SerialPortRx.Buffer[b+i*4+4]*0x1000000L + SerialPortRx.Buffer[b+i*4+5]*0x10000L + SerialPortRx.Buffer[b+i*4+6]*0x100L + SerialPortRx.Buffer[b+i*4+7];
            if(d>0x7FFFFFFF)
            {
              d1 = 0x7FFFFFFF - d;
            }
            else
            {
              d1 = d;
            }
            UartData[i]=d1;
            UartData[i]/=65536.0;
          }
          UartDebug();  //转去处理，把受到的数据付给变量
        }
        SerialPortRx.Stack = 0;
      }
      else if(   SerialPortRx.Stack >= UartRxCmdLen //UartRxDataLen个数为一帧
              && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen]  ==0xff
                && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+1]==0x55
                  && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+2]==0xaa
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+3]==0x77 )//cmd
      {
        SerialPortRx.Check = 0;
        b = SerialPortRx.Stack - UartRxCmdLen; //起始位
        for(i=b; i<SerialPortRx.Stack-1; i++)  //除校验位外的位进行校验
        {
          SerialPortRx.Check += SerialPortRx.Buffer[i];//校验
        }
        if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
        {   //校验成功
          UartCmd(UartCmdNum,UartCmdData);//处理接收到的命令，付给MCU命令变量
        }
        SerialPortRx.Stack = 0;
      }
    }
    else
    {
      SerialPortRx.Stack = 0;
    } 
  }
}

/*接收数据处理*/
void UartDebug()
{
  uint8 i;
  for(i=0;i<9;i++)
  {
    push(i,(uint16)UartData[i]);
  }
  P_servo = UartData[0];
  I_servo = UartData[1];
  
  
  
  
#if FREECARS_MOTTO
  LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, (uint32)UartData[2]);
#endif
  
#if !FREECARS_MOTTO
 speed_aim = (uint32)UartData[3];
#endif
}

void UartCmd(uint8 cmdnum,uint8 cmddata)///
{
  switch(cmddata)
  {
    case(6):break;//F6
    case(7):break;//F7
    case(8):break;//F8
    case(9):break;//F9
    case(10):break;//F10
    case(11):break;//F11
    case(12):break;//F12
    case(100):break;//PAUSE
    case(101):
      flag_stop = 0;
      flag_a_car = 0;
      flag_b_car = 0;
      break;//HOME
    case(102):
        flag_a_car = 1 ;
        flag_b_car = 0;
        flag_stop = 0;
        a_car_init();
      break;//PG UP
    case(103):
        flag_b_car = 1;
        flag_a_car = 0;
        flag_stop = 0;
        b_car_init();
        this_location = 0;
         location [0] = 
           location [1] = 
             location [2] =  
               location [3] =
                  location [4] = 0;
      break;//PF DN
    case(104):
    flag_stop = 1 ;
    flag_a_car = 0;
    flag_b_car = 0;
    break;//END
  }
}