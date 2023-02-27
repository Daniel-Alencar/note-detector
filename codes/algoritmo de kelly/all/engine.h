
#define speedController 3
#define motor1A 4
#define motor1B 5
#define maximumSpeedValue 255

// 0 é o valor mínimo de velocidade
// 255 é o valor máximo de velocidade
int speedValue = 0;

int frequencyLimits[] = {20, 4938};
int average = (frequencyLimits[0] + frequencyLimits[1]) / 2;
int range = average - frequencyLimits[0];
int frequency = 0;

void updateSpeedValue(int frequency) {
  if(frequency >= frequencyLimits[0] && frequency <= frequencyLimits[1]) {
    if(frequency >= average) {
      speedValue = ((frequency / range) * maximumSpeedValue);
    } else {
      speedValue = 0 - ((frequency / range) * maximumSpeedValue);
    }
  }
}

void setupEngine() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(speedController, OUTPUT);

  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  analogWrite(speedController, speedValue);
}

void runEngine(int waitTime) {
  if(speedValue >= 0) {
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, HIGH);
  } else {
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor1B, LOW);
  }
  analogWrite(speedController, speedValue);
  delay(waitTime);
}

void stopEngine(int waitTime) {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  delay(waitTime);
}
