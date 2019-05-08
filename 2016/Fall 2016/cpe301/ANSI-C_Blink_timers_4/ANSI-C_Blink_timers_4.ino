volatile unsigned char *myTCCR1A = (unsigned char *) 0x80; // Timer/Counter Control Register A
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81; // Timer/Counter Control Register B
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82; // Timer/Counter Control Register C
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F; // Timer/Counter Interrupt Mask Register
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84; // Timer/Counter Register (low & high)
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36; // Timer/Counter Interrupt Flag Register
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;

void genFreq();

void setup() {
  /* Initialize Timer1 for NORMAL mode */
  *myTCCR1A = 0;
  *myTCCR1B = 0; 
  *myTCCR1C = 0;
  *myTIMSK1 = 0; // Timer 1 should have no interrupts
 
  *portDDRB |= 0x80;  // Initialize GPIO PortB
}

void loop() {
  genFreq();  
}

void genFreq() {
  /* TODO: generate frequency of 500 Hz, 30% up <---> 70% down */
  
  /*  period => 1/500 = 0.002 seconds = 2 milliseconds
   *  30% period for square wave => 0.3(1/500) = 0.6 milliseconds 
   *  we want the delay to be 0.6 milliseconds for UP
   *  0.6 milliseconds = 600 microseconds
   *  600 microseconds/4 microseconds = 150
   *  we need to subtract 150 from the top of the timer and use pre-scalar of 64
   */

  *portB |= 0x40; // turn on bit 6 (0b01000000 => 0x40) // turn on bit 6
  
  *myTCCR1B &= 0xF8; // turn timer to OFF
  *myTCNT1 = (unsigned int) (65536 - 150);
  *myTCCR1B |= 0x03; // turn timer ON with pre-scalar of 64 (0b011 => 0x03)
  while((*myTIFR1 & 0x01)!=1); // once overflow flag is 1, we will stop  
  *myTCCR1B &= 0xF8; // turn timer to OFF (prof. Egbert says this is optional)                          
  *myTIFR1 |= 0x01;// clear overflow flag bit (by setting to 1 for some reason)

  /*  period => 1/500 = 0.002 seconds = 2 milliseconds
   *  70% period for square wave => 0.7(1/500) = 1.4 milliseconds 
   *  we want the delay to be  1.4 milliseconds for DOWN
   *  1.4 milliseconds = 1400 microseconds
   *  1400 microseconds/4 microseconds = 350
   *  we need to subtract 350 from the top of the timer and use pre-scalar of 64
   */

  *portB &= 0xBF; // turn off bit 6
  
  *myTCNT1 = (unsigned int) (65536 - 350);
  *myTCCR1B |= 0x03; // turn timer ON with pre-scalar of 64 (0b011 => 0x03)
  while((*myTIFR1 & 0x01)!=1); // once overflow flag is 1, we will stop  
  *myTCCR1B &= 0xF8; // turn timer to OFF (prof. Egbert says this is optional)                          
  *myTIFR1 |= 0x01;// clear overflow flag bit (by setting to 1 for some reason)
}
