
int in[128];

// Data for note detection based on frequency
byte NoteV[13] = {8,23,40,57,76,96,116,138,162,187,213,241,255};

// Top 5 frequencies peaks in descending order
float f_peaks[5];
int Mic_pin;


void   setup() {
  Serial.begin(115200);
  Mic_pin = A1;
}


void loop() {
  note_detector();
}


void note_detector() {
  long unsigned int a1,b,a2;
  float a;
  float sum1 = 0,sum2 = 0;
  float sampling;
  a1 = micros();
  for(int i=0;i<128;i++) {
    // Rough zero shift
    a = analogRead(Mic_pin) - 500;
          
    // Utilising time between two sample for windowing & amplitude calculation
    // To average value
    sum1 = sum1 + a;
    // To RMS value         
    sum2 = sum2 + a*a;
    // Hann window
    a = a*(sin(i*3.14/128)*sin(i*3.14/128));
    // Scaling for float to int conversion
    in[i] = 10*a;
    // Based on operation frequency range
    delayMicroseconds(195);   
  }
  
  b = micros();

  // Average amplitude
  sum1 = sum1/128;
  // RMS  
  sum2 = sqrt(sum2/128);
  // Real time sampling frequency
  sampling = 128000000 / (b-a1);

  // for very low or no amplitude, this code won't start
  // it takes very small aplitude of sound to initiate for value sum2-sum1>3,   
  // change sum2-sum1 threshold based on requirement
  
  if(sum2 - sum1 > 3) {
    
    FFT(128, sampling);        
    // EasyFFT based optimised  FFT code,   
    // this code updates f_peaks array with 5 most dominent frequency in descending order

    // Utilising in[] array for further calculation
    for(int i=0;i<12;i++) {
      in[i] = 0;
    }
    
    // Below loop will convert frequency value to note   
    int j = 0,k = 0; 
    for(int i=0; i<5;i++) {
      if(f_peaks[i] > 1040) {f_peaks[i]=0;}
      if(f_peaks[i] >= 65.4 && f_peaks[i] <= 130.8) {f_peaks[i]=255*((f_peaks[i]/65.4)-1);}
      if(f_peaks[i] >= 130.8 && f_peaks[i] <= 261.6) {f_peaks[i]=255*((f_peaks[i]/130.8)-1);}
      if(f_peaks[i] >= 261.6 && f_peaks[i] <= 523.25) {f_peaks[i]=255*((f_peaks[i]/261.6)-1);}
      if(f_peaks[i] >= 523.25 && f_peaks[i] <= 1046) {f_peaks[i]=255*((f_peaks[i]/523.25)-1);}
      if(f_peaks[i] >= 1046 && f_peaks[i] <= 2093) {f_peaks[i]=255*((f_peaks[i]/1046)-1);}
      if(f_peaks[i] > 255) {f_peaks[i]=254;}
      
      j = 1;
      k = 0;
         
      while(j == 1) {
        if(f_peaks[i] < NoteV[k]) {
          f_peaks[i] = k;
          j = 0;
        }

        // A note with max peaks (harmonic) with aplitude priority is selected
        k++;  
        if(k > 15) {
          j = 0;
        }
      }

      if(f_peaks[i] == 12) {
        f_peaks[i] = 0;
      }
      k = f_peaks[i];
      in[k] = in[k]+(5-i);
    }

    k = 0;
    j = 0;
    
    for(int i=0;i<12;i++) {
      //Max value detection
      if(k < in[i]) {
        k = in[i];
        j = i;
      }   
    }
    
    // Note print
    
    // If you need to use note value for some application, use of note number recomendded
    // where, 0 = c, 1 = c#, 2 = D, 3 = D#, ...
       
    // a2 = micros(); // Time check
    
    k = j;
    
    if(k==0) {Serial.println('C');}
    if(k==1) {Serial.println("C#");}
    if(k==2) {Serial.println('D');}
    if(k==3) {Serial.println("D#");}
    if(k==4) {Serial.println('E');}
    if(k==5) {Serial.println('F');}
    if(k==6) {Serial.println("F#");}
    if(k==7) {Serial.println('G');}
    if(k==8) {Serial.println("G#");}
    if(k==9) {Serial.println('A');}
    if(k==10){Serial.println("A#");}
    if(k==11){Serial.println('B');}
  }
}

// Documentation on EasyFFT: https://www.instructables.com/member/abhilash_patel/instructables/
// EasyFFT code optimised for 128 sample size to reduce memory consumption

float FFT(byte N,float Frequency) {
  byte data[8] = {1,2,4,8,16,32,64,128};
  int a,c1,f,o,x;
  
  a = N;  

  // Calculating the levels
  for(int i=0;i<8;i++) {
    if(data[i] <= a) {
      o = i;
    } 
  }
  
  o = 7;
  
  // Input for sequencing
  byte in_ps[data[o]] = {}; 

  // Real part of transform
  float out_r[data[o]] = {};

  // Imaginary part of transform
  float out_im[data[o]] = {};  
            

  x = 0;

  // Bit reversal
  for(int b=0;b<o;b++) {
    c1 = data[b];
    f = data[o] / (c1+c1);
    
    for(int j=0;j<c1;j++) { 
      x = x + 1;
      in_ps[x] = in_ps[j]+f;
     }
  }

  // Update input array as per bit reverse order
  for(int i=0;i<data[o];i++) {
    if(in_ps[i] < a) {
      out_r[i] = in[in_ps[i]];
    }
    if(in_ps[i] > a) {
      out_r[i] = in[in_ps[i] - a];
    }       
  }

  int i10,i11,n1;
  float e,c,s,tr,ti;

  // FFT
  for(int i=0;i<o;i++) {

    // Overall values of sine cosine
    i10 = data[i];
    // Loop with similar sine cosine
    i11 = data[o] / data[i+1];     
    e = 6.283 / data[i+1];
    e = 0 - e;
    n1 = 0;

    for(int j=0;j<i10;j++) {
      c = cos(e*j);   
      s = sin(e*j); 
      n1 = j;
          
      for(int k=0;k<i11;k++) {
        tr=c*out_r[i10+n1]-s*out_im[i10+n1];
        ti=s*out_r[i10+n1]+c*out_im[i10+n1];
          
        out_r[n1+i10]=out_r[n1]-tr;
        out_r[n1]=out_r[n1]+tr;
        
        out_im[n1+i10]=out_im[n1]-ti;
        out_im[n1]=out_im[n1]+ti;          
        
        n1=n1+i10+i10;
      }       
    }
  }

  //---> Here onward out_r contains amplitude and our_in conntains frequency (Hz)

  // Getting amplitude from complex number
  for(int i=0;i<data[o-1];i++) {

    // To increase the speed delete sqrt
    out_r[i] = sqrt((out_r[i]*out_r[i])+(out_im[i]*out_im[i]));   
    out_im[i] = (i*Frequency) / data[o];
    
    /*
    Serial.print(out_im[i], 2);
    Serial.print("Hz");
    */
  }

  // Peak detection
  x = 0;
  
  for(int i=1;i<data[o-1]-1;i++) {
    if(out_r[i] > out_r[i-1] && out_r[i] > out_r[i+1]) {
      // in_ps array used for storage of peak number
      in_ps[x] = i;     
      x = x + 1;
    }    
  }

  s = 0;
  c = 0;

  // Rearraange as per magnitude
  for(int i=0;i<x;i++) {
    for(int j=c;j<x;j++) {
      if(out_r[in_ps[i]]<out_r[in_ps[j]]) {
        s = in_ps[i];
        in_ps[i] = in_ps[j];
        in_ps[j] = s;
      }
    }
    
    c = c + 1;
  }

  // Updating f_peak array (global variable) with descending order
  for(int i=0;i<5;i++) {
    float a1 = out_im[in_ps[i]-1]*out_r[in_ps[i]-1];
    float a2 = out_im[in_ps[i]]*out_r[in_ps[i]];
    float a3 = out_im[in_ps[i]+1]*out_r[in_ps[i]+1];
    
    float a = (a1 + a2 + a3);
    float b = (out_r[in_ps[i]-1]+out_r[in_ps[i]]+out_r[in_ps[i]+1]);
    f_peaks[i] = a / b;
  }
}
