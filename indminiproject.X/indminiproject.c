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
#include "lcd.h"
#define _XTAL_FREQ 8000000
#define IN1 PORTAbits.RA4
#define IN2 PORTAbits.RA5
void motor1();
int i;

void main()
{
    ADCON1=0X0F;
    TRISA=0X0F;
    TRISC=0X00;
    ANSEL =0x03; //RA3 as analog pin
    OSCCON=0X75;
    
    
    PORTAbits.RA0=1;
    PORTAbits.RA1=1;
    PORTAbits.RA2=1;
    PORTAbits.RA3=1;
    PORTCbits.RC0=0;
    
    //unsigned int count=0;
   // unsigned char sevenSeg[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
    
    while(1)
    {
        if(PORTAbits.RA0==0)
        {
           motor1(); 
        }
        if(PORTAbits.RA1==0)
        {
            motor1();
        }
        if(PORTAbits.RA2==0)
        {
            (PORTCbits.RC0==0);
        }
    }
}

void motor1()
{
    IN1=1;
    IN2=0;
}
