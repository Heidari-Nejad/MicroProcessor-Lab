 

#include <io.h>
#include <mega16.h>
#include <delay.h>
#include <stdlib.h>
#include <math.h>


void prepare7SegDisplay(int floor){
    PORTB.0 = floor%2;
    PORTB.1 = floor==2||floor==3||floor==6||floor==7;
    PORTB.2 = floor==4||floor==5||floor==6||floor==7;
    PORTB.3 = floor==8||floor==9;
}
void turnOnLED(int requsted_floor) {
	if (requsted_floor == 1) PORTC.5 = 0;
	else if (requsted_floor == 2) PORTC.6 = 0;
	else if (requsted_floor == 3) PORTC.7 = 0;
}
void turnOffLED(int requsted_floor) {
	if (requsted_floor == 1) PORTC.5 = 1;
	else if (requsted_floor == 2) PORTC.6 = 1;
	else if (requsted_floor == 3) PORTC.7 = 1;
}
int getCurrentFloor(){
    return PINA.2 * 3 +  PINA.1 * 2 + PINA.0;
}

int getInBtnsFloor(){
    return PINC.2 * 3 +  PINC.1 * 2 + PINC.0;
}
int getOutBtnsFloor(){
    return PIND.2 * 3 +  PIND.1 * 2 + PIND.0;
}



short getDirection(){
    return !PINA.6?(PINA.7?-1:0):1;
}



short isElevatorEmpty(){
    return PINB.5==1;
}
short isElevatorOk() {
	return PINB.6 == 1;
}
short isElevatorOverWeight(){
    return PINB.7==1;
}

void initialization();


void main(void)
{	
	struct pQueue f_queue;
	initQueue(&f_queue);

	initialization();
	
    while (1){
		
		int in_req = getInBtnsFloor(), out_req = getOutBtnsFloor();
		int curr_floor = getCurrentFloor();
		prepare7SegDisplay(curr_floor);
	
		
		if (in_req!=0) {
			if(curr_floor!=in_req)
				if (isElevatorOverWeight() == 0)
					turnOnLED(in_req);
			
			
		}
		if (out_req!=0) {
			if (curr_floor != out_req)
				turnOnLED(out_req);
		
		}

		if (getDirection() != 0) {
			turnOffLED(curr_floor);

		}
		
		
		
    }        
}

void initialization(){
	
	DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
	PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);


	
	DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
	PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

	DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
	PORTC=(1<<PORTC7) | (1<<PORTC6) | (1<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

	DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
	PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

	
	TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
	TCNT0=0x00;
	OCR0=0x00;


	TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;


	ASSR=0<<AS2;
	TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
	TCNT2=0x00;
	OCR2=0x00;

	TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

	
	MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
	MCUCSR=(0<<ISC2);

	
	UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

	
	ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
	SFIOR=(0<<ACME);

	
	ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

	
	SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

	
	TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

}





