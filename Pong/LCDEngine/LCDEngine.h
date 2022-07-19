/* LCDEngine.h
 *
 * Created on: 5 May 2021
 *
 * Author: Benjamin Evans
 *
 * Description: LCDEngine header file driver to produce different shapes and text on LCD
 * Reference: Some code modified from Dr Craig Evans N5110.h library
 * 
 */

#ifndef LCDENGINE_LCDENGINE_H_
#define LCDENGINE_LCDENGINE_H_

#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "BasicFont/BasicFont.h"
#include "HPS_usleep/HPS_usleep.h"
#include <math.h>
#include <stdlib.h>


// LCDEngine Declarations ------------------------------------------------------------
/** Fill types for 2D shapes
 * Reference: Code modified from Dr Craig Evans N5110.h library
 * https://os.mbed.com/users/eencae/code/N5110/docs/tip/N5110_8h_source.html
 */
typedef enum {
    FILL_TRANSPARENT, ///< Transparent with outline
    FILL_BLACK,       ///< Filled black
    FILL_WHITE,       ///< Filled colour (no outline)
} FillType;

/**
 * DrawString
 *
 * Draws text on the lcd display
 * 
 * Inputs:
 * 		x:		    x position on display
 * 		y: 		    y position on display
 *      string:	    input string text to draw
 * 		colour: 	colour of text
 * 
 */
void DrawString(int x, int y, char *string, unsigned short colour);

/**
 * TestDrawString
 *
 * Test the draw sting function on the display by looping through alphabet and numbers
 * 
 */
void TestDrawString(void);

/** 
 * DrawLine 
 * 
 * This function draws a line between the specified points using linear interpolation
 * Reference: Code modified from Dr Craig Evans N5110.h library
 * https://os.mbed.com/users/eencae/code/N5110/docs/tip/N5110_8h_source.html
 * 
 * Inputs:
 *       x0:        x-coordinate of first point
 *       y0:        y-coordinate of first point
 *       x1:        x-coordinate of last point
 *       y1:        y-coordinate of last point
 *       type:      0 white,1 black,2 dotted
 *       colour:    colour of line
 */
void DrawLine(int x0, int y0, int x1, int y1, unsigned int const type, unsigned short colour);

/** 
 * DrawRectangle 
 * 
 * This function draws a rectangle
 * Reference: Code modified from Dr Craig Evans N5110.h library
 * https://os.mbed.com/users/eencae/code/N5110/docs/tip/N5110_8h_source.html
 * 
 * Inputs:
 *       x0:        x-coordinate of origin (top-left)
 *       y0:        y-coordinate of origin (top-left)
 *       width:     width of rectangle
 *       hight:     height of rectangle
 *       fill:      fill-type for the shape
 *       colour:    colour of rectangle
 */
void DrawRectangle(int x0, int y0, int width, int height, FillType const fill, unsigned short colour);

/** 
 * DrawCircle
 * 
 * This function draws a circle at the specified origin with specified radius in the screen buffer
 * Uses the midpoint circle algorithm.
 * Reference: Code modified from Dr Craig Evans N5110.h library
 * https://os.mbed.com/users/eencae/code/N5110/docs/tip/N5110_8h_source.html
 * http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
 *   
 * Inputs:
 *        x0:       x-coordinate of centre
 *        y0:       y-coordinate of centre
 *        radius:   radius of circle in pixels
 *        fill:     fill-type for the shape
 *        colour:   colour of circle
 */
void DrawCircle(int x0, int y0, int radius, FillType const fill, unsigned short colour);

#endif
