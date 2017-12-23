
/*********************** Included Files ***********************/
#include <stdlib.h>  // for malloc .
#include <string.h>  // for memcpy
#include "stack.h"


/********************** Functions Definitions *****************/



void InitializeStack(Stack * ps , const int type_size)
{
#ifdef LIMITED_MEMORY_
       ps->top = NULL ;
       ps->stack_size_ = 0 ;
       ps->entry_size_ = type_size ;
#else
     ps->top = 0 ;
     ps->size_ = 0 ;
     ps->entry_size = type_size ; // Element data type size .
#endif // LIMITED_MEMORY_


}

/**************************************************************/

int Push (void * pe , Stack *ps )
{
 #ifdef LIMITED_MEMORY_
      StackNode * pn = (StackNode *) malloc(sizeof(StackNode)) ;

      if(!pn)
     return 0 ;
   else
   {
      void * pcpy_e = (void *)malloc(ps->entry_size_) ;
      if(!pcpy_e)
         return 0 ;
     else
     {
       memcpy(pcpy_e , pe , ps->entry_size_) ;
       pn->entry = pcpy_e ;
       pn->next = ps->top ;
       ps->top = pn ;
       ps->stack_size_++ ;
       return 1 ;
     } //pcpy_e
   }//pn
#else
      void * pn = (void*) malloc(ps->entry_size) ;

   if(!pn)
     return 0 ;
   else
   {
       //*pn = *pe ; make compilation error as we don't know pointers are generic and we don't know the type of the pointers .
       memcpy(pn , pe , ps->entry_size) ;
       ps->entry[ps->top++] = pn ;
       ps->size_++ ;
       return 1 ;
   }

#endif // LIMITED_MEMORY_

}

/**************************************************************/


void Pop ( void *pe , Stack *ps )
{
#ifdef LIMITED_MEMORY_
     StackNode *pn = ps->top ;

     memcpy(pe , (void *)pn->entry , ps->entry_size_) ;  // Get the top value (Last stored one) .
     ps->top = pn->next ;
     free(pn->entry) ;
     free(pn) ;
     ps->stack_size_-- ;
#else
     memcpy(pe , ps->entry[(ps->top) -1] , ps->entry_size ) ;
     free(ps->entry[(ps->top--) -1]) ;
     ps->size_-- ;
#endif // LIMITED_MEMORY_

}

/**************************************************************/

void StackTop( void *pe  , Stack *ps )
{
#ifdef LIMITED_MEMORY_
       memcpy(pe , (void *)ps->top->entry , ps->entry_size_) ;
#else
     memcpy(pe , ps->entry[(ps->top) -1] , ps->entry_size ) ;
#endif // LIMITED_MEMORY_
}

/**************************************************************/

int StackFull(Stack *ps)
{
#ifdef LIMITED_MEMORY_
    return 0 ; // memory will not be full except at we use all memory .
#else
    return (ps->size_ == MAXSTACK) ;
#endif // LIMITED_MEMORY_
}

/**************************************************************/

int StackEmpty(Stack *ps)
{
#ifdef LIMITED_MEMORY_
    return !ps->top ;  // return !ps->stack_size_ ;
#else
    return !ps->size_;
#endif // LIMITED_MEMORY_
}

/**************************************************************/

int StackSize(Stack *ps)
{
#ifdef LIMITED_MEMORY_
   return ps->stack_size_ ;
#else
   return ps->size_ ;
#endif // LIMITED_MEMORY_
}

/**************************************************************/

void ClearStack(Stack *ps)
{
#ifdef LIMITED_MEMORY_
    StackNode *pn = ps->top ;

    while(pn)
    {
        free(pn->entry) ;
        pn = pn->next ;
        free(ps->top) ;
        ps->top = pn ;
    }
    ps->stack_size_ = 0 ;
#else
    int i ;
    for( i =ps->top-1 ; i>= 0 ; i-- )  // clear temp memory used in heap to make copies of stack entry elements .
        free(ps->entry[i]) ;

    ps->top = 0 ; // return again to index = 0 that means it's destroyed .
    ps->size_ = 0 ;
#endif // LIMITED_MEMORY_
}

/**************************************************************/

void TraverseSatck(Stack *ps , void(*pf)(void *))
{
#ifdef LIMITED_MEMORY_
    StackNode *pn ;
    for (  pn = ps->top ; pn ; pn = pn->next  )
          (*pf) (pn->entry) ;
 #else
    int i ;

    for ( i = ps->top-1 ; i >= 0 ; i--)
    {
        (*pf)(ps->entry[i]) ;
    }
 #endif // LIMITED_MEMORY_
}
/*
void InitializeStack_types(CoStack *ps)
{
     ps->top = 0 ;
     ps->size_ = 0 ;
}

int Push_types(void * pe, CoStack * ps, int entry_size )
{
    void * pn = (void*) malloc(entry_size) ;

   if(!pn)
     return 0 ;
   else
   {
       memcpy(pn , pe , entry_size) ;
       ps->entry_info[ps->top].entry_data = pn ;
       ps->entry_info[ps->top++].entry_size = entry_size ;
       ps->size_++ ;
       return 1 ;
   }
}
*/
