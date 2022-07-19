/* main.c
 *
 * Created on: 5 April 2021
 *
 * Author: Benjamin Evans
 *
 * Description: Main top level file for Pong game which uses the HPS timer and IRQ interrupts to function
 */

// Included header files -----------------------------------------------------------------------------
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "DE1SoC_WM8731/DE1SoC_WM8731.h"
#include "DE1SoC_Mandelbrot/DE1SoC_Mandelbrot.h" // Mandelbrot Pattern Animation Generator
#include "Interrupts/Interrupts.h"
#include "LCDEngine/LCDEngine.h"
#include "GameEngine/GameEngine.h"
#include "Image/Pong.h"

// Debugging Function from ELEC5620M - Unit 3.2 Lab Task 2 - 3-2-DisplayTest\main.c
void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

int main(void){
	// Initialise and Configure IRQs
	HPS_IRQ_initialise(NULL);
	HPS_ResetWatchdog();
	ConfigureTimeInterrupt();
	ConfigureKeyInterrupt();

	// Initialise the LCD Display
	exitOnFail(
		LT24_initialise(0xFF200060,0xFF200080), //Initialise LCD
		LT24_SUCCESS);                          //Exit if not successful
	HPS_ResetWatchdog();

	// Initialise the Audio Coder
	exitOnFail(
		WM8731_initialise(0xFF203040),  //Initialise Audio Codec
	WM8731_SUCCESS);                //Exit if not successful
	HPS_ResetWatchdog();

	// Displaying Pong intro Image
	exitOnFail(
    	LT24_copyFrameBuffer(Pong,0,0,240,320),
    LT24_SUCCESS);//Exit if not successful
	usleep(5000000); 
	LT24_clearDisplay(LT24_BLACK);

	// Intitialsise the Private timer
    IntitialiseTimer(); 

	while(1) {

		// Software Flow control
		PongFSM();

		// Reset watchdog
		HPS_ResetWatchdog();
	}
}

