#include "arduino-base/Libraries/AnalogInput.h"
#include "arduino-base/Libraries/Button.h"
#include "arduino-base/Libraries/SerialManager.h"

SerialManager serialManager;

long baudRate = 115200;

AnalogInput analogInput1;
Button button1;

// Pin assignments
#define analogInput1Pin A0
#define button1Pin 2
#define ledPin 3
#define pwmOutputPin 5

void setup() {

  // Enables/disables debug messaging from ArduinoJson
  boolean arduinoJsonDebug = false;

  // Ensure Serial Port is open and ready to communicate
  serialManager.setup(baudRate, [](char* message, char* value) {
    onParse(message, value);
  }, arduinoJsonDebug);

  // For every sketch, we need to set up our IO
  // Setup digital pins and default modes as needed, analog inputs are setup by default
  pinMode(ledPin, OUTPUT);
  pinMode(pwmOutputPin, OUTPUT);

  // ANALOG INPUTS

  // Parameter 1: pin location
  // Parameter 2: enable averaging to get a less constant stream of data
  boolean enableAverager = true;
  // Parameter 3: the number of samples to average
  int averagerSampleRate = 10;
  // Parameter 4: enable lowpass filter for Averager to further smooth value
  boolean enableLowPass = false;
  // Parameter 5: callback

  analogInput1.setup(analogInput1Pin, enableAverager, averagerSampleRate, enableLowPass, [](int analogInputValue) {
    serialManager.sendJsonMessage("analogInput1", analogInputValue);
  });

  // DIGITAL INPUTS

  // Parameter 1: pin location
  // Parameter 2: callback

  button1.setup(button1Pin, [](int state) {
    if (state) serialManager.sendJsonMessage("button1-press", 1);
  });
}

void loop() {
  analogInput1.idle();
  button1.idle();
  serialManager.idle();
}

void onParse(char* message, int value) {
  if (strcmp(message, "led") == 0) {
    // Turn-on led
    digitalWrite(ledPin, value);
  }
  else if (strcmp(message, "pwm-output") == 0 && value >= 0) {
    // Set pwm value to pwm pin
    analogWrite(pwmOutputPin, value);
    serialManager.sendJsonMessage("pwm-set", value);
  }
  else if (strcmp(message, "pot-rotation") == 0 && value == 1) {
    serialManager.sendJsonMessage("pot-rotation", analogInput1.readValue());
  }
  else if (strcmp(message, "wake-arduino") == 0 && value == 1) {
    serialManager.sendJsonMessage("arduino-ready", 1);
  }
  else {
    serialManager.sendJsonMessage("unknown-command", 1);
  }
}
