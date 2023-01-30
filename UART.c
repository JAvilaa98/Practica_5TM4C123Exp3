#include "lib/include.h"

extern void Configurar_UART0(void) //UART1
{
    SYSCTL->RCGCUART  = (1<<0);   //Habilitamos UART pág 344
    SYSCTL->RCGCGPIO |= (1<<0);     //Habilitamos el puerto del GPIO pág 340
    GPIOA->AFSEL = (1<<0) | (1<<1); //Habilitamos la función alternativa de los puertos pag 671
   // GPIOA->DIR |= (1<<0) | (0<<1); Habilitamos la dirección
    //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
    GPIOA->PCTL = (GPIOA->PCTL&0xFFFFFF00) | 0x00000011;// 
    GPIOA->DEN = (1<<0) | (1<<1);// Habilitamos canales digitales
    //UART0 UART Control (UARTCTL) pag.918 DISABLE!!
    UART0->CTL = (0<<9) | (0<<8) | (0<<0);


    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 20,000,000 / (16*9600) = 130.2083
    UARTFBRD[DIVFRAC] = integer(.2083 * 64 + 0.5) = 13.8312
    */
    UART0->IBRD = 130;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART0->FBRD = 14;
    //  UART Line Control (UARTLCRH) pag.916
    UART0->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART0->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART0->CTL = (1<<0) | (1<<8) | (1<<9);

}

extern char readChar(void)
{
    int v;
    char c;
    while ((UART0->FR & (1<<4)) != 0);
    v = UART0 -> DR & 0XFF;
    c = v;
    return c;
    
}

