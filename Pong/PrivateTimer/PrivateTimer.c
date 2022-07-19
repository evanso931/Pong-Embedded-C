/* PrivateTimer.c
 *
 * Created on: 7 April 2021
 *
 * Author: Benjamin Evans
 *
 * Description: Private Timer C file for triggering events based on ELEC5620M - Unit 2.2 - HPS_PrivateTimer.c code
 * Reference: Some Code from ELEC5620M - Unit 2 - NonBlockingTimer.c
 */


#include "PrivateTimer.h"


// Global variables -------------------------------------------------------------------------------------
// ARM A9 Private Timer Load
volatile unsigned int *private_timer_load      = (unsigned int *) 0xFFFEC600;
// ARM A9 Private Timer Value
volatile unsigned int *private_timer_value     = (unsigned int *) 0xFFFEC604;
// ARM A9 Private Timer Control
volatile unsigned int *private_timer_control   = (unsigned int *) 0xFFFEC608;
// ARM A9 Private Timer Interrupt
volatile unsigned int *private_timer_interrupt = (unsigned int *) 0xFFFEC60C;
unsigned int lastBlinkTimerValue = 0;
const unsigned int blinkPeriod = 10000000; 
unsigned int HalflastBlinkTimerValue = 0;
const unsigned int HaldblinkPeriod = 5000000; 

// Function Definitions PrivateTimer -----------------------------------------------------------------------
void IntitialiseTimer(void){
    lastBlinkTimerValue = *private_timer_value;
    HalflastBlinkTimerValue = *private_timer_value;
    // Configure the ARM Private Timer
    // Set the "Load" value of the timer to max value:
    *private_timer_load      = 0xFFFFFFFF; 
    // Set the "Prescaler" value to 0, Enable the timer (E = 1), Set Automatic reload
    // on overflow (A = 1), and disable ISR (I = 0)
    *private_timer_control   = (0 << 8) | (0 << 2) | (1 << 1) | (1 << 0);
}

bool TriggerTimer(void){
    unsigned int currentTimerValue = *private_timer_value;

    if (*private_timer_interrupt & 0x1) {
        // If the timer interrupt flag is set, clear the flag
        *private_timer_interrupt = 0x1;
    }

    // Check if Timer finished counter down
    if ((lastBlinkTimerValue - currentTimerValue) >= blinkPeriod) {
        
        lastBlinkTimerValue = lastBlinkTimerValue - blinkPeriod;
        return true;
    }else {
        return false;
    }

}

bool HalfTriggerTimer(void){
    unsigned int currentTimerValue = *private_timer_value;

    if (*private_timer_interrupt & 0x1) {
        // If the timer interrupt flag is set, clear the flag
        *private_timer_interrupt = 0x1;
    }

    // Check if Timer finished counter down
    if ((HalflastBlinkTimerValue - currentTimerValue) >= HaldblinkPeriod) {
        
        HalflastBlinkTimerValue = HalflastBlinkTimerValue - HaldblinkPeriod;
        return true;
    }else {
        return false;
    }
}
