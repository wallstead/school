volatile unsigned char *myADCSRA = (unsigned char *)0x7A; 
volatile unsigned char *myADCSRB = (unsigned char *)0x7B;
volatile unsigned char *myADMUX = (unsigned char *)0x7C;
volatile unsigned int  *myDIDR0  = (unsigned int *) 0x7E;
volatile unsigned int  *my7Seg  = (unsigned int *) 0x00; // would set this to an actual address we would use

void adcInit();

unsigned char pollChannel5();

void setup() {
  adcInit();
}

void loop() {
  
}

void adcInit() {
  *myADCSRA = 0b11100000;
  *myADCSRB = 0b01000000;
  *myADMUX  = 0b01000101;
  *myDIDR0  = 0b00100000;
}

unsigned char pollChannel5() {
  
}

