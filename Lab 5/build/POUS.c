void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void TASKLAB5_init__(TASKLAB5 *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__IX0_0,data__->UP_START,retain)
  __INIT_LOCATED_VALUE(data__->UP_START,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_1,data__->DOWN_STOP,retain)
  __INIT_LOCATED_VALUE(data__->DOWN_STOP,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->LATCH,__BOOL_LITERAL(FALSE),retain)
  __INIT_LOCATED(BOOL,__QX0_0,data__->LED,retain)
  __INIT_LOCATED_VALUE(data__->LED,__BOOL_LITERAL(FALSE))
}

// Code part
void TASKLAB5_body__(TASKLAB5 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,LATCH,,((__GET_VAR(data__->LATCH,) || __GET_LOCATED(data__->UP_START,)) && !(__GET_LOCATED(data__->DOWN_STOP,))));
  __SET_LOCATED(data__->,LED,,__GET_VAR(data__->LATCH,));

  goto __end;

__end:
  return;
} // TASKLAB5_body__() 





