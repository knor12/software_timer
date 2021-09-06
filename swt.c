/*
 * swt.c
 *
 *  Created on: Sep. 06, 2021
 *      Author: n.kessa
 */

#include "swt.h"
#include "swt_cfg.h"


extern  uint32_t swt_number_of_tasks;  
static uint32_t swt_ticks = 0; 
extern swt_task_t swt_task_t_arr[];

/*
funtion to initialize the timer
*/
swt_err_t swt_init( ){
    
    uint32_t  i = 0 ; 
    
    /*intialize the timers data*/
    swt_ticks = 0;
    for( i = 0 ; i< swt_number_of_tasks ; i++)
    {    
       swt_task_t_arr[i].flag = blocked; 
       swt_task_t_arr[i].counter = swt_task_t_arr[i].timer_interval + swt_task_t_arr[i].timer_interval_offset; 
    }
    
    /*call target specific initialization functions*/
    swt_init_cfg();
    
}

/*
called repeatadly to  process functions in the, this is called in a loop in main()
*/
swt_err_t swt_main()
{
    /*tasks*/
    for(int i = 0 ; i< swt_number_of_tasks ; i++)
    {
        /*run all ready functions and reinitialize the counters*/
        if(
            (swt_task_t_arr[i].flag == ready))
            {
                swt_task_t_arr[i].flag = running;
                
                /*run function*/
                swt_task_t_arr[i].callback_function();
                
                /*reintialize the timer*/
                swt_task_t_arr[i].counter=swt_task_t_arr[i].timer_interval;
                
                /*reset flag*/
                swt_task_t_arr[i].flag = blocked;
                

            }
            
    }
    
}

/*this funtion is to called in an interrupt context every 1mS*/
void swt_callBack_1ms(void)
{
    swt_ticks++; 
    
    (void)swt_tick_cfg();
    
    for(int i = 0 ; i< swt_number_of_tasks ; i++)
    {
        /*decrement counter for blocked functions waiting to run*/
        if(
            (swt_task_t_arr[i].flag == blocked))
            {
                swt_task_t_arr[i].counter--; 
            }
            
        /*check for function that need to run and mark them ready to run*/
        if(
            (swt_task_t_arr[i].counter==0)&&
            (swt_task_t_arr[i].flag == blocked))
            {
                swt_task_t_arr[i].flag = ready; 
            }
    }
    
    swt_reArm_cfg();
    
}

uint32_t swt_getTicks()
{
    return swt_ticks;
}