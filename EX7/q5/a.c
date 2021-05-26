#include <mega32a.h>
#include <alcd.h>
#include <stdio.h>
#include <mega_temp.h>

unsigned char str[15];


void main(void)
{

lcd_init(16);

while (1)
      {
   
      lcd_gotoxy(0,0);
      sprintf(str,"%f",lm35_res_kel(1));
      lcd_puts(str);
      
      }
}
