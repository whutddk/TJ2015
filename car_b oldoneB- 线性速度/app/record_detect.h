/****记忆算法H头文件
****
***李锐戈 2015 1 27
**
*
*/


#ifndef _RECORD_DETECT_H_
#define _RECORD_DETECT_H_

struct node
{
  uint32 send_count;
  int32 send_location;
  struct node *next;
};

extern struct node *head;
extern struct node *using_point;

uint8 record_detecter_init();
uint8 record_detecter_add(uint32 count, int32 location);
uint8 record_detecter_free();
void record_start();
void get_location();

#endif 