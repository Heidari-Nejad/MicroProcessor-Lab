
#include <mega16.h>
#include <delay.h>

int time;
int delay;
int motorState;
int states[4][4] = {{1, 0, 0, 1},{1, 0, 1, 0},{0, 1, 1, 0},{0, 1, 0, 1}};

interrupt [TIM0_OVF] void timer0_ovf_isr(void){
    TCNT0 = 0x0C;
    if(time == 1) {
        if(delay == 0) {
            PORTA.0 = states[motorState][0];                                   
            PORTA.1 = states[motorState][1];                                 
            PORTA.2 = states[motorState][2];
            PORTA.3 = states[motorState][3];}
        
        if(delay > 5 && delay <= 10) {
            PORTA = 0x00;}  
        
        if(delay == 10){
            delay = 0;  
            if(motorState < 3) {
                ++motorState;
            } else {
                motorState = 0;
                time = 0;
            }
        } else {
            ++delay;
        }   
    }
}
void main(void){ 
    delay = 0;  
    motorState = 0;
    time = 0;
    DDRC = 0x00;   
    PINC = 0x00;   
    DDRA = 0xff;  
    PORTA = 0x00;
    TCCR0 = (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (0<<CS00);
    TCNT0 = 0x0C;
    OCR0 = 0x00;
    TCCR1A = (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B = (0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
    ASSR = 0<<AS2;
    TCCR2 = (0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
    TCNT2 = 0x00;
    OCR2 = 0x00;
    TIMSK =(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    MCUCR =(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR =(0<<ISC2);
    UCSRB =(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
    ACSR =(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
    SFIOR =(0<<ACME);
    ADCSRA =(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
    SPCR =(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
    TWCR =(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

    #asm("sei")
    while (1) {
        if(time == 0 && PINC.2 == 0) {   
             time = 1;
             delay = 0;  
        }
    }
}
