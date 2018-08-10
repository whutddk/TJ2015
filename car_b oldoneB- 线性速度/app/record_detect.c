/****记忆算法C文件
****
***李锐戈 2015 1 27
**李锐戈 2015 2 23
*
*/


/****申请一个无限队列，同时保存编码器步数和location
************/
#include "common.h"
#include "include.h"



struct node *head;
struct node *using_point;

uint8 record_detecter_init()
{
  head = malloc(sizeof(struct node));
  using_point =head ;
  using_point ->send_count = 0;
  using_point ->send_location = 0;
  using_point ->next = NULL ;
  return 1;
}

uint8 record_detecter_add(uint32 count, int32 location)
{
  using_point -> next = malloc(sizeof(struct node));
  
  if ( using_point -> next != NULL )
  {
    using_point = using_point -> next;
    using_point -> send_count = count;
    using_point -> send_location = location;
    using_point -> next = NULL ;
    return 1;
  }
  else 
  {
    flag_stop = 1;
    //flag_a_car = 0;
    flag_b_car = 0;
    return 0;
  }
}

uint8 record_detecter_free()
{
  struct node* p_temp = head;
  if (head -> next != NULL)
  {
    head = head -> next;
    free(p_temp);
  }
  else
  {
    flag_stop = 1;
    flag_b_car = 0;
  }
  return 1;
}

void record_start() //AB车
{
  pluse_count_l = 0;
  solfware_count = 0;
  pit2ms_init() ;
}

void get_location() //B车获取赛道信息
{
  while(1)
  {
    if ( pluse_count_l > head -> send_count )
    {
      record_detecter_free();
    }
    else
    {
      location [4] = head ->send_location;
      /**************通过调整权重来改变灵敏度**********************/
  
    this_location = (int32)(location [0] * 0.05//【0】已经平滑化处理值及权重
               + location [1] * 0.10 //【1】已经平滑化处理值及权重
                 + location [2] * 0.15 //【1】已经平滑化处理值及权重
                   + location [3] * 0.20 //【1】已经平滑化处理值及权重
                    + location [4] * 0.50);//【2】当前AD差值，加入参与平滑化
 
 /*****************************************/
 if ( this_location >= 1000 )
   this_location = 1000;
 if ( this_location <= -1000 )
   this_location = -1000;
 /******************************************/
 location [0] = location[1];
 location [1] = location[2];
 location [2] = location[3];
 location [3] = this_location;
      break;
    }
  }
}


 

