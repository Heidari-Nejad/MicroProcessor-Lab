#include <io.h>
#include <stdlib.h>
#include <delay.h>
#include <alcd.h>

#define STEPPER_PORT         PORTC
#define SET                  PIND.6
#define OK                   PIND.7

//-------------------------------------------------------------------------------------------------
//global variables
const unsigned char StepCodes[]={0b0011, 0b0010, 0b0110 ,0b0100 ,0b1100 ,0b1000 ,0b1001 ,0b0001};
unsigned char Step = 0;
//*************************************************************************************************
void main(void)
{
int i;
char str[4];

PORTC = 0x00;
DDRC = 0x0F;

PORTD = 0xC0;
DDRD = 0x00;

lcd_init(16);

while (1)
  {
  lcd_clear();
  lcd_putsf("Angle : ");
  itoa(Step * 45, str);
  lcd_gotoxy(7, 1);
  lcd_puts(str);
  
  while(SET && OK);
  if(!SET)
    {
    Step = (++Step % 8);
    delay_ms(50);
    while(!SET);
    continue;
    }
  else if(!OK)
    {
    delay_ms(50);
    while(!OK);
    for(i = 0; i < Step; i++)
      {
      STEPPER_PORT = StepCodes[i];
      delay_ms(100);
      }
    }
  };
}
