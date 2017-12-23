#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

  /**********************************************
  *                                            *
  * ---------------- queue.h ----------------- *
  *                                            *
*********************************************/

/*********************** Included Files ***********************/
#include "global.h"



  /****************************** Constants ************************************/



  /****************************** ADT ******************************************/

#ifdef LIMITED_MEMORY_
       typedef struct QueueNode_
{
    void             * entry ;
    struct QueueNode_ * next ;
}QueueNode ;

  typedef struct Queue_
  {
      QueueNode * Front ;
      QueueNode * rear  ;
      int queue_size ;
      int entry_size ;
  }Queue ;
#else
      typedef struct Queue_
  {
      int Front ;
      int rear ;
      int queue_size;
      int entry_size ;
      void * entry[MAXQUEUE] ;
  }Queue ;
#endif // LIMITED_MEMORY_


  /********************************* Functions Prototypes **********************/

void InitializeQueue(Queue * , const int) ;
int Append(void * , Queue *) ;
void Serve(void *, Queue *) ;
int QueueEmpty(Queue *) ;
int QueueFull(Queue *) ;
int QueueSize(Queue *) ;
void ClearQueue(Queue *) ;
void TraverseQueue(Queue * , void (*)(void *)) ;
#endif // QUEUE_H_INCLUDED
