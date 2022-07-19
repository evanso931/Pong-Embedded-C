/* Interrupts.c
 *
 * Created on: 28 March 2021
 *
 * Author: Benjamin Evans
 *
 * Description: SevenSegmentDisplay c file to control seven segment displays
 * Reference: Interrupt Code from ELEC5620M - Unit 2.A Lab Task 1 - 2-A-Interrupts/main.c
 */

#include "Interrupts.h"

// Function Definitions Interrupts -----------------------------------------------------------------------
void ConfigureKeyInterrupt(void){
    // ELEC5620M - Unit 2.A Lab Task 1 - 2-A-Interrupts/main.c
    volatile unsigned int * KEY_ptr       = (unsigned int *) 0xFF200050;

    // Configure Push Buttons to interrupt on press for all four keys
    KEY_ptr[2] = 0xF;
    HPS_IRQ_registerHandler(IRQ_LSC_KEYS, pushbuttonISR);  // Register interrupt handler for keys
    HPS_ResetWatchdog();
}

void pushbuttonISR(HPSIRQSource interruptID, bool isInit, void* initParams) {
    if (!isInit) {
        volatile unsigned int * KEY_ptr     = (unsigned int *) 0xFF200050;

        // Clear the interup flag
        unsigned int press = KEY_ptr[3];
        KEY_ptr[3] = press;

        if (press == 8){
        }
    }

    // Reset watchdog
    HPS_ResetWatchdog();
}



