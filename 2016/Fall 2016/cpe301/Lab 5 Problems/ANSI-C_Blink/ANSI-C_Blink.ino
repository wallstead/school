void myDelay(unsigned long);

void setup() {
  unsigned char *portDDRB;
  portDDRB = (unsigned char *) 0x24;
  *portDDRB |= 0x80; // setting to output
}

// the loop function runs over and over again forever
void loop() {
  unsigned char *portB;
  portB = (unsigned char *) 0x25;
  *portB |= 0x80; 
  myDelay(1000); // REPLACED {}s with ()
  *portB &= 0x7F; // replaced : with ;
  myDelay(1000);// REPLACED {}s with (), removed ,
  
}

void myDelay(unsigned long mSecondsApx) {
  volatile unsigned long i;
  unsigned long endTime = 1000*mSecondsApx;
  for (i = 0; i < endTime; i++);
}

