#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STATES_MAX_NUMBER 5
#define STATE_MAX_INPUT   3

void FSM_State1(void*);
void FSM_State2(void*);
void FSM_State3(void*);
void FSM_State4(void*);

typedef enum
{
    STATE1 , STATE2 , STATE3 , STATE4
}State ;

typedef enum
{
    INPUT1 , INPUT2 , INPUT3
}Input ;


typedef void (*Fptr)(void *);

typedef struct States_Context{
    Input   MaxSignals;
    State   CurrentState;
    State   PerviousState;
    Input (*ProcessSignals)(void *);
    Fptr fsm_arr ;
}States_Context;

const Fptr Fsm_State[4][3] = {
                               {FSM_State2,FSM_State4,FSM_State3},
                               {FSM_State3,FSM_State2,FSM_State2},
                               {FSM_State3,FSM_State1,FSM_State3},
                               {FSM_State4,FSM_State4,FSM_State3}
};

#define Engine_Run_MACRO(CON , TABLE) ((TABLE[CON.CurrentState][CON.ProcessSignals(&CON)])(&CON) )


void Engine_Run(States_Context *Context)
{
    typedef void (*fptr_fsm)(void *) ; // User must know that fsm function proto type will be like that .
    #define Array_Col_Ptr fptr_fsm (*)[Context->MaxSignals]

   /* Context->PerviousState = Context->CurrentState ;
    State state = Context->CurrentState ;
    Input input = Context->ProcessSignals(Context) ;
    ( ( (Array_Col_Ptr)Context->fsm_arr)[state][input] ) (Context) ;*/

    /* OR if u need it in one statement*/

    Context->PerviousState = Context->CurrentState ;
    ( ( (fptr_fsm (*)[Context->MaxSignals])Context->fsm_arr)[Context->CurrentState ][Context->ProcessSignals(Context)] ) (Context) ;
}

Input ProcessStatesSignal(void *input)
{
  uint32_t FSM_C_Input=0;
  do{
  printf("Enter input from 0 - 2(For Case1)\n\t\t");
  scanf("%d",&FSM_C_Input);
  }while(FSM_C_Input>=3);
  return FSM_C_Input;
}

States_Context Case1Context , Case2Context;
int main()
{
    /*Case1*/
    Case1Context.CurrentState=STATE1;
    Case1Context.ProcessSignals =ProcessStatesSignal;
    Case1Context.MaxSignals=3;
    Case1Context.fsm_arr = Fsm_State ;

    while(1)
    {
      Engine_Run_MACRO (Case1Context ,Fsm_State ) ;
    }

    return 0 ;
}


void FSM_State1(void* Input)
{
 ((States_Context *)Input)->CurrentState = STATE1;
 printf("State 1 Prev = State%d\n",((States_Context *)Input)->PerviousState+1);
}
void FSM_State2(void* Input)
{
 ((States_Context *)Input)->CurrentState = STATE2;
 printf("State 2 Prev = State%d\n",((States_Context *)Input)->PerviousState+1);
}
void FSM_State3(void*  Input)
{
 ((States_Context *)Input)->CurrentState = STATE3;
 printf("State 3 Prev = State%d\n",((States_Context *)Input)->PerviousState+1);
}

void FSM_State4(void*  Input)
{
 ((States_Context *)Input)->CurrentState = STATE4;
 printf("State 4 Prev = State%d\n",((States_Context *)Input)->PerviousState+1);
}
