volatile unsigned char *portDDRB = (unsigned char*) 0x24;
volatile unsigned char *portDataB = (unsigned char*) 0x25;
volatile unsigned char *portPinB = (unsigned char*) 0x23;
volatile unsigned char *portDDRK = (unsigned char*) 0x107;
volatile unsigned char *portDataK = (unsigned char*) 0x108;

char test[16] = {'A','B','C','D','E','F','0','1','2','3','4','5','6','7','8','9'};
volatile unsigned int index = 0;

void setup() {
  *portDDRB &= 0b00000000; // set last 4 as inputs
  *portPinB |= 0b00001111; // turn on pullup resistor for last 4
  
  *portDDRK |= 0b11111111; // setting up port k
  Serial.begin(9600);
}


void loop() {

  unsigned char value = *portPinB & 0b00001111;
  
  Serial.println(value, BIN);

  *portDataK = 0; 
  switch (value) { // 0->9 A->F
    case 0:
      *portDataK |= 0b00111111; // 0 */goes from right to left*/
      break;
    case 1:
      *portDataK |= 0b00000110; // 1 done
      break;
    case 2:
      *portDataK |= 0b01011011; // 2 done
      break;
    case 3:
      *portDataK |= 0b01001111; // 3 done
      break;
    case 4:
      *portDataK |= 0b01100110; // 4 done
      break;
    case 5:
      *portDataK |= 0b01101101; // 5 done
      break;
    case 6:
      *portDataK |= 0b01111101; // 6 done
      break;
    case 7:
      *portDataK |= 0b00000111; // 7 done
      break;
    case 8:
      *portDataK |= 0b01111111; // 8 done
      break;
    case 9:
      *portDataK |= 0b01100111; // 9 done
      break;
    case 10:
      *portDataK |= 0b01110111; // A done
      break;
    case 11:
      *portDataK |= 0b01111100; // b done
      break;
    case 12:
      *portDataK |= 0b00111001; // C done
      break;
    case 13:
      *portDataK |= 0b01011110; // D done
      break;
    case 14:
      *portDataK |= 0b01111001; // E done
      break;
    case 15:
      *portDataK |= 0b01110001; // F done
      break;
    default:
      *portDataK |= 0b00111111; // 0 by default
  }
}

