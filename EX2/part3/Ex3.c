#include <mega16.h>
#include <delay.h>
// Declare your global variables here
int i=0;

void main(void)
{
// Declare your local variables here
DDRA =0x00;
DDRB =0xFF;

while (1)
      {
      // Place your code here
             if (PINA.0==1){
                for(i=0;i<8;i++){
                    PORTB = PORTB *2 ;
                    delay_ms(100);   
                } 
                for(i=0;i<8;i++){
                    PORTB = PORTB /2 ;
                    delay_ms(100);   
                } 
             }
                
      }
}