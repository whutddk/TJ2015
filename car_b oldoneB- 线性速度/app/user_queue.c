/*
****定长队列建立，用于放置传感器参数
****李锐戈
2014 11 25
*/
#include "common.h"
#include "include.h"



void queue_int( que *q )
{
  uint8 i;
  q->front = 0;
  q->rear=QUEMAX-1;
  for(i=0;i<QUEMAX;i++)
  {
    q -> data[i] = QUEUE_INIT;
  }
}

uint16 update_que( que *q , uint16 data_in )
{
  uint16 data_out;
  data_out =q-> data[ q -> rear ];
  q -> data[ q -> rear ] = data_in ;
  point_move(q);
  return data_out;
}

void point_move(que *q)
{
  if (q -> rear == 0)
  {
    q -> rear = 9 ;
  }
  else
  {
    q ->rear --;
  }
  if (q -> front == 0)
  {
    q -> front = 9 ;
  }
  else
  {
    q -> front --;
  }
}
