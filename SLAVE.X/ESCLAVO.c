/*
 * File:   ESCLAVO.c
 * Author: CHARLIE
 *
 * Created on February 16, 2020, 1:31 PM
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
void ANALOGICO(void);
void ANALOGICO2(void);
void LOOP(void);
void RECEIVE(void);
void MESSAGE(void);
void MESSAGE2(void);
char x;
char z;
char y;
char DATA;
char BANDERA;

void __interrupt() ISR(void){
       
    if(PIR1bits.SSPIF==1 & BANDERA == 0   ){
        x= SSPBUF;
        
        PORTB = x;
          SSPSTATbits.BF= 0;
          PIR1bits.SSPIF = 0;
           MESSAGE();
           
         
           return;
    }
    if(PIR1bits.SSPIF==1 & BANDERA == 1 ){
        x= SSPBUF;
        
        PORTB = x;
          SSPSTATbits.BF= 0;
          PIR1bits.SSPIF = 0;
           
           MESSAGE2();
         
           return;
    }
   
    return;
   
    
}


void main(void) {
   // oscilador interno
    
    OSCCONbits.IRCF = 0b110; //4Mhz
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1;
    
    
     //entradas, salidas, entradas digitales o analogicas
    ANSEL =  0b00000011;
    ANSELH = 0b00000000;
    
    TRISA = 0b00100011;
    TRISB = 0b00000000; 
    TRISC = 0b00011000;
    TRISD = 0b00000000;
    TRISE = 0b0000;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    // adc configuration bits
                 
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;

    ADCON0bits.ADON = 1;   // adc on
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    
    //spi config
    SSPSTATbits.SMP = 0;
    SSPSTATbits.CKE = 0;
    SSPCONbits.SSPEN = 1;
    SSPCONbits.CKP = 1;
    SSPCONbits.SSPM = 0b0100;
   
    //interrupts
    PIE1bits.SSPIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    x=0;
    y = 0;
    z=0;
    LOOP();
}
void LOOP(void){
    while(1){
      
         
    ANALOGICO();
    
    ANALOGICO2();
 
}
}




void MESSAGE(void){
   
    while(BF==1);
    
    SSPBUF = y;
    BANDERA = 1;
   
        return;
}
void MESSAGE2(void){
   
    while(BF==1);
   
    SSPBUF = z;
    BANDERA = 0;
    
    
        return;
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
void ANALOGICO2(void){
    __delay_ms(1);
        ADCON0bits.CHS = 0001;
        ADCON0bits.ADON = 1;
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
            
            z = ADRESH;
           
               
    return;
}