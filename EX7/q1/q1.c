
#include <io.h>
#include <delay.h>

const unsigned char SevenSegment[] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F };

char GetKey();
//*************************************************************************************************
void main(void)
{
char k;
DDRB = 0x7F;
PORTB = 0x00;
DDRD = 0xF0;
while (1)
    {
    k = GetKey();
    if(k != 0xFF) PORTB = SevenSegment[k];
    else PORTB = 0x00;
    }
}
//*************************************************************************************************
char GetKey()
{
unsigned char key_code = 0xFF;
unsigned char columns;
// first row
PORTD.4 = 0;
columns = PIND & 0x07;
if(columns != 0x07)
  {
  switch(columns)
    {
    case 0b110 : key_code = 1; break;
    case 0b101 : key_code = 2; break;
    case 0b011 : key_code = 3; break;
    }
  }  
PORTD.4 = 1;
// second row
PORTD.5 = 0;
columns = PIND & 0x07;
if(columns != 0x07)
  {
  switch(columns)
    {
    case 0b110 : key_code = 4; break;
    case 0b101 : key_code = 5; break;
    case 0b011 : key_code = 6; break;
    }
  }  
PORTD.5 = 1;
// third row
PORTD.6 = 0;
columns = PIND & 0x07;
if(columns != 0x07)
  {
  switch(columns)
    {
    case 0b110 : key_code = 7; break;
    case 0b101 : key_code = 8; break;
    case 0b011 : key_code = 9; break;
    }
  }  
PORTD.6 = 1;
// fourth row
PORTD.7 = 0;
if(!PIND.1) key_code = 0;
PORTD.7 = 1;

PORTD = 0xFF; 
return key_code;
}