
#define piezoSound A0
#include <stdlib.h>

// Sample Frequency in kHz
const float sample_freq = 22050;

int len = 0;
int i,k;
long sum, sum_old;
int thresh = 0;
float freq_per = 0;
byte pd_state = 0;
int value;
unsigned char *rawDataOfSound = NULL;
bool debug = false;


void listenTheSound(int waitTime, int amountOfExamples) {
  
  if(debug) {
    
    // rawDataOfSound = &rawData[0];
    // len = 1000;
    
  } else {
    free(rawDataOfSound);
    rawDataOfSound = NULL;
    
    int i;
    for(i = 0; i < amountOfExamples; i++) {
      
      value = analogRead(piezoSound);
      value = map(value, 0, 1023, 0, 255);
    
      rawDataOfSound = (unsigned char *) realloc(rawDataOfSound, (i + 1) * sizeof(unsigned char));
      if(!rawDataOfSound) {
        Serial.println("Não foi possível realocar espaço...");
      } else {
        Serial.println("Espaço realocado!");
      }
      rawDataOfSound[i] = value;
  
      delay(waitTime);
    }
    len = i;
  }  
}
  
int identifyFrequency() {
  sum = 0;
  pd_state = 0;
  int period = 0;
  for(i=0; i < len; i++) {
    
    // Autocorrelation
    sum_old = sum;
    sum = 0;
    for(k=0; k < len-i; k++) {
      sum += (rawDataOfSound[k]-128) * (rawDataOfSound[k+i]-128) / 256;
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
