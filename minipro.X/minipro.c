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
#define HEATER PORTCbits.RC2
#define KEEPWARM PORTCbits.RC3
#define WATERPUMP PORTCbits.RC4
#define ON 1
#define OFF 0

void DelaySeconds();
unsigned short Temp_Ref=80; //reference temperature
unsigned int myADC;
unsigned char z;
float ActualTemp;


void main()
{
    TRISB=0X07;
    TRISC=0X0F;
    OSCCON=0X75;
    TRISA=0X01;
    ANSEL=0X01;   
    TRISE=0X00;
    ADCON0=0b11000001;
    ADCON1=0b10000000;
    
    HEATER = OFF;
    KEEPWARM = OFF;
    WATERPUMP= OFF;
    
    PORTBbits.RB0=1;
    PORTBbits.RB1=1;
    PORTBbits.RB2=1;
    
    while(1)
    {
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE); 
        {
            myADC=(ADRESH<<8)+ADRESL;
            ActualTemp = ((float)myADC*5)/10.24;
            
        }
        
        if (ActualTemp < Temp_Ref)
            {
                    HEATER = ON, 
                    KEEPWARM = OFF;
            }

        if (ActualTemp >= Temp_Ref)
        {
                HEATER = OFF,
                KEEPWARM = ON;
        }
        
        if (PORTBbits.RB0==0)
        {
                HEATER = ON, 
                KEEPWARM = OFF;
        }
        
        if (PORTBbits.RB1==0 || PORTBbits.RB2==0)
        {
            WATERPUMP = ON;
        }
        
        DelaySeconds(5);
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

