#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>       // sprintf براي استفاده از تابع stdio فراخواني کتابخانه //
 
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))    // adc از خط 7 تا خط 16 دستورات مربوط به //
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(10);
ADCSRA|=(1<<ADSC);
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}
 
void main(void)
{
int     a=0 ;              // در ان adc براي ريختن مقادير خوانده شده از int تعريف متغير از نوع //
float   Temperature ;      // براي ريختن مقادير دما در ان float تعريف متغير از نوع //
char    Buffer_LCD[16];    // کاراکتري نمايش دهيم lcd براي تبديل مقادير دما به  رشته اي از کاراکتر تا بتوانيم ان را روي char تعريف متغير از نوع //
 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
 
ADMUX=ADC_VREF_TYPE;        //که توسط خود کدويژن با توجه به تنظيماتي که انجام داده ايم ايجاد مي شوند adc از خط 30 تا 32 رجيسترهاي مربوط به //
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
 
lcd_init(16);    //(LCD بررسي اتصال) LCD پيکره بندي //
lcd_clear();    // LCD پاک کردن //
 
while (1)
      { 
      a=read_adc(0);              // a خواندن عددي بين 0 تا 1023 که نشان دهنده مقدار ولتاژ انالوگ روي ان پين ميکرو است و ريختن ان در متغير //
      Temperature=(a/2.054) ;    // را به دما تبديل مي کند ADC مقادير خوانده شده LM35 دستور روبرو با توجه به ديتاشيت //                           
      sprintf(Buffer_LCD,"T=%3.1f",Temperature);  // LCD براي نمايش روي Buffer_LCD تبديل مقادير دما به رشته اي از کاراکتر و ذخيره ان در متغير //
      lcd_gotoxy(0,0);        // رفتن به ستون 0 و سطر 0 //
      lcd_puts(Buffer_LCD);   // ذخيره شده اند Buffer_LCD نمايش مقادير دما که به صورت کاراکتر در متغير //
      lcd_gotoxy(7,0);       // رفتن به ستون 7 و سطر 0 //
      lcd_putsf("C");       // بعد از دما به عنوان سانتي گراد LCD روي C نوشتن کاراکتر //
      lcd_gotoxy(2,1);     // رفتن به ستون 2 و سطر 1 //
      lcd_putsf("Hossein-Heidari-nejad");    // LCD روي Hossein-Heidari-nejad نوشتن متن //
      delay_ms(500);            /* ايجاد تاخير به مدت 500 ميلي ثانيه يا 0.5 ثانيه*/      
      }
}