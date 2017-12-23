/**********************************************
  *                                            *
  * ---------------- queue.c ----------------- *
  *                                            *
   *********************************************/


/*********************** Included Files ***********************/
#include "queue.h"
#include <stdlib.h> // malloc .
#include <string.h> // memcpy .

/* Header file selection */
#ifdef LIMITED_MEMORY_

#else

#endif // LIMITED_MEMORY_

/********************** Functions Definitions *****************/

void InitializeQueue(Queue *pq , const int entry_size)
{
#ifdef LIMITED_MEMORY_
   pq->Front = NULL ;
   pq->rear = NULL ;
   pq->queue_size = 0 ;

   pq->entry_size = entry_size ;
#else
    pq->Front = 0 ;
    pq->rear = -1 ;  // As when we add new element we will increase rear by one (rear = 0) and add element .
    pq->queue_size = 0 ;

    pq->entry_size = entry_size ;
#endif // LIMITED_MEMORY_

}

/**************************************************************/

int Append(void * pe , Queue *pq)
{
#ifdef LIMITED_MEMORY_
QueueNode * pn = (QueueNode *) malloc(sizeof(QueueNode)) ;
    if(!pn)
        return 0 ;
    else
    {
        void * pcpy_e = (void *)malloc(pq->entry_size) ;

      if(!pcpy_e)
         return 0 ;
     else
     {
        memcpy(pcpy_e , pe , pq->entry_size) ;
        pn->entry = pcpy_e ;
        pn->next = NULL ;

        if(!pq->rear)
           pq->Front = pn ;
        else
           pq->rear->next = pn ;

        pq->rear = pn ;
        pq->queue_size++ ;
        return 1 ;
     } // pcpy_e
    } // pn .
    // return 1 ;
#else
    void * pcpy_e = (void *) malloc(pq->entry_size) ;
    if(!pcpy_e)
        return 0 ;
    else
    {
        memcpy(pcpy_e , pe , pq->entry_size) ;
        pq->rear = (pq->rear + 1) % MAXQUEUE ; // if rear == MAXQUEUE then rear will be 0 ;
        pq->entry[pq->rear] = pcpy_e ;
        pq->queue_size++;
        return 1 ;
    }

#endif // LIMITED_MEMORY_
}

/**************************************************************/

void Serve(void *pe, Queue *pq)
{
 #ifdef LIMITED_MEMORY_
     QueueNode * pn = pq->Front ;

    memcpy(pe , pn->entry , pq->entry_size ) ;   //*pe = pn->entry ;
    free(pn->entry) ; // first we free entry field pointer .
    pq->Front = pn->next ;
    free(pn) ; // free that node .
    if(!pq->Front)
        pq->rear = NULL ;  // special case occur only when we serve and queue has only one node .

    pq->queue_size-- ;
#else
     memcpy(pe , pq->entry[pq->Front] , pq->entry_size) ;
     free(pq->entry[pq->Front]) ;
     pq->Front = (pq->Front + 1) % MAXQUEUE ; // if front == MAXQUEUE then front will be 0 ;
     pq->queue_size-- ;
#endif // LIMITED_MEMORY_
}

/**************************************************************/

int QueueEmpty(Queue *pq)
{
#ifdef LIMITED_MEMORY_
     return (!pq->queue_size) ; // queue will be empty if size = 0 .
#else
     return (!pq->queue_size) ; // queue will be empty if size = 0 .
#endif // LIMITED_MEMORY_
}
/**************************************************************/

int QueueFull(Queue *pq)
{
#ifdef LIMITED_MEMORY_
      return 0 ;
#else
      return (pq->queue_size == MAXQUEUE) ;
#endif // LIMITED_MEMORY_

}

/**************************************************************/

int QueueSize(Queue *pq)
{
#ifdef LIMITED_MEMORY_
      return (pq->queue_size) ;
#else
      return pq->queue_size ;
#endif // LIMITED_MEMORY_

}

/**************************************************************/

void ClearQueue(Queue *pq)
{
#ifdef LIMITED_MEMORY_
/*QueueNode *pn ;
    int s ;

    for ( s = 0 ; s< pq->size_ ; s++ )
    {
        pn = pq->Front ;
        pq->Front = pq->Front->next ;
        free(pn) ;
    }
    pq->rear = NULL ;*/


    while ( pq->Front)
    {
        pq->rear = pq->Front->next ;
        free(pq->Front->entry) ; // free entry pointer .
        free(pq->Front) ;// free node  .
        pq->Front = pq->rear;
    }
    pq->queue_size = 0  ;
#else
int pos , s ;
    for( pos = pq->Front , s = 0 ; s < pq->queue_size ; s++ , pos++)
    {
        free(pq->entry[pos]) ;
        if( pos == MAXQUEUE) pos = 0 ;
    }

    pq->Front = 0 ;
    pq->rear = -1 ;  // As when we add new element we will increase rear by one (rear = 0) and add element .
    pq->queue_size = 0 ;
#endif // LIMITED_MEMORY_

}

/**************************************************************/

void TraverseQueue(Queue *pq , void (*pf)(void *))
{
#ifdef LIMITED_MEMORY_
      QueueNode * pn = pq->Front ;

  while( pn )
  {
      (*pf)(pn->entry) ;
      pn = pn->next ;
  }
#else
      int s , pos ;

    for( pos = pq->Front , s = 0 ; s < pq->queue_size ; s++ , pos++)
    {
        (*pf)(pq->entry[pos]) ;
        if( pos == MAXQUEUE) pos = 0 ;
    }
#endif // LIMITED_MEMORY_

}

/**************************************************************/
