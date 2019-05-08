volatile unsigned char *myTCCR1A = (unsigned char *) 0x80; // Timer/Counter Control Register A
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81; // Timer/Counter Control Register B
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82; // Timer/Counter Control Register C
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F; // Timer/Counter Interrupt Mask Register
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84; // Timer/Counter Register (low & high)
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36; // Timer/Counter Interrupt Flag Register
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;

void myDelay(unsigned long);

void setup() {
  /* Initialize Timer1 for NORMAL mode */
  *myTCCR1A = 0;
  *myTCCR1B = 0; 
  *myTCCR1C = 0;
  *myTIMSK1 = 0; // Timer 1 should have no interrupts
 
  //*portDDRB |= 0x80; Question says this is already done
}
 
void loop() {
  
}

void shutterControl(int shutterSpeed) {
  // assuming shutter starts closed (off)

  *myTCCR1B &= 0xF8; // turn timer to OFF

  /*  base period => 1 second = 1000 milliseconds
   *  we want the delay to be 1000 milliseconds
   *  1000 milliseconds = 1,000,000 microseconds
   *  1,000,000 microseconds/64 microseconds = 15,625
   *  we need to subtract 15,625 from the top of the timer for 1 second
   *  
   */
  long toSubtract = 15625;
  
  switch(shutterSpeed) {
  case 0:
    // no change 
    break;
  case 1:
    toSubtract*(0.5); // 1/2
    break;
  case 2:
    toSubtract*(0.25); // 1/4
    break;
  case 3:
    toSubtract*(0.125); // 1/8
    break;
  case 4:
    toSubtract*(0.06666666667); // 1/15
    break;
  case 5:
    toSubtract*(0.03333333333); // 1/30
    break;
  case 6:
    toSubtract*(0.01666666667); // 1/60
    break;
  case 7:
    toSubtract*(0.008); // 1/125
    break;
  case 8:
    toSubtract*(0.004); // 1/250
    break;
  case 9:
    toSubtract*(0.002); // 1/500
    break;
  case 10:
    toSubtract*(0.001); // 1/1000
    break;
  default:
    //something   
    toSubtract*(1); // nothing by default
  }

  *myTCNT1 = (unsigned int) (65536 - toSubtract);
  *myTCCR1B |= 0x03; // turn timer ON with pre-scalar of 64 (0b011 => 0x03)

  *portB |= 0x80; // turn shutter on (open)
  
  while((*myTIFR1 & 0x01)!=1); // once overflow flag is 1, we will stop  
  *myTCCR1B &= 0xF8; // turn timer to OFF (prof. Egbert says this is optional)                          
  *myTIFR1 |= 0x01;// clear overflow flag bit (by setting to 1 for some reason)

  *portB &= 0x7F; // turn shutter off (closed)
}
