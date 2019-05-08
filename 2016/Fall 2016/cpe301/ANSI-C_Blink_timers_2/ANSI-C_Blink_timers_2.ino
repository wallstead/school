volatile unsigned char *myTCCR1A = (unsigned char *) 0x80; // Timer/Counter Control Register A
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81; // Timer/Counter Control Register B
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82; // Timer/Counter Control Register C
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F; // Timer/Counter Interrupt Mask Register
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84; // Timer/Counter Register (low & high)
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36; // Timer/Counter Interrupt Flag Register
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;

void myDelay();

void setup() {
  /* Initialize Timer1 for NORMAL mode */
  *myTCCR1A = 0;
  *myTCCR1B = 0; 
  *myTCCR1C = 0;
  *myTIMSK1 = 0; // Timer 1 should have no interrupts
 
  *portDDRB |= 0x80;  // Initialize GPIO PortB
}

void loop() {
  *portB |= 0x40; // turn on bit 6 (0b01000000 => 0x40)
  myDelay(); 
  *portB &= 0xBF; // turn off bit 6 (0b10111111 => 0xBF)
  myDelay(); 
}

void myDelay() {
  /* TODO: generate frequency of 440Hz */
  
  /*  period => 1/440 = 0.002222222222 seconds = 2.22 milliseconds
   *  half period for square wave => 0.5(1/440) = 1.136363636 milliseconds 
   *  we want the delay to be 1.136363636 milliseconds
   *  1.136363636 milliseconds = 1136.363636 microseconds
   *  1136.363636 microseconds/4 microseconds = 284.090909 ~= 284
   *  we need to subtract 284 from the top of the timer
   *  
   */
  *myTCCR1B &= 0xF8; // turn timer to OFF
  *myTCNT1 = (unsigned int) (65536 - 284);
  *myTCCR1B |= 0x03; // turn timer ON with pre-scalar of 64 (0b011 => 0x03)
  while((*myTIFR1 & 0x01)!=1); // once overflow flag is 1, we will stop  
  *myTCCR1B &= 0xF8; // turn timer to OFF (prof. Egbert says this is optional)                          
  *myTIFR1 |= 0x01;// clear overflow flag bit (by setting to 1 for some reason)
}
