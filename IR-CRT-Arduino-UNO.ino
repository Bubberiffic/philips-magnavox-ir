/*
  Philips_Magnavox_RC5_Service_Controller
  ----------------------------------------
  Custom IR remote controller for CRT service and input control.
  Uses RC5 protocol via IR LED on pin 3.

  Color-coded button layout (updated labels):
    🔴 INPUT TOGGLE (AV/RF) → Pin 2
    🟡 SERVICE MACRO → Pin 6
    🟢 HORIZONTAL POSITION ADJ → Pin 7
    🔵 VERTICAL POSITION ADJ → Pin 4
*/

#include <IRremote.hpp>

// Pin assignments
const int irLedPin = 3;               // IR LED on pin 3
const int inputToggleButton = 2;      // 🔴 RED = AV/RF input toggle
const int vPosAdjustButton = 4;       // 🔵 BLUE = Vertical position adjustment
const int hPosAdjustButton = 7;       // 🟢 GREEN = Horizontal position adjustment
const int serviceMacroButton = 6;     // 🟡 YELLOW = Service menu macro

void setup() {
  // Initialize IR transmitter
  IrSender.begin(irLedPin);

  // Button setup with internal pull-ups
  pinMode(inputToggleButton, INPUT_PULLUP);
  pinMode(vPosAdjustButton, INPUT_PULLUP);
  pinMode(hPosAdjustButton, INPUT_PULLUP);
  pinMode(serviceMacroButton, INPUT_PULLUP);

  // Debugging output
  Serial.begin(9600);
  Serial.println("==== Philips Magnavox RC5 Service Controller ====");
  Serial.println("Color-Coded Buttons:");
  Serial.println("  🔴 INPUT TOGGLE (Pin 2)  → AV/RF Select");
  Serial.println("  🔵 V-POS ADJUST (Pin 4) → Vertical Position");
  Serial.println("  🟢 H-POS ADJUST (Pin 7) → Horizontal Position");
  Serial.println("  🟡 SERVICE MACRO (Pin 6) → Service Menu Command Sequence");
  Serial.println("=================================================");
}

void loop() {
  // Read button states
  int inputToggleState = digitalRead(inputToggleButton);
  int vPosAdjustState = digitalRead(vPosAdjustButton);
  int hPosAdjustState = digitalRead(hPosAdjustButton);
  int serviceMacroState = digitalRead(serviceMacroButton);

  // 🔴 INPUT TOGGLE button (AV/RF)
  if (inputToggleState == LOW) {
    Serial.println("🔴 INPUT TOGGLE pressed → Sending AV/RF toggle command");
    IrSender.sendRC5(0x00, 56, true);
    delay(500);
  }

  // 🔵 VERTICAL position adjustment
  if (vPosAdjustState == LOW) {
    Serial.println("🔵 V-POS ADJUST pressed → Sending vertical position command");
    IrSender.sendRC5(0x00, 9, true);
    delay(500);
  }

  // 🟢 HORIZONTAL position adjustment
  if (hPosAdjustState == LOW) {
    Serial.println("🟢 H-POS ADJUST pressed → Sending horizontal position command");
    IrSender.sendRC5(0x00, 8, true);
    delay(500);
  }

  // 🟡 SERVICE MACRO (Test/Service menu sequence)
  if (serviceMacroState == LOW) {
    Serial.println("🟡 SERVICE MACRO pressed → Running 2 → 7 → 1 → MUTE service access sequence");
    IrSender.sendRC5(0x00, 12, true); // Power toggle (unchanged)
    delay(500);
    IrSender.sendRC5(0x00, 2, true);  // "2"
    delay(500);
    IrSender.sendRC5(0x00, 7, true);  // "7"
    delay(500);
    IrSender.sendRC5(0x00, 1, true);  // "1"
    delay(500);
    IrSender.sendRC5(0x00, 13, true); // "MUTE"
    delay(1000);
  }
}

// Program written by Bubberiffic and commented with AI. 