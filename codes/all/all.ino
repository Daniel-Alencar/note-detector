#include "engine.h"
#include "note_detector.h"

#define waitTime 3000

void setup() {
  Serial.begin(115200);
//  setupEngine();
}

void loop() {
  listenTheSound();
  frequency = identifyFrequency();
  
//  updateSpeedValue(frequency);
//
//  runEngine(waitTime);
//  stopEngine(100);

  delay(1000);
}
