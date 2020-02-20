/*
 * File:   EUSARTC.c
 * Author: CHARLIE
 *
 * Created on 19 de febrero de 2020, 22:45
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f887.h>
#define _XTAL_FREQ  4000000

void LOOP(void);
void ANALOGICO(void);
void TRANSMIT(void); 
void RECEIVE(void);
char y;
char x;
char z;
void main(void) {
    // oscilador interno
    
    OSCCONbits.IRCF = 0b110; //4Mhz
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1;
    
    
     //entradas, salidas, entradas digitales o analogicas
    ANSEL =  0b00100001;
    ANSELH = 0b00000000;
    
    TRISA = 0b00100001;
    TRISB = 0b00000000; 
    TRISC = 0b10011000;
    TRISD = 0b00000000;
    TRISE = 0b0001;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    // adc configuration bits
                 
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;

    //eusart
    
 SPBRG = 25;
    // EL QUE TX
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.TX9 = 0;
    //RX
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
     
    LOOP();
}

void LOOP(void){
    while(1){
      
        ANALOGICO();
        TRANSMIT();
        RECEIVE();
        PORTB = x;
 
}
}


void ANALOGICO(void){
    __delay_ms(1);
        ADCON0bits.CHS = 0000;
        ADCON0bits.ADON = 1;
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
            
            y = ADRESH;
           
               
    return;
}
void RECEIVE(void){
    while(!RCIF);
    x = RCREG;
    return;
}
    

void TRANSMIT(void){
     while(!TRMT);
  TXREG = y;
    return;
}
