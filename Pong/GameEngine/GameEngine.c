/* GameEngine.c
 *
 * Created on: 6 April 2022
 *
 * Author: Benjamin Evans
 *
 * Description: Game engine c file to run the different mechanics of the game, including physics and control
 * 
 */

#include "GameEngine.h"


// Global variables -------------------------------------------------------------------------------------
unsigned int LeftPaddleXPosition, LeftPaddleYPosition, RightPaddleXPosition, RightPaddleYPosition = 0;
unsigned int BallXPosition, BallYPosition = 0;
int RightPaddleScore, LeftPaddleScore = 0;
int BallXVelocity = 1;
int BallYVelocity = 4;
int VelocityMultiplier = 1;
unsigned int FSMState = 0;

// Peripheral base addresses.
volatile unsigned int *key_ptr = (unsigned int *)0xFF200050;

// Function Definitions GameEngine -----------------------------------------------------------------------
void RunGame(void){

    // Timer Controlls Movement Speed of Paddles and balls
    if (TriggerTimer()) {
        
        MoveBall();
        DrawHUD();
    }

    // Paddle move more frequently in smaller steps, to avoid missing hit box
    if (HalfTriggerTimer()){
        //MoveLeftPaddle(); Testing
        MoveRightPaddle();
        LeftPaddleAI();
    }

    DrawPaddles();
    DrawBall();
}

void MenuScreen(void){
    DrawString(HIGHT_RESOLUTION / 2, WIDTH_RESOLUTION/2 + WIDTH_RESOLUTION/10, "PLAY GAME", LT24_WHITE);
}

void PongFSM(void){
    // Top Level Game FSM
    // Menu Screen
    if (FSMState == 0) {
        if (*key_ptr & 0x4){
            FSMState = 1;
            LT24_clearDisplay(LT24_BLACK);
            InitItems();  
        }else{
            MenuScreen();
        }

    // Ingame Screen
    }else if (FSMState == 1) {	
        if (BallScore()) {
            usleep(3000000); // Display Win or lose for 3 seconds
            LT24_clearDisplay(LT24_BLACK);
            FSMState = 0;
        }else if (*key_ptr & 0x8){
            FSMState = 0;
            LT24_clearDisplay(LT24_BLACK);
        }else {
            RunGame();
        }
    } 
}

void DrawPaddles(void){
    DrawRectangle(LeftPaddleXPosition, LeftPaddleYPosition, HIGHT_RESOLUTION/10, WIDTH_RESOLUTION/48, FILL_BLACK, LT24_WHITE);
    DrawRectangle(RightPaddleXPosition, RightPaddleYPosition, HIGHT_RESOLUTION/10, WIDTH_RESOLUTION/48, FILL_BLACK, LT24_WHITE);
}

void InitItems(void){
    // Reset Game global Veribales
    LeftPaddleXPosition = (HIGHT_RESOLUTION/2) - (HIGHT_RESOLUTION / 20);
    LeftPaddleYPosition = WIDTH_RESOLUTION - (WIDTH_RESOLUTION / 5);
    RightPaddleXPosition = (HIGHT_RESOLUTION/2) - (HIGHT_RESOLUTION / 20);
    RightPaddleYPosition = WIDTH_RESOLUTION/5;
    BallXPosition = HIGHT_RESOLUTION/2;
    BallYPosition = WIDTH_RESOLUTION/2;
    RightPaddleScore = 0;
    LeftPaddleScore = 0;
    BallXVelocity = 1;
    BallYVelocity = 4;
    VelocityMultiplier = 1;

    // Draw zero score board
    DrawScore(false);
    DrawScore(true);
}

void MoveRightPaddle(void){
    // Moves paddle downdowards and stops it going off bottom of screen
    if(*key_ptr & 0x1 && RightPaddleXPosition < (HIGHT_RESOLUTION - HIGHT_RESOLUTION/10)) {
        RightPaddleXPosition+=HIGHT_RESOLUTION/80;

        // Delete old paddle drawing
        DrawRectangle(RightPaddleXPosition-HIGHT_RESOLUTION/80, RightPaddleYPosition, HIGHT_RESOLUTION/10, WIDTH_RESOLUTION/48, FILL_BLACK, LT24_BLACK);

    // Moves paddle upwards stops it going off top of screen
    }else if(*key_ptr & 0x2 && RightPaddleXPosition > HIGHT_RESOLUTION/4) {
        RightPaddleXPosition-=HIGHT_RESOLUTION/80;

        // Delete old paddle drawing
        DrawRectangle(RightPaddleXPosition+HIGHT_RESOLUTION/80, RightPaddleYPosition, HIGHT_RESOLUTION/10, WIDTH_RESOLUTION/48, FILL_BLACK, LT24_BLACK);
    }
}

void MoveLeftPaddle(bool Direction){
    // Moves paddle downwards and stops it going off bottom of screen
    if(!Direction && LeftPaddleXPosition < (HIGHT_RESOLUTION - HIGHT_RESOLUTION/10)) {
        LeftPaddleXPosition+=HIGHT_RESOLUTION/80;

        // Delete old paddle drawing
        DrawRectangle(LeftPaddleXPosition-HIGHT_RESOLUTION/80, LeftPaddleYPosition, HIGHT_RESOLUTION/10, WIDTH_RESOLUTION/48, FILL_BLACK, LT24_BLACK);

    // Moves paddle upwards and stops it going off top of screen
    }else if(Direction && LeftPaddleXPosition > HIGHT_RESOLUTION/4) {
        LeftPaddleXPosition-=HIGHT_RESOLUTION/80;

        // Delete old paddle drawing
        DrawRectangle(LeftPaddleXPosition+HIGHT_RESOLUTION/80, LeftPaddleYPosition, HIGHT_RESOLUTION/10, WIDTH_RESOLUTION/48, FILL_BLACK, LT24_BLACK);
    }
}

void DrawBall(void){
    DrawRectangle(BallXPosition, BallYPosition, HIGHT_RESOLUTION/60, HIGHT_RESOLUTION/60, FILL_BLACK, LT24_WHITE);
}

void MoveBall(void){
    // Delete old ball drawing
    DrawCircle(BallXPosition, BallYPosition, HIGHT_RESOLUTION/60, FILL_BLACK, LT24_BLACK);
    
    // Checks if ball hit top or bottom wall and reverses X velocity if it does
    // top wall
    if (BallXPosition > (HIGHT_RESOLUTION - HIGHT_RESOLUTION/20)) {
        BallXVelocity = -HIGHT_RESOLUTION/30;
        PlayBlip();

    // bottom wall
    }else if (BallXPosition < HIGHT_RESOLUTION/4) {
        BallXVelocity = HIGHT_RESOLUTION/30;
        PlayBlip();
    }

    // Checks Right and Left Paddle Collision
    // Right
    if (BallXPosition + HIGHT_RESOLUTION/60 > RightPaddleXPosition && 
    BallXPosition < (RightPaddleXPosition + HIGHT_RESOLUTION/10) && 
    BallYPosition < RightPaddleYPosition + WIDTH_RESOLUTION/30 &&
    BallYPosition > RightPaddleYPosition) {

        RightPaddleCollision();
        PlayBlip();

        // Left
    }else if (BallXPosition + HIGHT_RESOLUTION/60 > LeftPaddleXPosition && 
    BallXPosition < (LeftPaddleXPosition + HIGHT_RESOLUTION/10) && 
    BallYPosition + HIGHT_RESOLUTION/60 > LeftPaddleYPosition  &&
    BallYPosition + HIGHT_RESOLUTION/60 < LeftPaddleYPosition + WIDTH_RESOLUTION/30) {

        LeftPaddleCollision();
        PlayBlip();
    }

    // Update Ball position using velocity
    BallXPosition += BallXVelocity * VelocityMultiplier;
    BallYPosition += BallYVelocity * VelocityMultiplier;

    //ResetBall(); For testing
}

void RightPaddleCollision(void){
    unsigned int i = 0;
    unsigned int PreviousPaddleXSectionRight = 0;
    int VelocityXChangePaddle = 0;

    BallYVelocity = HIGHT_RESOLUTION/30;
    // Reset ball x velocity so leavease at same speed no matter whether it hit top or botton
    BallXVelocity = 0;

    //if the middle ball hits top side of paddle
    if (BallXPosition + HIGHT_RESOLUTION / 120 <= RightPaddleXPosition + HIGHT_RESOLUTION / 20)
    {
        VelocityXChangePaddle = -1;
        PreviousPaddleXSectionRight = RightPaddleXPosition + HIGHT_RESOLUTION / 10;
        // Breaks top part of paddle into 4 sections, increces reflection angle
        // the higher that ball collides with the paddle
        for (i = RightPaddleXPosition + HIGHT_RESOLUTION / 10 - HIGHT_RESOLUTION / 80;
            i >= RightPaddleXPosition; i -= HIGHT_RESOLUTION / 80) {

            // checks if ball collison is between certain section of top of paddle
            if (BallXPosition + HIGHT_RESOLUTION / 60 <= PreviousPaddleXSectionRight && BallXPosition + HIGHT_RESOLUTION / 60 > i) {
                
                // Changes angle of reflection angle depending on section of paddle hit
                BallXVelocity += VelocityXChangePaddle;
            }
            VelocityXChangePaddle--;
            PreviousPaddleXSectionRight = i;
        }
    }


    // if the middle ball hits bottom side of paddle
    if (BallXPosition + HIGHT_RESOLUTION/120 >  RightPaddleXPosition + HIGHT_RESOLUTION/20) {
        VelocityXChangePaddle = 1;
        PreviousPaddleXSectionRight = RightPaddleXPosition;
        // Breaks bottom part of paddle into 4 sections, increces reflection angle
        // the lower that ball collides with the paddle
        for (i = RightPaddleXPosition + HIGHT_RESOLUTION/20 + HIGHT_RESOLUTION/80;
        i <= RightPaddleXPosition + HIGHT_RESOLUTION/10; i += HIGHT_RESOLUTION/80) {

            // checks if ball collison is between certain section of bottom of paddle
            if (BallXPosition >= PreviousPaddleXSectionRight && BallXPosition < i) {

                // Changes angle of reflection angle depending on section of paddle hit
                BallXVelocity += VelocityXChangePaddle;
            }
            VelocityXChangePaddle++;
            PreviousPaddleXSectionRight = i;
        }
    }
}

void LeftPaddleCollision(void){
    unsigned int i = 0;
    unsigned int PreviousPaddleXSectionRight = 0;
    int VelocityXChangePaddle = 0;

    BallYVelocity = -HIGHT_RESOLUTION/30;
    // Reset ball x velocity so leavease at same speed no matter whether it hit top or botton
    BallXVelocity = 0;

    //if the middle ball hits top side of paddle
    if (BallXPosition + HIGHT_RESOLUTION / 120 <= LeftPaddleXPosition + HIGHT_RESOLUTION / 20)
    {
        VelocityXChangePaddle = -1;
        PreviousPaddleXSectionRight = LeftPaddleXPosition + HIGHT_RESOLUTION / 10;
        // Breaks top part of paddle into 4 sections, increces reflection angle
        // the higher that ball collides with the paddle
        for (i = LeftPaddleXPosition + HIGHT_RESOLUTION / 10 - HIGHT_RESOLUTION / 80;
            i >= LeftPaddleXPosition; i -= HIGHT_RESOLUTION / 80) {

            // checks if ball collison is between certain section of top of paddle
            if (BallXPosition + HIGHT_RESOLUTION / 60 <= PreviousPaddleXSectionRight && BallXPosition + HIGHT_RESOLUTION / 60 > i) {
                
                // Changes angle of reflection angle depending on section of paddle hit
                BallXVelocity += VelocityXChangePaddle;
            }
            VelocityXChangePaddle--;
            PreviousPaddleXSectionRight = i;
        }
    }


    // if the middle ball hits bottom side of paddle
    if (BallXPosition + HIGHT_RESOLUTION/120 > LeftPaddleXPosition + HIGHT_RESOLUTION/20) {
        VelocityXChangePaddle = 1;
        PreviousPaddleXSectionRight = LeftPaddleXPosition;
        // Breaks bottom part of paddle into 4 sections, increces reflection angle
        // the lower that ball collides with the paddle
        for (i = LeftPaddleXPosition + HIGHT_RESOLUTION/20 + HIGHT_RESOLUTION/80;
        i <= LeftPaddleXPosition + HIGHT_RESOLUTION/10; i += HIGHT_RESOLUTION/80) {

            // checks if ball collison is between certain section of bottom of paddle
            if (BallXPosition >= PreviousPaddleXSectionRight && BallXPosition < i) {

                // Changes angle of reflection angle depending on section of paddle hit
                BallXVelocity += VelocityXChangePaddle;
            }
            VelocityXChangePaddle++;
            PreviousPaddleXSectionRight = i;
        }
    }
}

void LeftPaddleAI(void){
    // Check if ball moving towards the left paddle 
    if (BallYVelocity > 0) {
        
        // Move for ball bellow than middle of the paddle
        if (BallXPosition > LeftPaddleXPosition + HIGHT_RESOLUTION/20) {
            MoveLeftPaddle(false);

        // Move for ball higher than middle of paddle
        }else if (BallXPosition <= LeftPaddleXPosition + HIGHT_RESOLUTION/20){
            MoveLeftPaddle(true);
        }
    }
}

void ResetBall(void){
    if(*key_ptr & 0x4) {
        BallXPosition = HIGHT_RESOLUTION/2 - 20;
        BallYPosition = WIDTH_RESOLUTION/2;
        BallXVelocity = 1;
        BallYVelocity = 4;
    }
}

bool BallScore(void){
    // Random number to change x direction and angle of next spawned ball
    int RandNumber = rand()%((3+1)-0);

    // Display Win
    if (RightPaddleScore == 11){
        LT24_clearDisplay(LT24_BLACK);
        DrawString(HIGHT_RESOLUTION / 2, WIDTH_RESOLUTION/2 + WIDTH_RESOLUTION/10, "YOU WIN", LT24_WHITE);
        return true;

    // Display lose
    }else if(LeftPaddleScore == 11){
        LT24_clearDisplay(LT24_BLACK);
        DrawString(HIGHT_RESOLUTION / 2, WIDTH_RESOLUTION/2 + WIDTH_RESOLUTION/10, "YOU LOSE", LT24_WHITE);
        return true;

    // Right player score
    }else if (BallYPosition > (WIDTH_RESOLUTION - WIDTH_RESOLUTION/16)) {
        BallXPosition = HIGHT_RESOLUTION/2 + 20;
        BallYPosition = WIDTH_RESOLUTION/2;
        BallXVelocity = 1-RandNumber;
        BallYVelocity = 4;
        RightPaddleScore++;
        DrawScore(true);

    // Left Player Score
    }else if (BallYPosition < WIDTH_RESOLUTION/16) {
        BallXPosition = HIGHT_RESOLUTION/2 + 20;
        BallYPosition = WIDTH_RESOLUTION/2;
        BallXVelocity = 1-RandNumber;
        BallYVelocity = -4;
        LeftPaddleScore++;
        DrawScore(false);  
    }

    return false;
}

void DrawScore(bool Player){
    char *score[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    
    // Draws the numbers on the screen for each sides score board 
    if (Player) {
        // Right Paddle
        DrawRectangle(HIGHT_RESOLUTION / 20, WIDTH_RESOLUTION / 5, HIGHT_RESOLUTION / 4, WIDTH_RESOLUTION / 8, FILL_BLACK, LT24_BLACK);
        DrawString(HIGHT_RESOLUTION / 20, WIDTH_RESOLUTION/5, score[RightPaddleScore], LT24_WHITE);
        SevenSeg_SetDoubleDec(0, RightPaddleScore);
    } else if (!Player) {
        // Left Paddle
        DrawRectangle(HIGHT_RESOLUTION / 20, WIDTH_RESOLUTION - (WIDTH_RESOLUTION / 5), HIGHT_RESOLUTION / 4, WIDTH_RESOLUTION / 8, FILL_BLACK, LT24_BLACK);
        DrawString(HIGHT_RESOLUTION / 20, WIDTH_RESOLUTION - (WIDTH_RESOLUTION / 5), score[LeftPaddleScore], LT24_WHITE);
        SevenSeg_SetDoubleDec(4, LeftPaddleScore);
    }
}

void DrawHUD(void){
    // Draw Dotted line down the display
    int i = 0;
    for (i = HIGHT_RESOLUTION / 4; i < HIGHT_RESOLUTION; i += HIGHT_RESOLUTION/20)  {
        DrawRectangle(i, WIDTH_RESOLUTION / 2, HIGHT_RESOLUTION/60, WIDTH_RESOLUTION/90, FILL_BLACK, LT24_WHITE);
    }
    
    // Displays score board for each player
    BallScore();
}
