unsigned char flag = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  analogRead(A0);
  
  digitalWrite(6, flag);
  flag = !flag;    
}
