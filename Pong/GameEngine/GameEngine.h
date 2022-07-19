/* GameEngine.h
 *
 * Created on: 6 April 2022
 *
 * Author: Benjamin Evans
 *
 * Description: Game engine header file to run the different mechanics of the game, including physics and control
 * Reference: Sound Code from ELEC5620M - Unit 3.1 Lab Task 1 - 3-1-ToneGenerator/main.c
 */

#ifndef GAMEENGINE_GAMEENGINE_H_
#define GAMEENGINE_GAMEENGINE_H_

#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include <math.h>
#include <stdlib.h>
#include "../LCDEngine/LCDEngine.h"
#include "../PrivateTimer/PrivateTimer.h"
#include "../SevenSegDisplay/SevenSegDisplay.h"
#include "DE1SoC_WM8731/DE1SoC_WM8731.h"
#include "../Sound/Sound.h"

// Game peramters definitions for to easily scale game to different resolutions 
// Round resolution to nearest zero
#define HIGHT_RESOLUTION 240
#define WIDTH_RESOLUTION 320


// GameEngine Declarations ------------------------------------------------------------
/**
 * RunGame
 *
 * The main game function that calls the different functions of the games at different 
 * rates depeding on which Private timer is used=
 * 
 */
void RunGame(void);

/**
 * MenuScreen
 *
 * Draws Menu screen, which displays play game
 * 
 */
void MenuScreen(void);

/**
 * PongFSM
 *
 * Main FSM that handles the software flow control
 * 
 */
void PongFSM(void);

/**
 * DrawPaddles
 *
 * Draws the two paddels on the display in their x and y positions and at the scaled
 * size to the lcd
 * 
 */
void DrawPaddles(void);

/**
 * InitItems
 *
 * Initialises Paddle and ball starting positions
 * 
 */
void InitItems(void);

/**
 * MoveRightPaddle
 *
 * Moves the right paddle up and down depending on key presses one and two
 * 
 */
void MoveRightPaddle(void);

/**
 * MoveLeftPaddle
 *
 * Moves the Left paddle up and down depending input direction 
 * 
 * Inputs:
 * 		Direction:      Direction of paddle movement, false = downwards, true = upwards
 * 
 */
void MoveLeftPaddle(bool Direction);

/**
 * DrawBall
 *
 * Draws the ball on the display in its x and y positions and at the scaled
 * size to the lcd
 * 
 */
void DrawBall(void);

/**
 * MoveBall
 *
 * Move the ball around the display by changing its velocity depending on 
 * collision with the paddles or top and bottom walls
 * 
 */
void MoveBall(void);

/**
 * RightPaddleCollision
 *
 * Change ball reflection angle depending on if it hits the top or bottom of
 * the paddle. The angle of reflection is increased the further away from 
 * the middle of the paddle the ball was when it collided
 * 
 */
void RightPaddleCollision(void);

/**
 * LeftPaddleCollision
 *
 * Change ball reflection angle depending on if it hits the top or bottom of
 * the paddle. The angle of reflection is increased the further away from 
 * the middle of the paddle the ball was when it collided
 * 
 */
void LeftPaddleCollision(void);

/**
 * LeftPaddleAI
 *
 * simple AI that Controls the movement of the left paddle
 * 
 */
void LeftPaddleAI(void);

/**
 * ResetBall
 *
 * Respawns the ball with a set velocity values on press of key 2
 * Used for testing purposeses 
 * 
 */
void ResetBall(void);

/**
 * BallScore
 *
 * Respawns the ball with in random direction towards conceding point player
 * 
 * Returns:
 * 		EndGame:      Game End flag for FSM, false = still playing, true = Game over
 * 
 */
bool BallScore(void);

/**
 * DrawScore
 *
 * Draws the numbers on the screen for each sides score board 
 * 
 * Inputs:
 * 		Player:      Lef or right paddle, false = left paddle, true = Righht paddle
 * 
 */
void DrawScore(bool Player);

/**
 * DrawHUD
 *
 * Draws the Heads up Display for the game 
 * Draws a dotted line in the middle of screen to define sides and the upper and lower walls
 * Draws the score board for each side
 * 
 */
void DrawHUD(void);

#endif
