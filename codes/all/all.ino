#include "engine.h"
#include "note_detector.h"

#define engineTime 3000
#define soundIntervalTime 0
#define amountOfExamples 1000

void setup() {
  Serial.begin(115200);
//  setupEngine();
}

void loop() {
  listenTheSound(soundIntervalTime, amountOfExamples);
  frequency = identifyFrequency();
  
//  updateSpeedValue(frequency);
//
//  runEngine(engineTime);
//  stopEngine(100);

  delay(1000);
}
