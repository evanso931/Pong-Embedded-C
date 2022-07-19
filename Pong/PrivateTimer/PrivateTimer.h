/* PrivateTimer.h
 *
 * Created on: 7 April 2022
 *
 * Author: Benjamin Evans
 *
 * Description: Private Timer header file for triggering events based on ELEC5620M - Unit 2.2 - HPS_PrivateTimer.c code
 * Reference: Some Code from ELEC5620M - Unit 2 - NonBlockingTimer.h 
 * 
 */

#include <stdbool.h>

#ifndef PRIVATETIMER_PRIVATETIMER_H_
#define PRIVATETIMER_PRIVATETIMER_H_

// PrivateTimer Declarations ------------------------------------------------------------
/**
 * InititialiseTimer
 *
 * Sets the prescaler and other timer register values
 * 
 */
void IntitialiseTimer(void);


/**
 * TriggerTimer
 *
 * Returns true if timer finished counting down then resets, flase if still
 * counting down
 * 
 * Returns:
 *        bool: True if end of timer, flase if timer still counting down
 * 
 */
bool TriggerTimer(void);

/**
 * HalfTriggerTimer
 *
 * Returns true if timer finished counting down then resets, flase if still
 * counting down
 * 
 * Returns:
 *        bool: True if end of timer, flase if timer still counting down
 * 
 */
bool HalfTriggerTimer(void);

#endif 
