#include <Adafruit_NeoPixel.h>
#define PIN        15 
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include "Keyboard.h"

int modePushCounter = 0;       // counter for the number of button presses
int buttonState = 0;           // current state of the button
int lastButtonState = 0;       // previous state of the button

const int ModeButton = 5;     // the pin that the Modebutton is attached to


// PIN numbers (CONSTANTS)
const int TLPIN = 14; // top row: left, center right
const int TCPIN = 16;
const int TRPIN = 10;
const int MLPIN = 9; // middle row: left, center, right
const int MCPIN = 8;
const int MRPIN = 7;
const int BLPIN = 6; // bottom row: left, right
//const int BRPIN = 5;
const int BNPIN = 4;// rotary encoder: button
const int RPIN = 2; // rotary encoder: right
const int LPIN = 3; // rotary encoder: left
const int FPIN = A0; // foot switch pin (digital)
const int APIN = A1; // potentiometer pin (analog)
const int JPIN = A3; // jumper pin (deactivates all functions if pulled down)

// pins to monitor
const int MPINS[] = {TLPIN, TCPIN, TRPIN, MLPIN, MCPIN, MRPIN, BLPIN, BNPIN, RPIN, FPIN};
int last_state[10]; // last pin states
int decay[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // current decay times per pin

// other digital pins
const int OPINS[] = {LPIN, JPIN};

// other variables and constants
const int DLY = 0; // extra delay per run, in ms (refresh rate)
const int DCY = 5; // decay per key, in runs (min. DCY*DLY milliseconds)
int analog_val = 0;
double analog_ratio = 0;


// *********************************
// MAIN FUNCTION, WITH CONFIGURATION
// *********************************


void keyEvent(int n, bool pressed) {
  // handles key event at n-th monitored pin
  // 'pressed' == false if released

  

switch (modePushCounter) {                  // switch between keyboard configurations:
    case 0:                      
  // *** TOP LEFT KEY ***
  if (n == 0) {
    if (pressed) {
      Keyboard.press('q');
    }
    else {
      Keyboard.release('q');
    }
  }

  // *** TOP CENTER KEY ***
  if (n == 1) {
    if (pressed) {
      Keyboard.press('w');
    }
    else {
      Keyboard.release('w');
    }
  }

  // *** TOP RIGHT KEY ***
  if (n == 2) {
    if (pressed) {
      Keyboard.press('e');
    }
    else {
      Keyboard.release('e');
    }
  }

  // *** MIDDLE LEFT KEY ***
  if (n == 3) {
    if (pressed) {
      Keyboard.press('a');
    }
    else {
      Keyboard.release('a');
    }
  }

  // *** MIDDLE CENTER KEY ***
  if (n == 4) {
    if (pressed) {
      Keyboard.press('s');
    }
    else {
      Keyboard.release('s');
    }
  }

  // *** MIDDLE RIGHT KEY ***
  if (n == 5) {
    if (pressed) {
      Keyboard.press('d');
    }
    else {
      Keyboard.release('d');
    }
  }
  
  // *** BOTTOM LEFT KEY ***
  if (n == 6) {
    if (pressed) {
      Keyboard.press(KEY_LEFT_ALT);
    }
    else {
      Keyboard.release(KEY_LEFT_ALT);
    }
  }


  // *** ROTARY ENCODER BUTTON ***
  if (n == 7) {
    if (pressed) {
      Keyboard.press(KEY_RETURN);
    }
    else {
      Keyboard.release(KEY_RETURN);
    }
  }

  // *** MONITOR ROTARY ENCODER ***
  if (n == 8) {
    if (!pressed) { // right pin is high...
      if (digitalRead(LPIN)) { // ... and left one not yet: clockwise
        Keyboard.write(']'); // plus on German keyboard
      }
      else { // ... and left one already high: counter-clockwise
        Keyboard.write('/'); // minus on German keyboard
      }
    }
  }

  // *** FOOT SWITCH ***
  if (n == 9) {
    if (!pressed) { // foot switch is inverted!
      Keyboard.press((char) 0x20); // space key
    }
    else {
      Keyboard.release((char) 0x20);
    }
  }

  
  // important: save state
  last_state[n] = !pressed; // pressed==false is HIGH
 
 break;

 case 1:  
  // *** TOP LEFT KEY ***
  if (n == 0) {
    if (pressed) {
      Keyboard.press(KEY_HOME);
    }
    else {
      Keyboard.release(KEY_HOME);
    }
  }

  // *** TOP CENTER KEY ***
  if (n == 1) {
    if (pressed) {
      Keyboard.press(KEY_UP_ARROW);
    }
    else {
      Keyboard.release(KEY_UP_ARROW);
    }
  }

  // *** TOP RIGHT KEY ***
  if (n == 2) {
    if (pressed) {
      Keyboard.press(KEY_END);
    }
    else {
      Keyboard.release(KEY_END);
    }
  }

  // *** MIDDLE LEFT KEY ***
  if (n == 3) {
    if (pressed) {
      Keyboard.press(KEY_LEFT_ARROW);
    }
    else {
      Keyboard.release(KEY_LEFT_ARROW);
    }
  }

  // *** MIDDLE CENTER KEY ***
  if (n == 4) {
    if (pressed) {
      Keyboard.press(KEY_DOWN_ARROW);
    }
    else {
      Keyboard.release(KEY_DOWN_ARROW);
    }
  }

  // *** MIDDLE RIGHT KEY ***
  if (n == 5) {
    if (pressed) {
      Keyboard.press(KEY_RIGHT_ARROW);
    }
    else {
      Keyboard.release(KEY_RIGHT_ARROW);
    }
  }
  
  // *** BOTTOM LEFT KEY ***
  if (n == 6) {
    if (pressed) {
      Keyboard.press(KEY_DELETE);
    }
    else {
      Keyboard.release(KEY_DELETE);
    }
  }


  // *** ROTARY ENCODER BUTTON ***
  if (n == 7) {
    if (pressed) {
      Keyboard.press(KEY_RETURN);
    }
    else {
      Keyboard.release(KEY_RETURN);
    }
  }

  // *** MONITOR ROTARY ENCODER ***
  if (n == 8) {
    if (!pressed) { // right pin is high...
      if (digitalRead(LPIN)) { // ... and left one not yet: clockwise
        Keyboard.write(']'); // plus on German keyboard
      }
      else { // ... and left one already high: counter-clockwise
        Keyboard.write('/'); // minus on German keyboard
      }
    }
  }

  // *** FOOT SWITCH ***
  if (n == 9) {
    if (!pressed) { // foot switch is inverted!
      Keyboard.press((char) 0x20); // space key
    }
    else {
      Keyboard.release((char) 0x20);
    }
  }

  
  // important: save state
  last_state[n] = !pressed; // pressed==false is HIGH
  
}

}
// ********************
// END OF MAIN FUNCTION




void setup() {
  // initialize monitored pins
  for (int i = 0; i < 10; i++) {
    pinMode(MPINS[i], INPUT_PULLUP);
    last_state[i] = digitalRead(MPINS[i]);
  }

  // initialize other pins and analog in
  for (int i = 0; i < 2; i++) {
    pinMode(OPINS[i], INPUT_PULLUP);
  }
  analog_val = analogRead(APIN);
  analog_ratio = analog_val / 1024;
  
  Serial.begin(9600); // for debugging only
  Keyboard.begin();
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pinMode(ModeButton, INPUT_PULLUP);  // initialize the button pin as a input:  
  Serial.begin(9600); // initialize serial communication:


}

void loop() {

buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState) { // compare the buttonState to its previous state
    if (buttonState == LOW) { // if the state has changed, increment the counter
      // if the current state is LOW then the button cycled:
      modePushCounter++;
      Serial.println("pressed");
      Serial.print("number of button pushes: ");
      Serial.println(modePushCounter);
    } 
    delay(50); // Delay a little bit to avoid bouncing
  }
  lastButtonState = buttonState;  // save the current state as the last state, for next time through the loop
   if (modePushCounter >1){       //reset the counter after 4 presses CHANGE THIS FOR MORE MODES
      modePushCounter = 0;}
  
  // monitor pins
  for (int i = 0; i < 10; i++) {
    if (decay[i] > 0) {
      decay[i] -= 1;
    }
    else if (digitalRead(MPINS[i]) != last_state[i]) {
      keyEvent(i, last_state[i]); // second argument: pressed (true) or released?
      decay[i] = DCY;
    }
  }

  // read analog value
  analog_val = analogRead(APIN);
  analog_ratio = analog_val / 1024;
  //Serial.println(analog_ratio);

  // extra delay per run
  delay(DLY);

 for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
   switch (modePushCounter) {                  // switch between keyboard configurations:
    case 0:    
    pixels.setPixelColor(i, pixels.Color(8,26,150));
    pixels.show();   // Send the updated pixel colors to the hardware.
  break;
   case 1:
   pixels.setPixelColor(i, pixels.Color(0,150,0));
   pixels.show();   // Send the updated pixel colors to the hardware.
   
   }
 }
}
