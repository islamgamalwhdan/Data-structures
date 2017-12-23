#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/**********************************************
  *                                            *
  * ---------------- list.h ----------------- *
  *                                            *
*********************************************/

/*********************** Included Files ***********************/
//#include "global.h"



  /****************************** Constants ************************************/


  /****************************** ADT ******************************************/

typedef int ListEntry ;

typedef struct ListNode_
{
    void         *p_entry ;
    struct ListNode_ *next  , *before ;
}ListNode ;


 struct list_t
{
    ListNode  *current ;
    int Size , elem_size , currentpos ;
};
typedef struct list_t List ;

/********************************* Functions Prototypes **********************/
void InitializeList(List * , int) ;
int InsertList(int , void * , List *) ;
int DeleteList(int  , void * , List *) ;
void RetreiveList(int  , void * , List *) ;
int ReplaceList(int  , void*  , List *) ;
void ClearList(List *);
int ListSize(List *) ;
int ListEmpty(List *) ;
int ListFull(List *) ;
void TraverseList(List * , void(*)(void *)) ;
void MergeList(List * , List *) ;

#endif // LIST_H_INCLUDED
