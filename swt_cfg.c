/*
 * swt_cfg.c
 *
 *  Created on: Sep. 06, 2021
 *      Author: n.kessa
 */
 
 
#include "swt.h"
#include "swt_cfg.h"

#define LINUX 1 
#define UNITY 2

#define TARGET LINUX 

#if TARGET == LINUX

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>

void task_1ms(){
    printf("task task_1ms called \n");
}

void task_2ms(){
    printf("task task_2ms called \n");
}

void task_3ms(){
    printf("task task_3ms called \n");
}

void task_10ms(){
    printf("task_10ms called \n");
}

void task_exit(){
    printf("task_exit called \n");
    exit(0); 
}

void task_15mS(){
    printf("task_15mS called \n");
}

void task_19mS(){
    printf("task_19mS called \n");
}

/*define variables and call back functions_*/
swt_task_t swt_task_t_arr[] = {
        /*index = 0*/
        { 
            .callback_function = task_1ms , 
            .timer_interval = 1,
            .timer_interval_offset = 1
        },
        /*index = 1*/
        { 
            .callback_function = task_2ms , 
            .timer_interval = 2,
            .timer_interval_offset = 0
        },
        /*index = 2*/
        { 
            .callback_function = task_3ms , 
            .timer_interval = 3,
            .timer_interval_offset = 1
        },
        /*index = 3*/ 
        { 
            .callback_function = task_10ms , 
            .timer_interval = 10,
            .timer_interval_offset = 3
        },
        /*index = 4*/ 
        { 
            .callback_function = task_exit , 
            .timer_interval = 50,
            .timer_interval_offset = 0
        },
        /*index = 5*/ 
        { 
            .callback_function = task_15mS , 
            .timer_interval = 15,
            .timer_interval_offset = 2
        },
        /*index = 6*/ 
        { 
            .callback_function = task_19mS , 
            .timer_interval = 19,
            .timer_interval_offset = 0
        }
};

/*the preprocessor will calculate the size of the array of configuration*/
const uint32_t swt_number_of_tasks = (sizeof(swt_task_t_arr)/sizeof(swt_task_t_arr[0])) ; 
static struct itimerval delay;

swt_err_t swt_init_cfg()
{
    
    signal (SIGALRM, swt_callBack_1ms);
	delay.it_value.tv_sec =0;
	delay.it_value.tv_usec = 1000;
	delay.it_interval.tv_sec = 0;
	delay.it_interval.tv_usec=0;
	

	//arm the timer
	
	int ret = setitimer (ITIMER_REAL, &delay, NULL);
	if (ret) {
		perror ("setitimer");
		return swt_err_ok;
	}
    
}

swt_err_t swt_reArm_cfg()
{
    int ret = setitimer (ITIMER_REAL, &delay, NULL);
	if (ret) {
		perror ("setitimer");
		return swt_err_ok;
	}
}


swt_err_t swt_tick_cfg()
{
    printf("tick %d \n" , swt_getTicks());
}
#elif /*!TARGET == LINUX*/

#else 

#endif 

