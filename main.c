#include "lib/include.h"
/*volatile float valor,valor1;
volatile uint16_t Result[2];
volatile uint16_t duty;
volatile uint16_t duty2;
volatile uint16_t duty3;*/

volatile uint8_t dc_rojo; //volatil para poderla monitorear 
volatile uint8_t dc_azul;
volatile uint8_t dc_verde;
uint8_t algo;
volatile uint16_t color;
volatile uint8_t R;
volatile uint8_t G;
volatile uint8_t B;


uint16_t count;
int main(void)
{
    
//Experimento 3
/* Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz, utilizando el uart de la practica 3
 * se enviara dato desde interfaz de simulink para controlar la intensidad luminosa 
 * usando un led RGB externa  
 */
    Configurar_PLL(_20MHZ);  //configuracion de velocidad de reloj
    Configurar_UART0();
    Configura_Reg_PWM1(8);

    dc_rojo = 114;
    dc_verde = 103;
    dc_azul = 98;

    while (1)
    {
        color = readChar();
        
        switch (color)
        {
            case 'r':
                while (dc_rojo == 114)
                {
                    dc_rojo = (int)readChar(); //recibe el % del uart para calcular el dc%
                }
               // R = ((int)(dc_rojo*100)/255); 
                PWM0->_0_CMPB = 20000-((int)(dc_rojo*10000)/50); //PB7 (R)
                dc_rojo = 114;
            break;

            case 'g':
                while (dc_verde == 103)
                {
                    dc_verde = (int)readChar();
                }
                // G = ((int)(dc_verde*100)/255);
                PWM0->_2_CMPA = 20000-((int)(dc_verde*10000)/50); //PE4 (G)
                dc_verde = 103;
            break;

            case 'b':
                while (dc_azul == 98)
                {
                    dc_azul = (int)readChar();
                }
                // B = ((int)(dc_azul*100)/255);
                PWM0->_1_CMPA = 20000-((int)(dc_azul*10000)/50); //PB4 (B)
                dc_azul = 98;
            break;

            default:
                algo=1;
            break;
        }   
    }
}

