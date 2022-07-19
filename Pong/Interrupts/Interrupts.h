/* Interrupts.h
 *
 * Created on: 28 March 2022
 *
 * Author: Benjamin Evans
 *
 * Description: Interrupts header file containing interrupt configuration and ISR declarations along with the state machine for the stopwatch
 * Reference: Interrupt Code from ELEC5620M - Unit 2.A Lab Task 1 - 2-A-Interrupts/main.c
 */

#ifndef INTERRUPTS_INTERRUPTS_H_
#define INTERRUPTS_INTERRUPTS_H_

#include "HPS_IRQ/HPS_IRQ.h"
#include "HPS_Watchdog/HPS_Watchdog.h"

// Interrupts Declaration ------------------------------------------------------------
/**
 * ConfigureKeyInterrupt
 *
 * Configure Push Buttons to interrupt on press for all four keys
 * Reference: ELEC5620M - Unit 2.A Lab Task 1 - 2-A-Interrupts/main.c
 *
 */
void ConfigureKeyInterrupt(void);

/**
 * pushbuttonISR
 *
 * Key Released Interrupt Displays Last Button Released and control stop watch functions
 *
 * Inputs:
 * 		interruptID:		ID of interrupt deffined in HPS_IRQ_IDs.h
 * 		isInit: 			Set to false when interrupt handler is called by IQR
 *      initParams:         pointer will be 0 when called by IQR
 */
void pushbuttonISR(HPSIRQSource interruptID, bool isInit, void *initParams);

#endif
