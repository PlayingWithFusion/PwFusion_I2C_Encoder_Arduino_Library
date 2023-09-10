/***************************************************************************
* File Name: PwFusion_Encoder_RGB_LED_example.ino
* Processor/Platform: R3aktor (tested)
* Development Environment: Arduino 2.2.1
*
* Designed for use with with Playing With Fusion I2C Rotary Encoder
* interface board: IFB-40001
*
* Copyright © 2015-18 Playing With Fusion, Inc.
* SOFTWARE LICENSE AGREEMENT: This code is released under the MIT License.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
* **************************************************************************
* REVISION HISTORY:
* Author		  Date	    Comments
* N. Johnson  2023Aug10 Original Version
*
* Playing With Fusion, Inc. invests time and resources developing open-source
* code. Please support Playing With Fusion and continued open-source
* development by buying products from Playing With Fusion!
* **************************************************************************
* ADDITIONAL NOTES:
* This file contains functions to initialize and run a Playing With Fusion R3aktor in
* order to communicate with the I2C Encoder board. Funcionality is as described below:
*	- Configure R3aktor to alter the brightness of an RGB LED based on the input from
*   the rotary encoder
*       - call PWF library to configure and read the I2C Rotary Encoder inputs
*	- Broadcast results to COM port
*  Circuit:
*    R3aktor     -->  RGB LED
*    DIO pin 09  -->  Red Pin with 220 ohm resistor in series
*    DIO pin 10  -->  Green Pin with 220 ohm resistor in series
*    DIO pin 11  -->  Blue Pin with 220 ohm in resistor series
*    GND         -->  GND
*    R3aktor     -->  I2C Encoder
*    Qwiic pins  -->  Qwiic pins
***************************************************************************/

// Include the PwFusion I2C Encoder library
#include <PwFusion_Encoder.h>

// Define the color in relation to its index in the array
#define RED_LED 0
#define GREEN_LED 1
#define BLUE_LED  2

// Define the number of encoder ticks from 0% to 100% brightness.
// Increasing this number will increase the achievable precision of color selection, but
// will increase the number of rotations required to move from 0% to 100% brightness.
#define LED_VALUE_STEP  10

// Define the i2c address for the encoder
// uint8_t ADR = 0x01;
uint8_t ADR = 0x02;

// Variable to keep track of the number of times the encoder button has been pressed
int btnCounter = 0;

// Variable to keep track of the previous enocder counter value
int prevCounter = 0;

// Variable to keep track of the previous encoder button state
int prevBtnState = 0;

// Variable to keep track of the currently selected LED with a range from 0-2.
// Used to index leds[] and ledVals[] arrays
int toggle = 0;

// Define an array with the RGB pins
// leds[0] = red, leds[1] = green, leds[2] = blue
int leds[3] = {9, 10, 11};

// Define an array to store the brightness values of each color in the RGB.
int ledVals[3] = {0, 0, 0};

// Create a new encoder object
Encoder enc;

void setup() {

  Serial.begin(9600);

  // Start the encoder object and pass in the i2c address
  enc.begin(ADR);

  // Set the RBG LED pins as outputs
  pinMode(leds[RED_LED], OUTPUT);
  pinMode(leds[GREEN_LED], OUTPUT);
  pinMode(leds[BLUE_LED], OUTPUT);

}

void loop() {

  // If the encoder switch is pressed, add one to the button counter
  if (enc.getBtnState() == 1 && prevBtnState == 0) btnCounter += 1;

  // Update the value of the previous encoder button state
  prevBtnState = enc.getBtnState();

  // Update the toggle variable to be in a range of 0 to 2 based on the current valye of the encoder button counter
  toggle = btnCounter % 3;

  // If the encoder count has changed, update the selected LED value with the direction of the encoder (-1 or 1)
  if (enc.getCount() != prevCounter) ledVals[toggle] += enc.getDirection();

  // Update the value of the previous encoder counter state
  prevCounter = enc.getCount();

  // Keep the selected LED value in the desired range
  if (ledVals[toggle] < 0) ledVals[toggle] = 0;
  if (ledVals[toggle] > LED_VALUE_STEP) ledVals[toggle] = LED_VALUE_STEP;

  // Print the LED brightness values
  Serial.print("RED:  ")
  Serial.print(ledVals[RED_LED]);
  Serial.print("  |  GREEN:  ");
  Serial.print(ledVals[GREEN_LED]);
  Serial.print("  |  BLUE:  ");
  Serial.println(ledVals[BLUE_LED]);

  // Write the LED value to the currently selected color in the RGB
  analogWrite(leds[toggle], map(ledVals[toggle], MIN_LED_VAL, MAX_LED_VAL, 0, 255));

}
