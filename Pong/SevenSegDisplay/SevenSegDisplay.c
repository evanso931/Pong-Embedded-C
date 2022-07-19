/* SevenSegmentDisplay.c
 *
 * Created on: 23 March 2021
 *
 * Author: Benjamin Evans
 *
 * Description: SevenSegmentDisplay c file to control seven segment displays based on ELEC5620M - Unit 1 - DE1SoC_SevenSeg.c code
 * Reference: Code from ELEC5620M - Unit 1 Assignment - DE1SoC_SevenSeg.h code
 */


#include "SevenSegDisplay.h"

// Global pointer variables --------------------------------------------------------------------------------
// Base addresses of the seven segment display peripherals.
volatile unsigned char *sevenseg_base_lo_ptr = (unsigned char*)0xFF200020;
volatile unsigned char *sevenseg_base_hi_ptr = (unsigned char*)0xFF200030;

// Seven segment display select definitions ----------------------------------------------------------------
// There are four HEX displays attached to the low (first) address.
#define SEVENSEG_N_DISPLAYS_LO 4

// There are two HEX displays attached to the high (second) address.
#define SEVENSEG_N_DISPLAYS_HI 2

// Function Definitions SevenSegDisplay --------------------------------------------------------------------
void SevenSeg_Write(unsigned int display, unsigned char value) {
    // Select between the two addresses so that the higher level functions
    // have a seamless interface.
    if (display < SEVENSEG_N_DISPLAYS_LO) {
        // If we are targeting a low address, use byte addressing to access
        // directly.
        sevenseg_base_lo_ptr[display] = value;
    } else {
        // If we are targeting a high address, shift down so byte addressing
        // works.
        display = display - SEVENSEG_N_DISPLAYS_LO;
        sevenseg_base_hi_ptr[display] = value;
    }
}

void SevenSeg_SetSingle(unsigned int display, unsigned int value) {

	// Array to translate input value into relevant bit-mapping value of 7-segment display
	unsigned int seven_seg_hex_values[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
									   0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	// If the input value is greater than 15, only display a dash on segment 6, other wise display number
	if (value < 16) {
		SevenSeg_Write(display, seven_seg_hex_values[value]);
	} else {
		// Display dash
		SevenSeg_Write(display, 0x40);
	}

}

void SevenSeg_SetDoubleDec(unsigned int display, unsigned int value) {

	// Displays the least significant digit on the requested 7-segment display
	SevenSeg_SetSingle(display,value%10);

	// Displays the most significant digit on the 7-segment display to the left of the previous
	SevenSeg_SetSingle(display+1, (value-(value%10))/10);
}
