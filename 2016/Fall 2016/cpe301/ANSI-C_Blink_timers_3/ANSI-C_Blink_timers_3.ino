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
  *portB |= 0x80; // turn on bit 6 (0b01000000 => 0x40)
  myDelay(); 
  *portB &= 0x7F; // turn off bit 6 (0b10111111 => 0xBF)
  myDelay(); 
}

void myDelay() {
  /* TODO: generate frequency of 12 kHz = 12000Hz */
  
  /*  period => 1/12000 = 0.00008333333333 seconds = 0.08333 milliseconds
   *  half period for square wave => 0.5(1/12000) = 0.04166666667 milliseconds 
   *  we want the delay to be 0.04166666667 milliseconds
   *  0.04166666667 milliseconds = 41.66666667 microseconds
   *  41.66666667 microseconds/0.0625 microseconds = 666.66666672 ~= 667
   *  we need to subtract 667 from the top of the timer and use pre-scalar of 1
   *  
   */
  *myTCCR1B &= 0xF8; // turn timer to OFF
  *myTCNT1 = (unsigned int) (65536 - 667);
  *myTCCR1B |= 0x01; // turn timer ON with pre-scalar of 1 (0b001 => 0x01)
  while((*myTIFR1 & 0x01)!=1); // once overflow flag is 1, we will stop  
  *myTCCR1B &= 0xF8; // turn timer to OFF (prof. Egbert says this is optional)                          
  *myTIFR1 |= 0x01;// clear overflow flag bit (by setting to 1 for some reason)
}
