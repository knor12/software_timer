/*
 * swt.h : software timer header file provides API access file.
 *
 *  Created on: Sep. 06, 2021
 *      Author: n.kessa
 */
 
#ifndef SWT_H_
#define SWT_H_

#include <stdint.h>

 
typedef void (*swt_task_function_t) (void);

 
typedef enum 
{ 
    swt_err_ok = 0, 
    swt_err_init = 1 
 
} swt_err_t;

 
typedef enum 
{ 
    ready = 0, 
    blocked = 1, 
    inactif = 2, 
    running = 3 
 
} swt_task_state_t;

 
 
 
typedef struct 
{
  

    swt_task_function_t callback_function;	/*function called back when timer is up */
  

    uint32_t timer_interval;	/*the interval time (mS) of which the function is called */
  

    uint32_t timer_interval_offset;	/*offset so function can be staggered when executed to iprove time */
  

    swt_task_state_t flag;	/*indicates if the function is active etc */
  


    uint32_t counter;		/*counts how many seconds since function execution */



} swt_task_t;

 
 
 
/*public API functions*/ 
  
 
/*
*funtion to initialize the timer
*/ 
swt_err_t swt_init ();

 
 
/*
*called repeatadly to  process functions in the foreground, this needs to be within the context of main to execute functions that ready for execution
*/ 
swt_err_t swt_main ();

 
 
/*
*this funtion is to called in an interrupt context every 1mS
*/ 
void swt_callBack_1ms (void);

 
/*
*return the number of ticks (time in mS) since system startup
*/ 
uint32_t swt_getTicks ();

 
 
#endif	/* !SWT_H_ */
