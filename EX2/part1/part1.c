#include <mega16.h>

// Declare your global variables here
static unsigned  int time_count ;//.5sec counter
// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{  

     // 12 MHz/8 = 1500 kHz, which has a period of 1/1500 kHz = 0.66 µs
    //  225 * 0.66 µs = 150 µs
    //  3333 * 150 µs = 500 ms  
    //  256 – 225 = 31 
        
    TCNT0 = 31;
       ++time_count; /*increment .5 second counter*/
    if (time_count == 3333)
  {
        PORTC.0 = (PORTC.0 ^ 1); /*complement port bit to blink LED*/
        time_count = 0; /*reset time counter for next .5 second*/ 
   }



}

void main(void)
{

    DDRC = 0x01; /*set lsb for output*/

    /*set timer 0 prescaler to clk/8*/
    TCCR0=0x02;
    TCNT0=31;
   

    /* unmask Timer 0 overflow interrupt*/
    TIMSK=0x01;

    /* enable interrupts */
    #asm("sei")
    while(1) 
    {

      }
}