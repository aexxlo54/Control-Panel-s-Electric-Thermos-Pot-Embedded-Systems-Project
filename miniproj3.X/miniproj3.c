// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdlib.h>
#include <stdio.h> //header file for sprintf

#define _XTAL_FREQ 8000000
#define ON 1
#define OFF 0
#define RS PORTAbits.RA0
#define EN PORTAbits.RA1


void DelaySeconds();
void lcdInit();
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void select_Item();

unsigned int z;
unsigned char s1[17]={" BOILING... "};
unsigned char s2[17]={" DISPENSING... "};
unsigned char s3[17]={" KEEP WARM... " };
unsigned char s4[17]={" WELCOME... "};

int i;

void main()
{
    TRISA=0XFC;
    TRISB=0X3F;
    TRISC=0XF8;
    TRISD=0X00;
    
    OSCCON=0X75;
    ANSELH=0X00;
    ADCON0=0b11000001;
    ADCON1=0b10000000;
    
    PORTBbits.RB0=1;
    PORTBbits.RB1=1;
    PORTBbits.RB2=1;
    
    PORTBbits.RB3=1;
    PORTBbits.RB4=1;
    PORTBbits.RB5=1;
    PORTBbits.RB6=1;
    
    PORTEbits.RE3=1;
    
    PORTCbits.RC0=OFF;
    PORTCbits.RC1=OFF;
    PORTCbits.RC2=OFF;
    
    lcdInit();
        __delay_ms(300);
    lcdclear();
        
    
    
    while(1)
    {
        //Temp button
        if (PORTBbits.RB0==0)
        {  
            PORTCbits.RC0=ON;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=OFF;
            for (i=0;i<17;i++)
            {
                lcdInit();
                lcddata(s3[i]);
            }
        }
        
        if (PORTBbits.RB1==0)
        {
            PORTCbits.RC0=ON;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=OFF;
            for (i=0;i<17;i++)
            {
                lcdInit();
                lcddata(s3[i]);
            }
        }
        
        if (PORTBbits.RB2==0)
        {
            PORTCbits.RC0=OFF;
            PORTCbits.RC1=ON;
            PORTCbits.RC2=OFF;
            for (i=0;i<17;i++)
            {
                lcdInit();
                lcddata (s1[i]);
            }
        }
        
        //Main button
        if(PORTBbits.RB3==0)
        {
            PORTCbits.RC0=OFF;
            PORTCbits.RC1=ON;
            PORTCbits.RC2=OFF;
            for (i=0;i<17;i++)
            {
                lcdInit();
                lcddata (s1[i]);
            }
        }
        
        if(PORTBbits.RB4==0)
        {
            PORTCbits.RC0=ON;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=ON;
            for (i=0;i<15;i++)
            {
                lcdInit();
                lcddata (s2[i]);
            }
        }
        
        if (PORTBbits.RB5==0)
        {
            PORTCbits.RC0=ON;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=ON;
            for (i=0;i<15;i++)
            {
                lcdInit();
                lcddata (s2[i]);
            }
        }
        
        if (PORTEbits.RE3==0)
        {
            PORTCbits.RC0=OFF;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=OFF;
        }
        
        else
        {
            lcdcmd(0x0C);
            if(PORTBbits.RB6==1)
                select_Item();
        }
    }
}

void DelaySeconds(z)
{
    unsigned char x,y;
    for (y=0;y<z;y++)
    {
        for (x=0;x<100;x++)
        {
             __delay_ms(10);
        }
    }
}

void lcdInit()
{
    lcdcmd(0x38);
    lcdcmd(0x0E);
}

void lcdcmd(unsigned char d1)
{
    PORTD=d1;
    RS=0;
    EN=0;
    __delay_ms(50);
    EN=1;
}

void lcddata(unsigned char d2)
{
    PORTD=d2;
    RS=1;
    EN=0;
    __delay_ms(50);
    EN=1;
}

void lcdclear()
{
    lcdcmd(0);
    lcdcmd(1);
}
