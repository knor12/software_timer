/*
 * swt_cfg.h
 *
 *  Created on: Sep. 06, 2021
 *      Author: n.kessa
 */
 
#ifndef SWT_CFG_H_
#define SWT_CFG_H_




/*
*target specific impementation for starting the timer
*/
swt_err_t swt_init_cfg();

/*
*in the case the timer used reqauire re-arming (one shot timer)
*if periodic timer is used do not implement this function, leave it empty
*/
swt_err_t swt_reArm_cfg();

/*
*use this as a piggyback and place any code you need to execute from interrupt service routine.
* this is optional
*/
swt_err_t swt_tick_cfg(); 

#endif  /* !SWT_CFG_H_ */