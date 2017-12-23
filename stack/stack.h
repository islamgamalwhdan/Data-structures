#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

 /**********************************************
  *                                            *
  * ---------------- stack.h ----------------- *
  *                                            *
  *********************************************/

/*********************** Included Files ***********************/

#include "global.h"


/****************************** Constants ************************************/




  /****************************** ADT ******************************************/

#ifdef LIMITED_MEMORY_
      typedef struct StackNode_
   {
      void * entry ;
      struct StackNode_ *next ;
   }StackNode ;


   typedef struct Stack_
   {
       StackNode *top ;
       int entry_size_ ;
       int stack_size_ ;
   }Stack ;
#else


  typedef struct stack_    // stack abstract data type by implementer only .
  {
      int top ;
      int size_ ;
      int entry_size ;
      void * entry [MAXSTACK] ; // array of pointers to elements copies in heap memory .
  }Stack ;

/* Test combined Stack push and pop
typedef struct CoStackNode_
{
    void * entry_data ;
    int entry_size ;
}CoStackNode ;

  typedef struct CoStack_
  {
      int top ;
      int size_;
      CoStackNode entry_info[MAXSTACK] ; // array of struct of elements
  }CoStack;
  */

#endif // LIMITED_MEMORY_


  /********************************* Functions Prototypes **********************/

  void InitializeStack(Stack * , const int) ;
  int Push (void * , Stack * ) ;    /* Pre-conditions : 1 - stack initialized       2- stack must not be Full  */
  void Pop ( void * , Stack * ) ; /* Pre-conditions : 1 - stack initialized       2- stack must not be empty  */
  int StackFull(Stack *) ;
  int StackEmpty(Stack *) ;
  void StackTop( void *  , Stack * ) ; /* Pre-conditions : 1 - stack initialized       2- stack must not be empty  */
  int StackSize(Stack *) ;  /* Pre-conditions : 1 - stack initialized*/
  void ClearStack(Stack *) ;/* Pre-conditions : 1 - stack initialized*/
  void TraverseSatck(Stack * , void(*)(void *)) ;
/*
  void InitializeStack_types(CoStack *) ;
  int Push_types(void * , CoStack * , int ) ;
  int Pop_types( void * , CoStack * , int ) ; // we cannot popping element for different types such as pop double to char
*/
#endif // STACK_H_INCLUDED
