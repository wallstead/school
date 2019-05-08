void NewDelay(unsigned long); // changed from char to long

void setup() {
  unsigned char *portDDRB;
  portDDRB = (unsigned char *) 0x24;
  *portDDRB |= 0x80;
}

void loop() {
  unsigned char *portB;
  portB = (unsigned char *) 0x25;
  *portB |= 0x80; 
  NewDelay(100);
  *portB &= 0x7F;
  NewDelay(100);
}

void NewDelay(unsigned long mSecondsApx) { // changed from char to long
  volatile unsigned long i; // changed from char to long
  unsigned long endTime = 1000*mSecondsApx;
  for (i = 0; i < endTime; i++);
}

