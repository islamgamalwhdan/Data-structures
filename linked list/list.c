/**********************************************
  *                                            *
  * ---------------- list.c ----------------- *
  *                                            *
   *********************************************/


/*********************** Included Files ***********************/
#include "list.h"
#include <stdlib.h>
#include<string.h>



/********************** Functions Definitions *****************/

void InitializeList(List *pl , int elem_size)
{
    pl->current = NULL ;
    pl->Size = pl->currentpos = 0 ;
    pl->elem_size = elem_size ;
}

/**************************************************************/

int InsertList(int pos , void * pe , List * pl)
{
    ListNode *pn;

    pn = (ListNode *)malloc(sizeof(ListNode)) ;

    if(pn)
    {
        void *p_ecpy = (void *) malloc(sizeof(pl->elem_size)) ;
        if(!p_ecpy)
            return 0 ;
        else
        {
          memcpy(p_ecpy , pe , pl->elem_size) ;
          pn->p_entry = p_ecpy ;
          pn->next = pn->before  = NULL ;

          if(pos == 0)
          {
            for(; pl->currentpos ; pl->currentpos--)
                 pl->current = pl->current->before ;

            pn->next = pl->current ;
            if(pl->Size)
               pl->current ->before = pn ;
            pl->currentpos = 0 ;
           }
         else
           {
               if( pos <= pl->currentpos )
              {
                for( ; pl->currentpos > pos-1 ; pl->currentpos--)
                     pl->current = pl->current->before ;
              }
               else   // pos > currentpos .
              {
                for( ; pl->currentpos < pos-1 ; pl->currentpos++)
                     pl->current = pl->current->next ;
              }//else pos>currentpos .
              pn->next = pl->current->next ;
              if(pl->Size >pos)
                 pl->current->next->before = pn ;

              pl->current->next = pn ;
              pn->before = pl->current ;
              pl->currentpos++ ;
           }// else pos == 0 .

        pl->current = pn ;
        pl->Size++ ;
        return 1 ;
        }

    }
    else
        return 0 ;
}


/**************************************************************/


int DeleteList(int pos  , void * pe , List *pl)
{
    ListNode *tmp ;

    if(pos == 0)
    {
      for( ; pl->current->before  ; pl->currentpos--) // loop to reach position 0 .
        pl->current = pl->current->before ;

      memcpy(pe , pl->current->p_entry , pl->elem_size) ;
      tmp = pl->current->next ;
      if(pl->Size >1)
        tmp->before = NULL ;

      free(pl->current->p_entry) ;
      free(pl->current) ;
      pl->current = tmp ;
    }
    else
    {
         if(pos <= pl->currentpos)
        {
           for( ; pl->currentpos > pos-1 ; pl->currentpos--)
               pl->current = pl->current->before ;
        }// if ==>  pos<=currentpos .

       else
        {
           for( ; pl->currentpos < pos-1 ; pl->currentpos++)
               pl->current = pl->current->next ;
        }//else pos> currentpos .

      tmp = pl->current->next ;
      memcpy(pe , tmp->p_entry , pl->elem_size);
      pl->current->next = tmp->next ;
      tmp->next->before = pl->current ;
      free(tmp->p_entry) ;
      free(tmp) ;
    } // else ==> if(pos == 0)

    pl->Size-- ;
    return 1 ;
}

/**************************************************************/

void RetreiveList(int pos , void *pe , List *pl)
{
    if(pos <= pl->currentpos)
         for( ; pl->currentpos > pos ; pl->currentpos-- )
              pl->current = pl->current->before ;
    else
        for( ; pl->currentpos < pos ; pl->currentpos++)
               pl->current = pl->current->next ;

    memcpy(pe , pl->current->p_entry , pl->elem_size) ;
}

/**************************************************************/

int ReplaceList(int pos , void * pe , List *pl)
{
    void *p_ecpy = (void *) malloc(sizeof(pl->elem_size)) ;
        if(!p_ecpy)
            return 0 ;
        else
        {
          memcpy(p_ecpy , pe , pl->elem_size) ;

         if(pos <= pl->currentpos)
             for( ; pl->currentpos > pos ; pl->currentpos-- )
                  pl->current = pl->current->before ;
         else
             for( ; pl->currentpos < pos ; pl->currentpos++)
                 pl->current = pl->current->next ;

            free(pl->current->p_entry) ; // free pointer to old location .
            pl->current->p_entry = p_ecpy ; // Assign p_entry to the new location .
            return 1 ;
        }
}

/**************************************************************/

void ClearList(List *pl)
{
    ListNode *pnext ;

    for(  ; pl->current->before  ; pl->current =  pl->current->before ); // loop to reach position 0 .

    while(pl->current)
    {
        pnext = pl->current->next ;
        free(pl->current->p_entry) ;
        free(pl->current);
        pl->current = pnext ;
    }
    pl->Size = pl->currentpos = 0 ;
}

/**************************************************************/

int ListSize(List *pl)
{
    return pl->Size ;
}

/**************************************************************/

int ListEmpty(List *pl)
{
    return (!pl->Size) ;
}

/**************************************************************/

int ListFull(List *pl)
{
    return 0 ;
}

/**************************************************************/

void TraverseList( List *pl , void(*pf)(void *) )
{
    ListNode *pn ;


    for( pn = pl->current ; pn->before  ; pn = pn->before ); // loop to reach position 0 .

    while(pn)
    {
        pf(pn->p_entry) ;
        pn = pn->next ;
    }
}

/**************************************************************/

void MergeList(List *p_dis, List *p_new)
{
    /*Get Tail of old List */
    ListNode *dis_current , *new_current ;

    for( dis_current = p_dis->current ; dis_current->next ;   dis_current = dis_current-> next ) ;

    /* Get Head of new list */
   for( new_current = p_new->current ; new_current->before ;   new_current = new_current-> before ) ;

    dis_current->next = new_current ;
    new_current->before = dis_current ;
    p_dis ->Size += p_new->Size ;
}


