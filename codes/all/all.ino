#include "display.h"
#include "engine.h"
#include "note_detector.h"

#define engineTime 3000

int noteValue = 0;

void setup() {
  Serial.begin(115200);

  displaySettings();
  // setupEngine();
}

void loop() {
  noteValue = note_detector();

  displayNote(noteValue);
  
  // updateSpeedValue(frequency);
  // runEngine(engineTime);
  // stopEngine(100);

  delay(1000);
}
