#define RDA 0x80 // Received Data Available ~= RXC
#define TBE 0x20 // Transmitter Buffer Empty ~= DRE (Data Register Empty)
#define TIMSK1_ADDR (unsigned char *) 0x6F
#define TIMSK1_ICIE_MASK  0x20
#define TIMSK1_OCIEB_MASK 0x04
#define TIMSK1_OCIEA_MASK 0x02
#define TIMSK1_TOIE_MASK  0x01

volatile unsigned char *myTCCR1A = (unsigned char *) 0x80; // Timer/Counter Control Register A
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81; // Timer/Counter Control Register B
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82; // Timer/Counter Control Register C
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F; // Timer/Counter Interrupt Mask Register
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84; // Timer/Counter Count Register (low & high)
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36; // Timer/Counter Interrupt Flag Register

volatile unsigned char *myUCSR0A = (unsigned char *)0xC0; // USART MSPIM Control and Status Register A
volatile unsigned char *myUCSR0B = (unsigned char *)0xC1; // USART MSPIM Control and Status Register B
volatile unsigned char *myUCSR0C = (unsigned char *)0xC2; // USART MSPIM Control and Status Register C
volatile unsigned int  *myUBRR0  = (unsigned int *) 0xC4; // USART0 Baud Rate Register Low Byte
volatile unsigned char *myUDR0   = (unsigned char *)0xC6; // USART I/O Data Register

volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile unsigned char charRead;
volatile int numTicks;

void timerInit();
void U0init(long U0baud);
unsigned char U0kbhit();
unsigned char U0getchar();
void U0putchar(unsigned char U0pdata);

ISR(TIMER1_OVF_vect) {
  *myTCCR1B &= 0xF8; // stop timer
  *myTCNT1 = (unsigned int) (65536 - numTicks); // reload timer
  *myTCCR1B |= 0x01; // turn timer ON with pre-scalar of 1
  *portB ^= 0x40; // toggle portb
  *myTIFR1 |= 0x01; // clear overflow flag bit (by setting to 1 for some reason)
}

void setup() {
  /* Initialize Timer1 for NORMAL mode */
  *myTCCR1A = 0;
  *myTCCR1B = 0; 
  *myTCCR1C = 0;
  *myTIMSK1 = 0; // Timer 1 should have no interrupts
 
  *portDDRB |= 0x40;  // Initialize GPIO PortB as output

  U0init(9600); // initialize serial port on USART0
  timerInit();
  
}
 
// the loop function runs over and over again forever
void loop() {
  while (U0kbhit()==0){}; // wait for RDA = true
  charRead = U0getchar();    // read character
  
  switch(charRead) {
    case 'a':
      numTicks = 18182;
      break;
    case 'A': // A#
      numTicks = 17167;
      break;
    case 'b':
      numTicks = 16194;
      break;
    case 'c':
      numTicks = 15296;
      break;
    case 'C': // C#
      numTicks = 14440;
      break;
    case 'd':
      numTicks = 13629;
      break;
    case 'D': // D#
      numTicks = 12821;
      break;
    case 'e':
      numTicks = 12140;
      break;
    case 'f':
      numTicks = 11461;
      break;
    case 'F': // F#
      numTicks = 10811;
      break;
    case 'g':
      numTicks = 10204;
      break;
    case 'G': // G#
      numTicks = 9627;
      break;
    default:
      U0putchar('a');
      numTicks = 18182;
  }
}



void timerInit() {
  unsigned char *portTimerCounterInterruptMaskRegister;
  unsigned char shadow;

  portTimerCounterInterruptMaskRegister = TIMSK1_ADDR;

  shadow = *portTimerCounterInterruptMaskRegister;
  shadow &= ~(TIMSK1_ICIE_MASK | TIMSK1_OCIEB_MASK | TIMSK1_OCIEA_MASK | TIMSK1_TOIE_MASK);
  shadow |= TIMSK1_TOIE_MASK;
  *portTimerCounterInterruptMaskRegister = shadow;

  numTicks = 18182; // do a by default
}

void U0init(long U0baud) {
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U0baud - 1);
  *myUCSR0A = 0x20; // 0010 0000
  *myUCSR0B = 0x18;
  *myUCSR0C = 0x06;
  *myUBRR0  = tbaud;
}

unsigned char U0kbhit() {
  unsigned char rdaIsSet = *myUCSR0A & RDA;
  return rdaIsSet;
}

unsigned char U0getchar() {
  while (U0kbhit()==0) {}; // wait until data available (double-checking for safety)
  return *myUDR0;
}

void U0putchar(unsigned char U0pdata) {
  unsigned char transmitterBufferEmpty = *myUCSR0A & TBE; // "If UDREn is one, the buffer is empty, and therefore ready to be written."
  while (transmitterBufferEmpty==0) {}; // wait until it is ready
  *myUDR0 = U0pdata; // write character
}

