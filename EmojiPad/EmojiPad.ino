//*****************************************************************************
//*     EmojiPad Arduino Sketch                                               *    
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
//
//*****************************************************************************

#include <UsbKeyboard.h>
#include "EmojiPad.h"

// --- DEBUG MACROS -----------------------------------------------------------
// These macros are used to blink the LED attached to D13. This allows for 
// different sections of code to use the LED and not have to manually add and 
// remove code to blink the LED. 

// #define TIMER2_COMPA_DEBUG

// --- FUNCTION DEFINITIONS ---------------------------------------------------

//-----------------------------------------------------------------------------
//
//  setup
//
//  Description:
//      This is the main setup function for Arduino. This takes care of all of 
//      the initialization required for the operation of the EmojiPad. This 
//      includes:
//          - Setting up the GPIO for INPUT or OUTPUT
//          - Initializing TIMER2 to be used as the millis() timer
//          - Disable TIMER0 interrupts for the V-USB Library
//          - Force USB re-enumeration by disconnecting and reconnecting the 
//            device.
//
//  Entry:
//      None
//
//  Exit:
//      None
//
//-----------------------------------------------------------------------------
void setup(){
    // Serial.begin(9600);

    // Setup LED as output√
    pinMode(LED, OUTPUT);

    // --- TIMER 2 setup ------------------------------------------------------
    initTimer2();

    // --- USB setup ----------------------------------------------------------
    // Disable timer0 since it can mess with the USB timing. Note that
    // this means some functions such as delay() will no longer work.
    TIMSK0 &= !(1<TOIE0);

    // Clear interrupts while performing time-critical operations
    cli();

    // Force re-enumeration so the host will detect us
    usbDeviceDisconnect();
    delayMs(250);
    usbDeviceConnect();

    // Set interrupts again
    sei();

}


//-----------------------------------------------------------------------------
//
//  loop
//
//  Description:
//      This is the main execution loop for the EmojiPad sketch. This controls
//      the reading of the keypad and the sending of USB keystrokes.
//
//  Entry:
//      None
//  
//  Exit:
//      None
//
//-----------------------------------------------------------------------------
void loop(){
    // Local Variables
    uint8_t key = getKey();

    // update USB device state
    UsbKeyboard.update();

    // Toggle LED every second
    if((key != -1) && (lastState == LOW))
    {
        digitalWrite(LED, 1);

        // emoticonBtnMap(key);
        mediaPlayerBtnMap(key);

        delay(20);

        digitalWrite(LED, 0);
        
    }

}


//--- Emoticon Functions ------------------------------------------------------
// These are simple keyboard based emoticons, none of them require unicode 
// characters. 

// :)
void smileyFace() {
    UsbKeyboard.sendKeyStroke(KEY_COLON, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_0, MOD_SHIFT_LEFT);
}

// :(
void sadFace() {
    UsbKeyboard.sendKeyStroke(KEY_COLON, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_9, MOD_SHIFT_LEFT);

}

// ;(
void cryingFace() {
    UsbKeyboard.sendKeyStroke(KEY_COLON);
    UsbKeyboard.sendKeyStroke(KEY_9, MOD_SHIFT_LEFT);
}

// ('_')
void seriousFace() {
    UsbKeyboard.sendKeyStroke(KEY_9, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_QUOTE);
    UsbKeyboard.sendKeyStroke(KEY_DASH, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_QUOTE);
    UsbKeyboard.sendKeyStroke(KEY_0, MOD_SHIFT_LEFT);
}

// (~_^)
void crazyFace() {
    UsbKeyboard.sendKeyStroke(KEY_9, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_TILDE, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_DASH, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_6, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_0, MOD_SHIFT_LEFT);
}

// >_>
void skepticalFace() {
    UsbKeyboard.sendKeyStroke(KEY_PERIOD, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_DASH, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_PERIOD, MOD_SHIFT_LEFT);
}

// (*^_^*) 
void shyFace() {
    UsbKeyboard.sendKeyStroke(KEY_9, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_8, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_6, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_DASH, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_6, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_8, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_0, MOD_SHIFT_LEFT);
}

// =D
void bigSmileFace() {
    UsbKeyboard.sendKeyStroke(KEY_EQUAL);
    UsbKeyboard.sendKeyStroke(KEY_D, MOD_SHIFT_LEFT);
}

// >_<
void angryFace() {
    UsbKeyboard.sendKeyStroke(KEY_PERIOD, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_DASH, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_COMMA, MOD_SHIFT_LEFT);
}

// =^.^=
void cat() {
    UsbKeyboard.sendKeyStroke(KEY_EQUAL);
    UsbKeyboard.sendKeyStroke(KEY_6, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_PERIOD);
    UsbKeyboard.sendKeyStroke(KEY_6, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_EQUAL);
}

// (//_^)
void emohFace() {
    UsbKeyboard.sendKeyStroke(KEY_9, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_FORWARD_SLASH);
    UsbKeyboard.sendKeyStroke(KEY_FORWARD_SLASH);
    UsbKeyboard.sendKeyStroke(KEY_DASH, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_6, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_0, MOD_SHIFT_LEFT);
}

// <:3)~
void mouse() {
    UsbKeyboard.sendKeyStroke(KEY_COMMA, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_COLON, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_3);
    UsbKeyboard.sendKeyStroke(KEY_0, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_TILDE, MOD_SHIFT_LEFT);
}


// --- BUTTON MAPS ------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//  EmoticonButtonMap
//
//  Description:
//      This function contains that switch statement used to map the button 
//      presses to standard text emoticons. 
//
//  Entry:
//      key - Current key that is pressed
//
//  Exit:
//      None
//
//-----------------------------------------------------------------------------
void emoticonBtnMap(uint8_t key) {
    switch(key) {
            case EB_KEY0:
                crazyFace();
                break;
            case EB_KEY1:
                skepticalFace();
                break;
            case EB_KEY2:
                smileyFace();
                break;
            case EB_KEY3:
                // Not currently supported due to hardware issue
                break;
            case EB_KEY4:
                sadFace();
                break;
            case EB_KEY5:
                cryingFace();
                break;
            case EB_KEY6:
                seriousFace();
                break;
            case EB_KEY7:
                // Not currently supported due to hardware issue
                break;
            case EB_KEY8:
                shyFace();
                break;
            case EB_KEY9:
                bigSmileFace();
                break;
            case EB_KEY10:
                angryFace();
                break;
            case EB_KEY11:
                // Not currently supported due to hardware issue
                break;
            case EB_KEY12:
                cat();
                break;
            case EB_KEY13:
                emohFace();
                break;
            case EB_KEY14:
                mouse();
                break;
            case EB_KEY15:
                // Not currently supported due to hardware issue
                break;
            default:
                break;
        }
}


//-----------------------------------------------------------------------------
//
//  mediaPlayerBtnMap
//
//  Description: 
//      This function contains the button map for the keypad to control
//      multimedia applications on the computed. The following functions are 
//      currently supported:
//          - Volume Up
//          - Volume Down
//          - Mute
//
//  Entry:
//      key - Current key that is being pressed
//
//  Exit:
//      None
//
//-----------------------------------------------------------------------------
void mediaPlayerBtnMap(uint8_t key) {
    switch(key) {
            case EB_KEY0:
                
                break;
            case EB_KEY1:
                
                break;
            case EB_KEY2:
                
                break;
            case EB_KEY3:
                // Not currently supported due to hardware issue
                break;
            case EB_KEY4:
                
                break;
            case EB_KEY5:
                
                break;
            case EB_KEY6:
                
                break;
            case EB_KEY7:
                // Not currently supported due to hardware issue
                break;
            case EB_KEY8:
                
                break;
            case EB_KEY9:
                
                break;
            case EB_KEY10:
                
                break;
            case EB_KEY11:
                // Not currently supported due to hardware issue
                break;
            case EB_KEY12:
                UsbKeyboard.sendKeyStroke(KEY_VOL_UP);
                break;
            case EB_KEY13:
                UsbKeyboard.sendKeyStroke(KEY_VOL_DOWN);
                break;
            case EB_KEY14:
                UsbKeyboard.sendKeyStroke(KEY_MUTE);
                break;
            case EB_KEY15:
                // Not currently supported due to hardware issue
                break;
            default:
                break;
        }
}

//-----------------------------------------------------------------------------
//
//  sketchupBtnMap
//
//  Description:
//      This is a button map containing hot keys for Google Sketchup
//
//  Entry:
//      key - Current key that is being pressed
//
//  Exit:
//      None
//
//-----------------------------------------------------------------------------
void sketchUpBtnMap(uint8_t key) {
    switch(key) {
            case EB_KEY0:
                
                break;
            case EB_KEY1:
                
                break;
            case EB_KEY2:
                
                break;
            case EB_KEY3:
                
                break;
            case EB_KEY4:
                
                break;
            case EB_KEY5:
                
                break;
            case EB_KEY6:
                
                break;
            case EB_KEY7:
                
                break;
            case EB_KEY8:
                
                break;
            case EB_KEY9:
                
                break;
            case EB_KEY10:
                
                break;
            case EB_KEY11:
                
                break;
            case EB_KEY12:
                
                break;
            case EB_KEY13:
                
                break;
            case EB_KEY14:
                
                break;
            case EB_KEY15:
                
                break;
            default:
                break;
        }
}


//-----------------------------------------------------------------------------
//
//  btnMapTemplate
//
//  Description:
//      This is a template for a button map. Copy this, use a descriptive name
//      for the type of button map and add ther BtnMap suffix to the function.
//      
//      Change the case statements to call a function or the button presses
//      needed to execute what you would like. 
//
//  Entry:
//      key - Current key that is being pressed
//
//  Exit:
//      None
//
//-----------------------------------------------------------------------------
// void btnMapTemplate(uint8_t key) {
//     switch(key) {
//             case EB_KEY0:
                
//                 break;
//             case EB_KEY1:
                
//                 break;
//             case EB_KEY2:
                
//                 break;
//             case EB_KEY3:
                
//                 break;
//             case EB_KEY4:
                
//                 break;
//             case EB_KEY5:
                
//                 break;
//             case EB_KEY6:
                
//                 break;
//             case EB_KEY7:
                
//                 break;
//             case EB_KEY8:
                
//                 break;
//             case EB_KEY9:
                
//                 break;
//             case EB_KEY10:
                
//                 break;
//             case EB_KEY11:
                
//                 break;
//             case EB_KEY12:
                
//                 break;
//             case EB_KEY13:
                
//                 break;
//             case EB_KEY14:
                
//                 break;
//             case EB_KEY15:
                
//                 break;
//             default:
//                 break;
//         }
// }

// --- SUPPORT FUNCTIONS ------------------------------------------------------

//-----------------------------------------------------------------------------
//
//  delayMs
//
//  Description:
//      This function replaces the default delay function with Arduino. This is
//      due to TIMER0 being disabled to allow for the V-USB library to function 
//      correctly.
//
//  Entry:
//      ms: Number of milliseconds to wait
//
//  Exit:
//      None
//  
//-----------------------------------------------------------------------------
void delayMs(unsigned int ms) {
    for( int i=0; i<ms; i++ ) {
        delayMicroseconds(1000);
    }
}

//-----------------------------------------------------------------------------
//
//  initTimer2
//
//  Description:
//      This function initializes TIMER2 COMPA to interrupt every millisecond.
//      For this to occur, a prescaler of 64 is used, and the compare match 
//      register is set to 250. (16000000Hz/64/250 = 1000Hz)
//
//  Entry:
//      None
//
//  Exit:
//      None
//
//-----------------------------------------------------------------------------
bool initTimer2() {
    // Disable interrupts
    cli();

    // --- TIMER 2 INTERRUPT SETUP --------------------------------------------
    // TIMER2 is used to generate the millis clock on the EmojiPad. To have the
    // ISR trigger every millisecond, the TIMER2 prescaler is set to 64, and 
    // the COMPA register is set to 250 (16000000Hz/64/250 = 1000Hz)

    // Clear Timer2 control registers
    TCCR2A = 0;
    TCCR2B = 0;

    // Initialize counter to 0
    TCNT2 = 0;

    // Set compare match register to 250 for interrupt to occur every 1000Hz
    OCR2A = 250; 

    // Turn on CTC Mode
    TCCR2B |= (1 << WGM22);

    // Set Prescaler to 64
    TCCR2B |= (1 << CS22) | (0 << CS21) | (0 << CS20);

    // Enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);
}

//-----------------------------------------------------------------------------
//
//  millis2
//
//  Description:
//      This function returns the number of milliseconds the processor has been
//      active since the last reset. 
//    
//      This will reset approximately every 49 days.
//
//      This function is neccessary due to TIMER0 interrupts being disabled. 
//      The default Arduino millis() function uses the TIMER0 interrupts to 
//      operate. 
//
//  Entry:
//      None
//  
//  Exit:
//      elapsedTime - Number of milliseconds since last reset
//
//-----------------------------------------------------------------------------
uint32_t millis2() {
    return (elapsedTimeMs);
}

// --- KEYPAD FUNCTIONS -------------------------------------------------------
// The EmojiPad features a 4x4 Keypad Matrix. This is a standard 4x4 matrix 
// that utilizes a diode connected to each key to prevent ghosting from 
// occurring. 
//
// To read the keys, a scan occurs over each row and column to determine which
// keys are currently being pressed. This is stored in a bitmap, which consists
// of an array of bytes, of which each bit is mapped to a key on the current 
// row. For example, Key 0 is mapped to Bit 0 of Byte 0, and Key 15 is mapped
// to Bit 3 of Byte 3. 
//
// The globally defined list keys_active consists of MAX_KEYS_ACTIVE key 
// objects. This list is used by the updateList function to determine the 
// current state, start time, and value of the active keys. 
//
//  The methodology for scanning the keypad was heavily leveraged from the 
//  Arduino Keypad library developed by Mark Stanley and Alexander Brevig. 
//  This library is available here: http://playground.arduino.cc/code/keypad


//-----------------------------------------------------------------------------
//
//  scanKeys
//
//  Description:
//      This function scans the rows and columns of the keyboard and determines
//      which keys are currently being pressed. 
//
//      The pressed keys are represented by a 1 in a globally defined bitmap 
//      named bit_map. The bit_map is then used by the updateList function to 
//      determine which keys are currently active. 
//
//  Entry:
//      None
//
//  Exit:
//      None
//
//-----------------------------------------------------------------------------
void scanKeys() {
    // Local Variables
    uint8_t cur_row;
    uint8_t cur_col;

    // Initialize the row pins
    for(cur_row=0; cur_row<ROWS; cur_row++) {
        pinMode(rowPins[cur_row], INPUT);
        digitalWrite(rowPins[cur_row], HIGH);
    }

    // Scan through all keys that are pressed and store pressed keys in bitmap
    for(cur_col=0; cur_col<COLS; cur_col++) {
        pinMode(colPins[cur_col], OUTPUT);
        digitalWrite(colPins[cur_col], LOW);

        // Iterate through rows and read the buttons state
        for(cur_row=0; cur_row<ROWS; cur_row++) {
            bitWrite(bit_map[cur_row], cur_col, !digitalRead(rowPins[cur_row]));
        }
        digitalWrite(colPins[cur_col], HIGH);                       
        pinMode(colPins[cur_col], INPUT);
    }
}


//-----------------------------------------------------------------------------
//
//  updateList
//
//  Description:
//      This function updates the list containing all of the currently pressed
//      keys. This list is globally defined as keys_active.
//
//      Each member of this list is a key struct, which contains 3 different 
//      parameters, start_time - the timestamp the key was first pressed, 
//      key_value - the value of the current pressed key (EB_KEY0), and
//      key_state - the current state of the key, PRESSED, HOLD, IDLE. 
//
//      To update the list, the bit_map that is updated by scankeys is scanned. 
//      If the current bit is active (1), then the list of currently active 
//      keys is checked to see if the key was pressed previously. A key press 
//      consists of the following states:
//          - IDLE 
//              The key is not currently pressed
//              key_state = IDLE
//              key_value = 0
//              start_time = 0
//
//          - PRESSED (first press)
//              The key has just been pressed, this is the first time the key
//              press has been detected.
//              key_state = PRESSED
//              key_value = CUR_KEY_VALUE
//              start_time = millis2()
//  
//          - HOLD
//              The key was previously pressed, now wait for HOLD_TIME to 
//              expire before repeating the key press.
//              key_state = HOLD
//              key_value = value from when it was initially pressed
//              start_time = value from when it was initially pressed
//          
//          - PRESSED (repeat keystrokes)
//              The key has now been held down for longer than HOLD_TIME. The
//              is now repeatedly sent. 
//              key_state = PRESSED
//              key_value = value from when it was initially pressed
//              start_time = value from when it was initially pressed 
//              
//
//  Entry:
//      None
//
//  Exit:
//      num_keys_active: Number of keys that are being pressed
//
//-----------------------------------------------------------------------------
uint8_t updateList() {
    // Local variables
    uint8_t num_keys_active = 0;
    int8_t  key_index;
    uint8_t cur_row;
    uint8_t cur_col;
    uint8_t cur_key;

    // Clear all idle keys
    for(cur_key=0; cur_key<MAX_KEYS_ACTIVE; cur_key++) {
        // Clear the time for idle keys
        if(keys_active[cur_key].key_state == IDLE) {
            keys_active[cur_key].key_value = 0;
            keys_active[cur_key].start_time = 0;
        }
    }

    // Check rows and columns for active keys
    for(cur_row=0; cur_row<ROWS; cur_row++) {
        for(cur_col=0; cur_col<COLS; cur_col++) {
            // Update active keys if the current key is pressed
            if(bitRead(bit_map[cur_row], cur_col))
            {   
                // Check if the key is already in the keys_active list
                key_index = findInList(keys[cur_row][cur_col]);

                if(key_index == -1) {
                    // Change state to PRESSED
                    keys_active[num_keys_active].key_state = PRESSED;
                    keys_active[num_keys_active].key_value = keys[cur_row][cur_col];
                    keys_active[num_keys_active].start_time = millis2();

                    num_keys_active++;
                }
                // else if(millis2()-hold_time > )
                else {
                    if(keys_active[key_index].key_state == PRESSED) {
                        // Wait for key hold time to expire before sending key press again
                        keys_active[num_keys_active].key_state = HOLD;
                        keys_active[num_keys_active].key_value = keys_active[key_index].key_value;
                        keys_active[num_keys_active].start_time = keys_active[key_index].start_time;
                    }
                    else if(millis2()-hold_time > keys_active[key_index].start_time) {
                        // Key hold time has expired, repeat the key strokes
                        keys_active[num_keys_active].key_state = PRESSED;
                        keys_active[num_keys_active].key_value = keys[cur_row][cur_col];
                    }

                    num_keys_active++;
                }
            }
            else{
                // Check if the key is currently active
                key_index = findInList(keys[cur_row][cur_col]);

                // Put the key back into the idle state
                if(key_index != -1)
                {
                    keys_active[key_index].key_state = IDLE;
                }
            }
        }
    }

    return num_keys_active;
}

//-----------------------------------------------------------------------------
//
//  getKeys
//
//  Description:
//      This function executes a scan of the keypad, updates the keys_active
//      list, and returns the number of keys that are currently active. 
//
//  Entry:
//      None
//  
//  Exit:
//      key - 1 if keys are currently pressed, 0 if they are not
//
//-----------------------------------------------------------------------------
bool getKeys() {
    // Local Variables
    uint8_t keys_active;

    if((millis2()-start_time) > debounce_time)
    {
        scanKeys();
        keys_active= updateList();
        start_time = millis2();
    }

    return keys_active;
}


//-----------------------------------------------------------------------------
//
//  getKey
//
//  Description:
//      This function returns the first key that was detected as being pressed.
//      This is a very basic use and is maily used to verify the functionality
//      of the keypad. 
//
//  Entry:
//      None
//
//  Exit:
//      pressed_key - Key that is currently pressed
//
//-----------------------------------------------------------------------------
char getKey() {
    if(getKeys()) {
        // Check if repeat time has been elapsed
        if(keys_active[0].key_state == PRESSED)
            return keys_active[0].key_value;
    }

    return -1;
}


//-----------------------------------------------------------------------------
//
//  findInList
//
//  Description:
//      This function checks if a key is currently in the keys_active list. It 
//      will return either the index of the key in the keys_active list or -1 
//      if the key is not in the list. 
//  
//  Entry:
//      key_code: key code to find in the list
//  
//  Exit:
//      Returns -1 if the key is not in the list, the index of the item in the
//      list if it exists. 
//
//-----------------------------------------------------------------------------
int8_t findInList(uint8_t key_code) {
    // Local variables
    uint8_t i;

    for(i=0; i<MAX_KEYS_ACTIVE; i++) {
        if(keys_active[i].key_value == key_code) {
            return i;
        }
    }

    return -1;
}

// --- ISR ROUTINES -----------------------------------------------------------

//-----------------------------------------------------------------------------
//
//  TIMER2_COMPA_vect
//
//  Description:
//      This interrupt service routine (ISR) is executed every millisecond and 
//      is used to increment the millis() count. The millis() count is kept in
//      the global variable elapsedTime.
//
//-----------------------------------------------------------------------------
ISR(TIMER2_COMPA_vect) {
  elapsedTimeMs++;

  #ifdef TIMER2_COMPA_DEBUG
  digitalWrite(LED, !digitalRead(LED));
  #endif
}