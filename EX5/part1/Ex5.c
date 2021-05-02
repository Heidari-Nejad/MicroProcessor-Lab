#include <mega16.h>
#include <delay.h>
#define LCD_DATA PORTB                      // تعریف پورت بی برای ال سی دی
#define ctrl PORTD                          // تعریف پورت دی برای پین های کنترل
#define en PIND.2                        
#define rw PIND.1                     
#define rs PIND.0
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data); 
void main(void)
{
unsigned char i,HeidariNejad[11]="HeidariNejad";// عبارتی که میخواهیم روی ال سی دی نمایش داده شود
DDRB=0xFF;
DDRD=0x07;                 
init_LCD();                      // راه اندازی اولیه ی ال سی دی 
LCD_cmd(0x0F);
delay_ms(1000);
LCD_cmd(0x14);                   
LCD_cmd(0x14);
LCD_cmd(0x14);
for(i=0;i<10;i++)                 // دادن کاراکترهای عبارت مورد نظر به ال سی دی جهت نمایش
{
    LCD_write(HeidariNejad[i]);   
    delay_ms(10);
}
}
--------------------------------------
void init_LCD(void)     // تابع راه اندازی اولیه ی ال سی دی 
{
    LCD_cmd(0x38);       // راه اندازی ال سی دی شانزده تایی برای مد هشت تایی                     
    delay_ms(1);
    LCD_cmd(0x01);        // پاک کردن صفحه                         
    delay_ms(1);
    LCD_cmd(0x0E);        // روشن کردن کرسر                
    delay_ms(1);
    LCD_cmd(0x80);         // بردن کرسر به اولین مکان از اولین سطر            
    delay_ms(1);
    return;
}

void LCD_cmd(unsigned char cmd)  // تابع ارسال دستور
{
    LCD_DATA=cmd;
    ctrl=0x04;               // یک کردن پین اینیبل
    delay_ms(1);
    ctrl=0x00;                // صفر کردن پین اینیبل
    delay_ms(50);
    return;
}

void LCD_write(unsigned char data)   // تابع ارسال داده 
{
    LCD_DATA= data;
    ctrl=0x05;                 // یک کردن پین های اینیبل و انتخاب رجیستر
    delay_ms(1);
    ctrl=0x01;
    delay_ms(50);
    return ;
}