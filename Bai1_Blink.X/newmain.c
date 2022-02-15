/*
 * File:   newmain.c
 * Author: Linh
 *
 * Created on March 28, 2021, 1:30 AM
 */


// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
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

#define     s0   0x3F
#define     s1   0x06
#define     s2   0x5B
#define     s3   0x4F
#define     s4   0x66
#define     s5   0x6D
#define     s6   0x7D
#define     s7   0x07
#define     s8   0x7F
#define     s9   0x6F

#define _XTAL_FREQ 8000000

#include <xc.h>

uint8_t ledcode[]={0x3F;0x06;0x5B;0x4F;0x66;0x6D;0x7D;0x07;0x7F;0x6F};

void showled4(int Nu)
{
    PORTA |= 1<<3;
    uint8_t HangNgan =Nu/1000;;
    uint8_t HangTram =(Nu - HangNgan*1000)\100;
    uint8_t HangChuc =(Nu - HangNgan*1000 - HangTram*100)\10;
    uint8_t HangDV = (Nu - HangNgan*1000 - HangTram*100 - HangChuc*10);
    PORTB = ledcode[HangDV];
}
void showled3(int Nu)
{
    PORTA = 0;
    PORTA |= 1<<2;
    uint8_t HangNgan =Nu/1000;;
    uint8_t HangTram =(Nu - HangNgan*1000)\100;
    uint8_t HangChuc =(Nu - HangNgan*1000 - HangTram*100)\10;
    uint8_t HangDV = (Nu - HangNgan*1000 - HangTram*100 - HangChuc*10);
    PORTB = ledcode[HangChuc];
}
void showled2(int Nu)
{
    PORTA = 0;
    PORTA |= 1<<1;
    uint8_t HangNgan =Nu/1000;;
    uint8_t HangTram =(Nu - HangNgan*1000)\100;
    uint8_t HangChuc =(Nu - HangNgan*1000 - HangTram*100)\10;
    uint8_t HangDV = (Nu - HangNgan*1000 - HangTram*100 - HangChuc*10);
    PORTB = ledcode[HangTram];
}
void showled4(int Nu)
{
    PORTA = 0;
    PORTA |= 1<<0;
    uint8_t HangNgan =Nu/1000;;
    uint8_t HangTram =(Nu - HangNgan*1000)\100;
    uint8_t HangChuc =(Nu - HangNgan*1000 - HangTram*100)\10;
    uint8_t HangDV = (Nu - HangNgan*1000 - HangTram*100 - HangChuc*10);
    PORTB = ledcode[HangDV];
}

void main(void) {
    TRISB = 0;
    TRISA = 0;
    PORTA = 0;
    PORTB = 0;
    
    while (1)
    {
        showled4(1234);
        __delay_ms(100);
        showled3(1234);
        __delay_ms(100);
        showled2(1234);
        __delay_ms(100);
        showled1(1234);
        __delay_ms(100);
    }
    return;
}
