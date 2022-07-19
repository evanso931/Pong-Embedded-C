/* LCDEngine.c
 *
 * Created on: 5 May 2021
 *
 * Author: Benjamin Evans
 *
 * Description: LCDEngine c file driver to produce different shapes and text on LCD
 * Reference: Some code modified from Dr Craig Evans N5110.h library
 * 
 */

#include "LCDEngine.h"


// Function Definitions LCDEngine -----------------------------------------------------------------------
void DrawString(int x, int y, char *string, unsigned short colour){
	int current_character;	// select character in string
	int row, column; // row and column of character pixel array 

	// Loops through each character in the string
	for(current_character = 0; current_character < strlen(string); current_character++) {
		int character_offset = y-((current_character)*12); // character offset for spaceing for larger characters

		// Checks if pixel in row and column from BF_fontMap is on and then Prints each character pixel by pixel
		for(row = 0; row < 5; row++) {
			for(column = 0; column < 7; column++) {
				// Draws each pixel a a 2x2 square on display to double character size
				if((BF_fontMap[string[current_character] - ' '][4-row] >> column) & 1) {
					LT24_drawPixel(colour, x+(column*2), character_offset+(row*2));
					LT24_drawPixel(colour, x+(column*2)+1, character_offset+(row*2));
					LT24_drawPixel(colour, x+(column*2), character_offset+(row*2)+1);
					LT24_drawPixel(colour, x+(column*2)+1, character_offset+(row*2)+1);
				}
			}
		}
	}
}

void TestDrawString(void){
	char *alphabet[88] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
						   "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", 
						   "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", 
						   "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", 
						   "u", "v", "w", "x", "y", "z", "!", "#", "$", "%", "&", "("," )", "*",
						   "+", ",", "-", "_", ".", "/", "?", "@", ">", "<", "=," ";", ":," "{", 
						   "}", "[", "]", "~"};

	int i;

	// loop through array and print to LCD
	for (i = 0; i < 88; i++) {
		LT24_clearDisplay(LT24_BLACK);
		DrawString(150, 200, alphabet[i], LT24_RED);
		usleep(200000);
	}
}

// Reference: Code modified from Dr Craig Evans N5110.h library
// https://os.mbed.com/users/eencae/code/N5110/docs/tip/N5110_8h_source.html
void DrawLine(int x0, int y0, int x1, int y1, unsigned int const type, unsigned short colour){
	// Note that the ranges can be negative so we have to turn the input values
    // into signed integers first
    int const y_range = y1 - y0;
    int const x_range = x1 - x0;
	unsigned int x;
	unsigned int y;

	// if dotted line, set step to 2, else step is 1
    unsigned int const step = (type==2) ? 2:1;
 
    // make sure we loop over the largest range to get the most pixels on the display
    // for instance, if drawing a vertical line (x_range = 0), we need to loop down the y pixels
    // or else we'll only end up with 1 pixel in the x column
    if ( abs(x_range) > abs(y_range) ) {
 
        // ensure we loop from smallest to largest or else for-loop won't run as expected
        unsigned int const start = x_range > 0 ? x0:x1;
        unsigned int const stop =  x_range > 0 ? x1:x0;
 
        // loop between x pixels
        for (x = start; x<= stop ; x+=step) {
            // do linear interpolation
            int dx = x - x0;
            unsigned int const y = y0 + y_range * dx / x_range;
 
            // If the line type is '0', this will clear the pixel
            // If it is '1' or '2', the pixel will be set
            LT24_drawPixel(colour, x, y);
        }
    } else {
 
        // ensure we loop from smallest to largest or else for-loop won't run as expected
        unsigned int const start = y_range > 0 ? y0:y1;
        unsigned int const stop =  y_range > 0 ? y1:y0;
 
        for (y = start; y<= stop ; y+=step) {
            // do linear interpolation
            int const dy = y - y0;
            unsigned int const x = x0 + x_range * dy / y_range;
 
            // If the line type is '0', this will clear the pixel
            // If it is '1' or '2', the pixel will be set
            LT24_drawPixel(colour, x, y);
        }
    }
}

// Reference: Code modified from Dr Craig Evans N5110.h library
// https://os.mbed.com/users/eencae/code/N5110/docs/tip/N5110_8h_source.html
void DrawRectangle(int x0, int y0, int width, int height, FillType const fill, unsigned short colour){
	if (fill == FILL_TRANSPARENT) { // transparent, just outline
        DrawLine(x0,y0,x0+(width-1),y0,1,colour);  // top
        DrawLine(x0,y0+(height-1),x0+(width-1),y0+(height-1),1,colour);  // bottom
        DrawLine(x0,y0,x0,y0+(height-1),1,colour);  // left
        DrawLine(x0+(width-1),y0,x0+(width-1),y0+(height-1),1,colour);  // right
    } else { // filled rectangle
        int type = (fill==FILL_BLACK) ? 1:0;  // black or white fill
		int y;
		for (y = y0; y<y0+height; y++) {  // loop through rows of rectangle
            DrawLine(x0,y,x0+(width-1),y,type,colour);  // draw line across screen
        }
    }
}

// Reference: Code modified from Dr Craig Evans N5110.h library
// https://os.mbed.com/users/eencae/code/N5110/docs/tip/N5110_8h_source.html
void DrawCircle(int x0, int y0, int radius, FillType const fill, unsigned short colour){
	// from http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
    int x = radius;
    int y = 0;
    int radiusError = 1-x;
 
    while(x >= y) {
 
        // if transparent, just draw outline
        if (fill == FILL_TRANSPARENT) {
            LT24_drawPixel(colour, x + x0,  y + y0);
            LT24_drawPixel(colour,-x + x0,  y + y0);
            LT24_drawPixel(colour, y + x0,  x + y0);
            LT24_drawPixel(colour,-y + x0,  x + y0);
            LT24_drawPixel(colour,-y + x0, -x + y0);
            LT24_drawPixel(colour, y + x0, -x + y0);
            LT24_drawPixel(colour, x + x0, -y + y0);
            LT24_drawPixel(colour,-x + x0, -y + y0);
        } else {  // drawing filled circle, so draw lines between points at same y value
 
            int type = (fill==FILL_BLACK) ? 1:0;  // black or white fill
 
            DrawLine(x+x0,y+y0,-x+x0,y+y0,type,colour);
            DrawLine(y+x0,x+y0,-y+x0,x+y0,type,colour);
            DrawLine(y+x0,-x+y0,-y+x0,-x+y0,type,colour);
            DrawLine(x+x0,-y+y0,-x+x0,-y+y0,type,colour);
        }
 
        y++;
        if (radiusError<0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}

