volatile unsigned char *myTCCR1A = (unsigned char *) 0x80; // Timer/Counter Control Register A
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81; // Timer/Counter Control Register B
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82; // Timer/Counter Control Register C
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F; // Timer/Counter Interrupt Mask Register
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84; // Timer/Counter Count Register (low & high)
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36; // Timer/Counter Interrupt Flag Register
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile byte byteRead =0;

void myDelayFor(int);

void setup() {
  /* Initialize Timer1 for NORMAL mode */
  *myTCCR1A = 0;
  *myTCCR1B = 0; 
  *myTCCR1C = 0;
  *myTIMSK1 = 0; // Timer 1 should have no interrupts
 
  *portDDRB |= 0x40;  // Initialize GPIO PortB as output

  Serial.begin(115200);
}
 
// the loop function runs over and over again forever
void loop() {

   /*  check if data has been sent from the computer: */
  if (Serial.available()) {
    /* read the most recent byte */
    byteRead = Serial.read();
  }
  
  switch(byteRead) {
    case 'a':
      myDelayFor(18182);
      break;
    case 'A':
      myDelayFor(17167); // A#
      break;
    case 'b':
      myDelayFor(16194);
      break;
    case 'c':
      myDelayFor(15296);
      break;
    case 'C':
      myDelayFor(14440); // C#
      break;
    case 'd':
      myDelayFor(13629);
      break;
    case 'D':
      myDelayFor(12821); // D#
      break;
    case 'e':
      myDelayFor(12140);
      break;
    case 'f':
      myDelayFor(11461);
      break;
    case 'F':
      myDelayFor(10811); // F#
      break;
    case 'g':
      myDelayFor(10204);
      break;
    case 'G':
      myDelayFor(9627); // G#
      break;
    default:
      Serial.write(byteRead);
      myDelayFor(18182);
  }

//myDelayFor(284);

//  myDelayFor('A');
//  *portB ^= 0x40;

  
}

void myDelayFor(int numTicks) {
  *myTCCR1B &= 0xF8; // turn timer to OFF
  *myTCNT1 = (unsigned int) (65536 - numTicks); // for A
  *myTCCR1B |= 0x01; // turn timer ON with pare-scalar of 1
  while(!(*myTIFR1 & 0x01)); // once overflow flag is 1, we will stop  
  *myTCCR1B &= 0xF8; // turn timer to OFF (prof. Egbert says this is optional)                          
  *myTIFR1 |= 0x01; // clear overflow flag bit (by setting to 1 for some reason)

  *portB ^= 0x40;
}

