/* Sound.c
 *
 * Created on: 20 April 2022
 *
 * Author: Benjamin Evans
 *
 * Description: Sound c file for paddle and ball blips
 * 
 */


#include "Sound.h"


// Global variables Pointers -------------------------------------------------------------------------------------
volatile unsigned char* fifospace_ptr;
volatile unsigned int*  audio_left_ptr;
volatile unsigned int*  audio_right_ptr;
double phase = 5.0;  // Phase accumulator
double inc   = 5.0;  // Phase increment
double ampl  = 2.0;  // Tone amplitude (i.e. volume)
signed int audio_sample = 0;
bool PlayBack = false;
volatile unsigned int * HPS_timer_ptr = (unsigned int *) 0xFFC08000;
volatile unsigned int*  LEDR_ptr  = (unsigned int *) 0xFF200000; // Red LEDs base address

// Function Definitions Sound ------------------------------------------------------------------------------------
// Reference: Sound Code from ELEC5620M - Unit 3.1 Lab Task 1 - 3-1-ToneGenerator/main.c
void PlayBlip(void){
    PlayBack = true;

    // Clear FIFO
    WM8731_clearFIFO(true,true);
    fifospace_ptr = WM8731_getFIFOSpacePtr();
    audio_left_ptr = WM8731_getLeftFIFOPtr();
    audio_right_ptr = WM8731_getRightFIFOPtr();

    inc   = 459 * PI2 / F_SAMPLE;  // Calculate the phase increment based on desired frequency - e.g. 440Hz
    ampl  = 8388608.0;               // Pick desired amplitude (e.g. 2^23). WARNING: If too high = deafening!
    phase = 0.0;

    // Start Timer 
    HPS_timer_ptr[2] = 0x03; // mode = 1, enable = 1

    while(PlayBack){
        if ((fifospace_ptr[2] > 0) && (fifospace_ptr[3] > 0)) {
            //If there is space in the write FIFO for both channels:
            //Increment the phase
            phase = phase + inc;

            //Ensure phase is wrapped to range 0 to 2Pi (range of sin function)
            while (phase >= PI2) {
                phase = phase - PI2;
            }

            // Calculate next sample of the output tone.
            audio_sample = (signed int)( ampl * sin( phase ) );

            // Output tone to left and right channels.
            *audio_left_ptr = audio_sample;
            *audio_right_ptr = audio_sample;
        }
        ResetWDT();
    }
    // Stop Timer Interupt
    HPS_timer_ptr[2] = 0x02;

    // Reset watchdog
    HPS_ResetWatchdog();
}

void ConfigureTimeInterrupt(void){
    // ELEC5620M - Unit 2.A Lab Task 1 - 2-A-Interrupts/main.c
    
    // Configure HPS Timer to interrupt every 0.01 seconds
    HPS_timer_ptr[2] = 0; // write to control register to stop timer
    // Set the timer period
    HPS_timer_ptr[0] = 1000000; // period = 1/(100 MHz) x (100 x 10^6) = 1 sec
    // Write to control register to start timer, with interrupts
    HPS_timer_ptr[2] = 0x03; // mode = 1, enable = 1
    // Register interrupt handler for timer
    HPS_IRQ_registerHandler(IRQ_TIMER_L4SP_0, timerISR);
    HPS_ResetWatchdog();
}

void timerISR(HPSIRQSource interruptID, bool isInit, void* initParams) {
    if (!isInit) {
        volatile unsigned int * HPS_timer_ptr = (unsigned int *) 0xFFC08000;

        // Clear the Timer Interrupt Flag
        unsigned int gpio_rmw = HPS_timer_ptr[3]; 

        // Stop Note Sound
        PlayBack = false;
    }

    // Reset watchdog
    HPS_ResetWatchdog();
}
