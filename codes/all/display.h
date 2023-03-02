#define SEGMENT_A 1
#define SEGMENT_B 2
#define SEGMENT_C 3
#define SEGMENT_D 4
#define SEGMENT_E 5
#define SEGMENT_F 6
#define SEGMENT_G 7

#define SEGMENT_SHARP 8

#define ARRAY_SIZE 8

// Ligações: a b c d e f g
byte seven_seg_digits[][ARRAY_SIZE] = {
 { 0,1,1,0,0,0,1,1 },  //DIGITO C
 { 0,1,1,0,0,0,1,0 },  //DIGITO C#
 { 1,0,0,0,0,1,0,1 },  //DIGITO D
 { 1,0,0,0,0,1,0,0 },  //DIGITO D#
 { 0,1,1,0,0,0,0,1 },  //DIGITO E
 { 0,1,1,1,0,0,0,1 },  //DIGITO F
 { 0,1,1,1,0,0,0,0 },  //DIGITO F#
 { 0,1,0,0,0,0,0,1 },  //DIGITO G
 { 0,1,0,0,0,0,0,0 },  //DIGITO G#
 { 0,0,0,1,0,0,0,1 },  //DIGITO A
 { 0,0,0,1,0,0,0,0 },  //DIGITO A#
 { 1,1,0,0,0,0,0,1 }   //DIGITO B
};

//FUNÇÃO QUE ACIONA O SEGMENTO
void powerSegment(int segment, byte value) {  
  digitalWrite(segment, value);
}

void displayNote(int note) {
  int i;
  for(i = 0; i < ARRAY_SIZE; i++) {
    powerSegment(i + 1, seven_seg_digits[note][i]);
  }
}

void displaySettings(){
  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);
  pinMode(SEGMENT_SHARP, OUTPUT);
}
