/*
 * main.c
 *
 *  Created on: Sep. 06, 2021
 *      Author: n.kessa
 */
 
#include <stdio.h>
#include "swt.h"


int main()
{
    
    (void)swt_init();
    printf("Hello World\n");

    /*forever loop*/
    while(1)
    {
        swt_main();
        
    }

    return 0;
}
