void NewDelay(unsigned long);

void setup() {
  unsigned char *portDDRB;
  portDDRB = (unsigned char *) 0x24;
  *portDDRB |= 0x80;
  Serial.begin(9600);
}

void loop() {
  unsigned char *portB;
  portB = (unsigned char *) 0x25;
  *portB |= 0x80; 
  NewDelay(1000);
  *portB &= 0x7F;
  NewDelay(1000);
}

void NewDelay(unsigned long mSecondsApx) {
  volatile unsigned long i; 
  unsigned char j;
  unsigned long k;
  unsigned long endTime = 100 * mSecondsApx;
  
  for (i = 0; i < endTime; i++) { // The content of this loop was dividing by 0, I removed the content.
    j = 10;
    do {
      if (j != 1) {
        j = j - 1;
      }
      k = i / j; // this eventually divides by 0 (bad).
    } while (k > 1);
  }
}
