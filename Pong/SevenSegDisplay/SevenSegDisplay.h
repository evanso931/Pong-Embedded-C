/* SevenSegDisplay.h
 *
 * Created on: 23 March 2022
 *
 * Author: Benjamin Evans
 *
 * Description: SevenSegmentDisplay header file to control seven segment displays
 * Reference: Code from ELEC5620M - Unit 1 Assignment - DE1SoC_SevenSeg.h code
 */

#ifndef SEVENSEGDISPLAY_SEVENSEGDISPLAY_H_
#define SEVENSEGDISPLAY_SEVENSEGDISPLAY_H_


// SevenSegDisplay Declarations ------------------------------------------------------------
/**
 * SevenSeg_Write
 *
 * Low level set function to send a byte value to a selected display.
 *
 * Inputs:
 * 		display:		index of the display to update (0-5)
 * 		value: 			byte to set display to.
 */
void SevenSeg_Write(unsigned int display, unsigned char value);

/**
 * SevenSeg_SetSingle
 *
 * Set a single seven segment display from a hexadecimal (0x0-0xF) value.
 *
 * Inputs:
 * 		display:		index of the display to update (0-5)
 * 		value: 			value to assign to the display (0x0-0xF)
 */
void SevenSeg_SetSingle(unsigned int display, unsigned int value);

/**
 * SevenSeg_SetDoubleDec
 *
 * Set a pair of seven segment displays from a decimal (00-99) value.
 *
 * Inputs:
 * 		display:		index of the pair of displays to update (0-4)
 * 		value: 			value to assign to the display (00-99)
 */
void SevenSeg_SetDoubleDec(unsigned int display, unsigned int value);


#endif
