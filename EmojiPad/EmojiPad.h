//*****************************************************************************
//* 		EmojiPad Arduino Sketch Header                                        *    
//*****************************************************************************
//
//      Creates a USB HID Device using the V-USB Library from Objective 
//      Development. This is then used to implement a 16-key keyboard, with 
//      keys mapped to different emoticons. 
//
//      Author: Duncan Lowder
//      E-Mail: duncan.lowder@gmail.com
//      Date: 2015-04-07
//      License: GNU GPL v2
//
//      Copyright (C) 2015  Duncan Lowder
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <http://www.gnu.org/licenses/>.
//*****************************************************************************
#ifndef __EmojiPad_h__
#define __EmojiPad_h__


// --- Global Constants -------------------------------------------------------

// Pin Declarations
#define COL0 3
#define COL1 5
#define COL2 6
#define COL3 12
#define ROW0 8
#define ROW1 9
#define ROW2 10
#define ROW3 11
#define LED  13

#define PIN_BUTTON 	7 // the button is attached to pin 7

// Button States 
#define IDLE 		0
#define PRESSED		1
#define HOLD		2
#define RELEASED	4

// Emoticon Keyboard Key Constants
#define EB_KEY0 	1
#define EB_KEY1 	2
#define EB_KEY2 	3
#define EB_KEY3 	4
#define EB_KEY4 	5
#define EB_KEY5 	6
#define EB_KEY6 	7
#define EB_KEY7 	8
#define EB_KEY8 	9
#define EB_KEY9 	10 
#define EB_KEY10	11
#define EB_KEY11 	12 
#define EB_KEY12 	13
#define EB_KEY13 	14
#define EB_KEY14 	15
#define EB_KEY15 	16

// Pin State Definitions
#define FLOAT 	2
#define HIGH 	1
#define LOW  	0

 
// Keypad Constants
const uint8_t ROWS = 4;
const uint8_t COLS = 4;
const uint8_t MAX_KEYS_ACTIVE = 6;

// --- STRUCTURE DEFINITIONS --------------------------------------------------

// Key Structure
// This is used to keep track of the current state and hold time of an active 
// key
struct key {
	uint32_t start_time;	// Timestamp of when the key was initially pressed
	uint8_t key_value;		// Value associated with the pressed key
	uint8_t key_state;		// Current state of the key
};


// --- GLOBAL VARIABLE DEFINITIONS --------------------------------------------

// Column and Row Pin Definitions
uint8_t colPins[COLS] = {COL0, COL1, COL2, COL3};
uint8_t rowPins[ROWS] = {ROW0, ROW1, ROW2, ROW3};

// Key Value Map
// This contains the map of the keypad matrix and it's associated values. This
// list is used to assign the value of a currently active key. 
uint8_t keys[ROWS][COLS] = {
	{ EB_KEY0,  EB_KEY1,  EB_KEY2,  EB_KEY3},
	{ EB_KEY4,  EB_KEY5,  EB_KEY6,  EB_KEY7},
	{ EB_KEY8,  EB_KEY9, EB_KEY10, EB_KEY11},
	{EB_KEY12, EB_KEY13, EB_KEY14, EB_KEY15}
};

// Bitmap for determining active keys
uint8_t bit_map[ROWS];

// List containing the active keys state information
key keys_active[MAX_KEYS_ACTIVE];

uint32_t start_time;
uint32_t debounce_time = 10;
uint32_t hold_time = 250;

uint32_t prevTime;
uint32_t elapsedTimeMs;
int lastState = LOW; // LOW is equivalent to 0

#endif // __EmojiPad_h__