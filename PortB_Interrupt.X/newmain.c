/*
 * File:   newmain.c
 * Author: Linh
 *
 * Created on April 5, 2021, 11:47 PM
 */


// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = RCIO6      // Oscillator Selection bits (External RC oscillator, port function on RA6)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ  20000000
#define TMR2PRESCALE    4
long u32TempFrequency;
int state;

Timer1_Configuration(void)
{   
    T1CON = 0x03;
    TMR1L = 0;                  //clear tmr1l
    TMR1H = 0;                  //clear tmr1h
}

void PWM1_Start(void)
{
    //......Mode PWM......//
    CCP1M3 = 1;
    CCP1M2 = 1;
    
    if (TMR2PRESCALE == 1)
    {
        T2CKPS0 = 0;
        T2CKPS1 = 0;
    }
    if (TMR2PRESCALE == 4)
    {
        T2CKPS0 = 1;
        T2CKPS1 = 0;
    }
    if (TMR2PRESCALE == 16)
    {
        T2CKPS0 = 1;
        T2CKPS1 = 1;
    }
    TMR2ON = 1;
    TRISC2 = 0;
}

//.........ham tinh PR2(so tick trong 1 chu ky PWM), gia tri vao u32Frequency la tan so mong muon cua PWM.......//
PWM1_Init(long u32Frequency)
{
    PR2 = (_XTAL_FREQ/(u32Frequency*4*TMR2PRESCALE)-1);     //dung cong thuc, 0<=PR2<=255, nen chu y gia tri u32Frequency dua vao
    u32TempFrequency = u32Frequency;                        //luu lai gia tri u32Frequency de dung cho viec tinh Duty cycle
}

PWM1_Duty(unsigned int duty)                //duty dua vao la gia tri PWM mong muon, thi PWM hoat dong voi x=duty*100/1000 (%) 
{
    if (duty<1024)
    {
        duty = ((float)duty/1023)*(_XTAL_FREQ/(u32TempFrequency*TMR2PRESCALE));     //dung cong thuc
        CCP1X = duty & 2;
        CCP1Y = duty & 1;
        CCPR1L = duty >> 2;
    }
}

void __interrupt() funtion()
{
    if (INTCONbits.RBIF == 1)
    {
        if (PORTBbits.RB4 == 0) 
        {
            RD4 = ~RD4;
            if (state == 0)
            {
                state = 1;
                PWM1_Duty(256);
            } else
            {
                state = 0;
                PWM1_Duty(0);
            }
        }
        if (PORTBbits.RB5 == 0) 
        {   
            RD5 = ~RD5;
            if (state == 1)
            {
                state = 2;
                PWM1_Duty(512);
            } else if (state == 2)
            {
                state = 3;
                PWM1_Duty(1023);
            }
        }
        if (PORTBbits.RB6 == 0) 
        {
            RD6 = ~RD6;
            if (state == 3)
            {
                state = 2;
                PWM1_Duty(512);
            } else if (state == 2)
            {
                state = 1;
                PWM1_Duty(256);
            }
        }
    }
    INTCONbits.RBIF = 0;
}

void PortB_INT_Configuration()
{
    TRISB = 0xff;
    PORTB = 0xff;
    INTCON = 0;
    INTCONbits.GIE = 1;
    //INTCONbits.PEIE = 1;
    INTCONbits.RBIE = 1; 
}

L298_Configuration()
{       
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;
    PORTCbits.RC3 = 0;                      //IN2 ouput = 0
    PORTCbits.RC4 = 1;                      //ENA output = 1
}

void main(void) {
    
    PortB_INT_Configuration();
    TRISD = 0;
    PORTD = 0;
    Timer1_Configuration(); 
    L298_Configuration();
    
    //.....Cau hinh L298.......//    
    PWM1_Init(5000);                        //Pwm period = 1/5000 (s)
    PWM1_Duty(0);                        //duty =1023, PWM 100%
    PWM1_Start();
    while(1)
    {
        
    }
    return;
}

