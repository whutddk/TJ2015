/********超声波模块 C文件****************
*******李锐戈 2015 2 6
*
*
*/

#include "common.h"
#include "include.h"

void sonar_init()
{
  /************TRIO*******************/
  GPIO_InitTypeDef gpio_inittype;
  gpio_inittype.GPIO_PTx = TRIO_PT;
  gpio_inittype.GPIO_Pins = TRIO_PIN;
  gpio_inittype.GPIO_Dir = DIR_OUTPUT;
  gpio_inittype.GPIO_Output = OUTPUT_L;
  gpio_inittype.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_inittype);
  
  /************ECHO*******************/
  gpio_inittype.GPIO_PTx = ECHO_PT;
  gpio_inittype.GPIO_Pins = ECHO_PIN;
  gpio_inittype.GPIO_Dir = DIR_INPUT;
  gpio_inittype.GPIO_PinControl = INPUT_PULL_DOWN|IRQC_RI;
  gpio_inittype.GPIO_Isr = sonar_ISR;
  LPLD_GPIO_Init(gpio_inittype);
  //LPLD_GPIO_EnableIrq(gpio_inittype);
  
  
  pit0us_init();
}

void sonar_detect()
{
  pit0us_init();
  LPLD_GPIO_Output_b( TRIO_PT, TRIO_NUM, 1);
  delay(15);
  LPLD_GPIO_Output_b( TRIO_PT, TRIO_NUM, 0);
  
}


uint16 sonar_distance = 0;
void sonar_ISR()
{
  if(LPLD_GPIO_Input_b(ECHO_PT, ECHO_NUM))
  {
    sonar_count = 0 ;
    sonar_distance = 0;
    while(LPLD_GPIO_Input_b(ECHO_PT, ECHO_NUM));
    sonar_distance = 3400 * sonar_count ;
    sonar_distance = sonar_distance;
  }
}


