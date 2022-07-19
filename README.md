# ELEC5620M Mini-Project Repository -  Pong

Embedded C Project of the arcade game Pong for the DE1-SoC board

The arcade game Pong has been programmed in C for the DE1-SoC board. The game uses most of the DE1-SoC peripherals and each feature has been validated during the development process. An AI provides an opponent to play to against and the game can be scaled to work for different screen resolutions. The program meets all the minimum and further requirements by having fully generalised code


The following files are provided:

| File | Purpose |
| ---  | --- |
| `main.c` | Main top level file for a Pong which uses the HPS timer and IRQ interupts to function |
| `.project` | DS-5 project configuration file  |
| `.cproject` | C project configuration file with debugger settings |
| `Interrupts.h` | Interrupts header file containing interrupt configuration and ISR declarations along with the state machine for the Pong  |
| `Interrupts.c` | Interrupts c file containing interrupt configuration and ISR definitions along with the state machine for the Pong |
| `SevenSegDisplay.h` | SevenSegmentDisplay header file to control seven segment displays  |
| `SevenSegDisplay.c` | SevenSegmentDisplay c file to control seven segment displays |
| `Sound.h` | Sound header file for paddle and ball blips  |
| `Sound.c` | Sound c file for paddle and ball blips |
| `PrivateTimer.h` | Private Timer header file for triggering events based on ELEC5620M - Unit 2.2 - HPS_PrivateTimer.c code |
| `PrivateTimer.c` | Private Timer C file for triggering events based on ELEC5620M - Unit 2.2 - HPS_PrivateTimer.c code |
| `LCDEngine.h` | LCDEngine header file driver to produce different shapes and text on LCD  |
| `LCDEngine.c` | LCDEngine c file driver to produce different shapes and text on LCD |
| `Pong.h` | Image code for intro loading picture  |
| `Pong.c` | RGB565C-Array image code for intro loading picture |
| `GameEngine.h` | Game engine header file to run the different mechanics of the game, including physics and control  |
| `GameEngine.c` | Game engine c file to run the different mechanics of the game, including physics and control |



Pong High-Level System Block Diagram

![alt text](https://github.com/leeds-embedded-systems/ELEC5620M-Mini-Project-evanso931/blob/main/Pictures/Pong%20System%20Block%20Diagram.png?raw=true)

Pong File Hierarchy Block Diagram

![alt text](https://github.com/leeds-embedded-systems/ELEC5620M-Mini-Project-evanso931/blob/main/Pictures/Pong%20File%20Hierarchy%20Block%20Diagram.png?raw=true)

Pong State Machine

![alt text](https://github.com/leeds-embedded-systems/ELEC5620M-Mini-Project-evanso931/blob/main/Pictures/Pong%20State%20Machine.png?raw=true)
