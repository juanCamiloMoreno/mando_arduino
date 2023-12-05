// Simple arcade stick example that demonstrates how to read twelve
// Arduino Pro Micro digital pins and map them to the
// Arduino Joystick library.
//

// The digital pins 2 - 20 are grounded when they are pressed.
// Pin 10, A10, Red = UP
// Pin 15, D15, Yellow = RIGHT
// Pin 16, D16, Orange = DOWN
// Pin 14, D14, Green = LEFT

// Pin 9, A9 = Button 1
// Pin 8, A8 = Button 2
// Pin 7, D7 = Button 3
// Pin 3, D3 = Button 4
// Pin 2, D2 = Button 5
// Pin 4, A6 = Button 6

// Pin 20, A2 = Select Button 1
// Pin 19, A1 = Start Button 2

// Pin 5, D5 = Other Button
// Pin 6, A7 = Other Button
// Pin 18, A0 = Other Button
// Pin 21, A3 = Other Button

// NOTE: This sketch file is for use with Arduino Pro Micro only.
//
// Original gamepad example by Matthew Heironimus
// 2016-11-24
// Adapted for arcade machine setup by Ben Parmeter
// 2019-05-20
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  8, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  true, true, false);  // No accelerator, brake, or steering
const int analogInPin0 = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue0 = 0;  // value read from the pot
int outputValue0 = 0;  // value output to the PWM (analog out)

const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to
int sensorValue1 = 0;  // value read from the pot
int outputValue1 = 0;  // value output to the PWM (analog out)


void setup() {
  // Initialize Button Pins
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
 // pinMode(6, INPUT_PULLUP);
  //pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setAcceleratorRange(0, 256);
  Joystick.setBrakeRange(0, 256);
  Serial.begin(9600);
}

// Last state of the buttons
int lastButtonState[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int buttonMap[16] = {A0,A1,0,0,10,2,16,3,14,4,15,5,19,6,18};
//int buttonMap[16] = {0,0,0,0,10,16,14,15,2,3,4,5,19,5,6,18};
//                    0 1 2 3,4  5   6 7  8 9 10 11 12 13 14 15
//                            0 1 2 3,4 5 6 7 8 9 10 11 12 13 14 15
// ButtonMap = 0, Pin 10 = UP
// ButtonMap = 1, Pin 15 = RIGHT
// ButtonMap = 2, Pin 16 = DOWN
// ButtonMap = 3, Pin 14 = LEFT

// ButtonMap = 4, Pin 9 = Button 1
// ButtonMap = 5, Pin 8 = Button 2
// ButtonMap = 6, Pin 7 = Button 3
// ButtonMap = 7, Pin 3 = Button 4
// ButtonMap = 8, Pin 2 = Button 5
// ButtonMap = 9, Pin 4 = Button 6

// ButtonMap = 10, Pin 20 = Select Button 1
// ButtonMap = 11, Pin 19 = Start Button 2

// ButtonMap = 12, Pin 5 = Other Button
// ButtonMap = 13, Pin 6 = Other Button
// ButtonMap = 14, Pin 18 = Other Button
// ButtonMap = 15, Pin 21 = Other Button


void loop() {
  sensorValue0 = analogRead(analogInPin0);
  sensorValue1 = analogRead(analogInPin1);
  // map it to the range of the analog out:
  outputValue0 = map(sensorValue0, 577, 492, 0, 255);
  outputValue1 = map(sensorValue1, 616, 517, 0, 255);
  // change the analog out value:


  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(outputValue0);
  Serial.print("\t output = ");
  Serial.println(outputValue1);
  Joystick.setAccelerator(outputValue0);
  Joystick.setBrake(outputValue1);

   //int index=17;
  // Read pin values

  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !digitalRead(buttonMap[index]);
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // accelerator
          sensorValue0 = analogRead(analogInPin0);
          outputValue0 = map(sensorValue0, 0, 1023, 0, 255);
          Serial.print("\t output = ");
          Serial.println(sensorValue0);
          break;
        case 1: // brake
          
          break;
        case 2: // DOWN
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 3: // LEFT
          if (currentButtonState == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 4: // Black Button 1
          Joystick.setButton(0, currentButtonState);
          break;
        case 5: // Black Button 2
          Joystick.setButton(1, currentButtonState);
          break;
        case 6: // Black Button 3
          Joystick.setButton(2, currentButtonState);
          break;
        case 7: // Black Button 4
          Joystick.setButton(3, currentButtonState);
          break;
        case 8: // Black Button 5
          Joystick.setButton(4, currentButtonState);
          break;
        case 9: // Black Button 6
          Joystick.setButton(5, currentButtonState);
          break;
        case 10: // Select Button
          Joystick.setButton(6, currentButtonState);
          break;
        case 11: // Start Button
          Joystick.setButton(7, currentButtonState);
          break;
        case 12: // Other Button 1
          Joystick.setButton(8, currentButtonState);
          break;
        case 13: // Other Button 2
          Joystick.setButton(9, currentButtonState);
          break;
        case 14: // Other Button 3
          Joystick.setButton(10, currentButtonState);
          break;
        case 15: // Other Button 4
          Joystick.setButton(11, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(10);
}
