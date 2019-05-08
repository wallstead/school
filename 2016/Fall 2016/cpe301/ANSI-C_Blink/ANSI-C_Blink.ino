void setup() {
  unsigned char *portDDRB;
  portDDRB = (unsigned char *) 0x24;
  *portDDRB |= 0x80; // setting to output
}

// the loop function runs over and over again forever
void loop() {
  unsigned char *portB;
  portB = (unsigned char *) 0x25;
  *portB |= 0x80; // 10000000
  myDelay(200);
  *portB &= 0x7F; // 01111111 
  myDelay(100);
  *portB |= 0x80; // 10000000
  myDelay(100);
  *portB &= 0x7F; // 01111111 
  myDelay(50);
  
}

void myDelay(unsigned long mSecondsApx) {
  volatile unsigned long i;
  unsigned long endTime = 1000*mSecondsApx;
  for (i = 0; i < endTime; i++);
}

