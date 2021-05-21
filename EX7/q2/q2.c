#include <mega8.h>
#include <string.h>
#include <delay.h>


#include <alcd.h>

#define DELETE               10
#define ENTER                11
#define LOCK                 PORTC.0                  

char GetKey();

// Declare your global variables here
char sys_code[] = "1394";
char usr_code[sizeof(sys_code)] = "";
char usr_code_idx = 0;
//*************************************************************************************************
void main(void)
{
char k;

DDRC.0 = 1;
DDRD = 0xF0;

lcd_init(16);

while (1)
  {                       
  LOCK = 0;
  lcd_clear();
  lcd_gotoxy(3, 0);
  lcd_putsf("Lock : OFF");
  lcd_gotoxy(0, 1);
  lcd_putsf("Pass: ");
GET_KEY:
  do 
    { 
    k = GetKey(); 
    } while(k == 0xFF);
  delay_ms(500);
  while(GetKey() != 0xFF); 
  if(k == DELETE)
    {
    strcpyf(usr_code, "");
    usr_code_idx = 0;
    }
  else if(k == ENTER)
    {
    usr_code[usr_code_idx] = '\0';
    if(strcmp(usr_code, sys_code) == 0)
      {
      LOCK = 1;
      lcd_clear();
      lcd_gotoxy(3, 0);
      lcd_putsf("Lock : ON");
      while(GetKey() != DELETE);
      }
    else
      {
      lcd_clear();
      lcd_putsf("Invalid Password");
      delay_ms(2000);
      }
    strcpyf(usr_code, "");
    usr_code_idx = 0;
    }
  else
    {
    if(usr_code_idx < sizeof(usr_code) - 1)
      {
      usr_code[usr_code_idx] = k + 0x30; 
      usr_code_idx++;
      lcd_putchar('*');
      }
    goto GET_KEY;
    } 
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
columns = PIND & 0x07;
if(columns != 0x07)
  {
  switch(columns)
    {
    case 0b110 : key_code = ���DELETE; break;
    case 0b101 : key_code = 0; break;
    case 0b011 : key_code = ENTER; break;
    }
  }  
PORTD.7 = 1;

PORTD = 0xFF; 
return key_code;
}