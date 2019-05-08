#define RDA 0x80
#define TBE 0x20  
volatile unsigned char *myUCSR0A = (unsigned char *) 0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *) 0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *) 0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *)  0x00C4;
volatile unsigned char *myUDR0   = (unsigned char *) 0x00C6;

void U0init(int U0baud);
unsigned char U0kbhit();
unsigned char U0getchar();
void U0puthex(unsigned char U0ptohex);
void U0putstr(unsigned char *string);
void U0putchar(unsigned char U0pdata);

void setup()
{
 // initialize the serial port on USART0:
 U0init(9600);
}
void loop()
{
  unsigned char cs1;
  while (U0kbhit()==0){}; // wait for RDA = true
  cs1 = U0getchar();    // read character
  U0putchar('a');     // echo character
}

// function to initialize USART0 to "int" Baud, 8 data bits,
// no parity, and one stop bit. Assume FCPU = 16MHz.

void U0init(int U0baud)
{
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 *myUCSR0A = 0x20;
 *myUCSR0B = 0x18;
 *myUCSR0C = 0x06;
 *myUBRR0  = tbaud;
}
//
// Read USART0 RDA status bit and return non-zero true if set
//
unsigned char U0kbhit() {
  unsigned char rdaIsSet = *myUCSR0A & RDA;
  return rdaIsSet;
}
//
// Read input character from USART0 input buffer
//
unsigned char U0getchar() {
  while (U0kbhit() == 0) {}; // wait until data available (double-checking for safety)
  return *myUDR0;
}

void U0puthex(unsigned char U0ptohex) {

  while ((*myUCSR0A & TBE) == 0) {};
  U0putchar('0');
  while ((*myUCSR0A & TBE) == 0) {};
  U0putchar('x');
  
  unsigned int firstChar = U0ptohex & 0b11110000;
  while ((*myUCSR0A & TBE) == 0) {};
  U0putchar(firstChar);
  while ((*myUCSR0A & TBE) == 0) {};
  U0putchar('\n');
  
}


//
// Wait for USART0 TBE to be set then write character to
// transmit buffer
//

void U0putstr(char *string) {
  while(*string) {
     U0putchar(*string);
     string++;
  }
}


void U0putchar(unsigned char U0pdata) {
  unsigned char transmitterBufferEmpty = *myUCSR0A & TBE; // "If UDREn is one, the buffer is empty, and therefore ready to be written."
  while (transmitterBufferEmpty==0) {}; // wait until it is ready
  *myUDR0 = U0pdata; // write character
}


