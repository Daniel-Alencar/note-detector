#define speedController 3
#define motor1A 4
#define motor1B 5

#define waitTime 3000
#define maximumSpeedValue 255

#include "Guitar_C5.h"

// Sample Frequency in kHz
const float sample_freq = 22050;

int len = sizeof(rawData);
int i,k;
long sum, sum_old;
int thresh = 0;
float freq_per = 0;
byte pd_state = 0;
  
int identifyFrequency(unsigned char rawData[]) {
  sum = 0;
  pd_state = 0;
  int period = 0;
  for(i=0; i < len; i++) {
    
    // Autocorrelation
    sum_old = sum;
    sum = 0;
    for(k=0; k < len-i; k++) {
      sum += (rawData[k]-128) * (rawData[k+i]-128) / 256;
    }
    
    // Peak Detect State Machine
    if(pd_state == 2 && (sum-sum_old) <=0) {
      period = i;
      pd_state = 3;
    }
    if(pd_state == 1 && (sum > thresh) && (sum-sum_old) > 0) {
      pd_state = 2;
    }
    if(!i) {
      thresh = sum * 0.5;
      pd_state = 1;
    }
  }
  // Frequency identified in kHz
  freq_per = sample_freq / period;
  Serial.println(freq_per);

  return freq_per;
}

// 0 é o valor mínimo de velocidade
// 255 é o valor máximo de velocidade
int speedValue = 0;

int frequencyLimits[] = {20, 4938};
int average = (frequencyLimits[0] + frequencyLimits[1]) / 2;
int range = average - frequencyLimits[0];
int frequency = 0;

void convertFrequencyInSpeedValue(int frequency) {

  if(frequency >= frequencyLimits[0] && frequency <= frequencyLimits[1]) {
    if(frequency >= average) {
      speedValue = ((frequency / range) * maximumSpeedValue);
    } else {
      speedValue = 0 - ((frequency / range) * maximumSpeedValue);
    }
  }
}

void listenTheSound() {}

void setup() {
  Serial.begin(115200);
//  
//  pinMode(motor1A, OUTPUT);
//  pinMode(motor1B, OUTPUT);
//  pinMode(speedController, OUTPUT);
//
//  digitalWrite(motor1A, LOW);
//  digitalWrite(motor1B, LOW);
//  analogWrite(speedController, speedValue);
}

void loop() {
  listenTheSound();
  frequency = identifyFrequency(rawData);
  
//  convertFrequencyInSpeedValue(frequency);
//  analogWrite(speedController, speedValue);
//
//  digitalWrite(motor1A, LOW);
//  digitalWrite(motor1B, HIGH);
//  delay(waitTime);
//
//  digitalWrite(motor1A, LOW);
//  digitalWrite(motor1B, LOW);
//  delay(100);
}
