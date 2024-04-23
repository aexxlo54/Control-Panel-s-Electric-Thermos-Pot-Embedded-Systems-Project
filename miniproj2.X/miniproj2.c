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
//#include <stdio.h> //header file for sprintf

#define _XTAL_FREQ 8000000
#define ON 1
#define OFF 0

void main()
{
    TRISA=0X07;
    TRISB=0X3F;
    TRISC=0XF8;
    
    OSCCON=0X75;
    ANSELH=0X00;
    
    PORTBbits.RB0=1;
    PORTBbits.RB1=1;
    PORTBbits.RB2=1;
    
    PORTBbits.RB3=1;
    PORTBbits.RB4=1;
    PORTBbits.RB5=1;
    
    PORTEbits.RE3=1;
    
    PORTCbits.RC0=OFF;
    PORTCbits.RC1=OFF;
    PORTCbits.RC2=OFF;
    
    while(1)
    {
        //Temp button
        if (PORTBbits.RB0==0)
        {
            PORTCbits.RC0=ON;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=OFF;
        }
        if (PORTBbits.RB1==0)
        {
            PORTCbits.RC0=ON;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=OFF;
        }
        if (PORTBbits.RB2==0)
        {
            PORTCbits.RC0=OFF;
            PORTCbits.RC1=ON;
            PORTCbits.RC2=OFF;
        }
        
        //Main button
        if(PORTBbits.RB3==0)
        {
            PORTCbits.RC0=OFF;
            PORTCbits.RC1=ON;
            PORTCbits.RC2=OFF;
        }
        if(PORTBbits.RB4==0)
        {
            PORTCbits.RC0=ON;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=ON;
        }
        if (PORTBbits.RB5==0)
        {
            PORTCbits.RC0=ON;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=ON;
        }
        if (PORTEbits.RE3==0)
        {
            PORTCbits.RC0=OFF;
            PORTCbits.RC1=OFF;
            PORTCbits.RC2=OFF;
        }
    }
}