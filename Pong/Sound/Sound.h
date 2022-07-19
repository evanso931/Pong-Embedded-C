/* Sound.h
 *
 * Created on: 20 April 2022
 *
 * Author: Benjamin Evans
 *
 * Description: Sound header file for paddle and ball blips
 * Reference: Sound Code from ELEC5620M - Unit 3.1 Lab Task 1 - 3-1-ToneGenerator/main.c
 */

#ifndef SOUND_SOUND_H_
#define SOUND_SOUND_H_

#include "../Interrupts/Interrupts.h"
#include "DE1SoC_WM8731/DE1SoC_WM8731.h"
#include <math.h>
#include "HPS_Watchdog/HPS_Watchdog.h"

// Sound Constants Definitions ------------------------------------------------------------
#define F_SAMPLE 48000.0        // Sampling rate of WM8731 Codec
#define PI2      6.28318530718  //2 x Pi 


// Sound Declarations ------------------------------------------------------------
/**
 * PlayBlip
 *
 * Playes a blip sounds for when the ball hits the paddels or walls
 *
 */
void PlayBlip(void);

/**
 * timerISR
 *
 * HPS Timer Interrupt for stopwatch and runs split timer state machine
 *
 * Inputs:
 * 		interruptID:		ID of interrupt deffined in HPS_IRQ_IDs.h
 * 		isInit: 			Set to false when interrupt handler is called by IQR
 *      initParams:         pointer will be 0 when called by IQR
 */
void timerISR(HPSIRQSource interruptID, bool isInit, void *initParams);

/**
 * ConfigureTimeInterrupt
 *
 * Configure HPS Timer to interrupt every 0.01 seconds
 * Reference: ELEC5620M - Unit 2.A Lab Task 1 - 2-A-Interrupts/main.c
 *
 */
void ConfigureTimeInterrupt(void);

#endif 
