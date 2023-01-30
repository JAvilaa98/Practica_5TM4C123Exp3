#include "lib/include.h"
volatile uint16_t coloracion;
volatile uint8_t duty_rojo;
volatile uint8_t duty_verde;
volatile uint8_t duty_azul;
int main(void)
{
//Experimento 3
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz , utilizando el uart de la practica 3
 * se enviara dato desde interfaz de simulink para controlar la intensidad luminosa 
 * usando un led RGB externa 
 *
 */
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART0(); //20MHZ Baudrate 9600
    Configura_Reg_PWM1(8);
    
   //ASCII colores
   duty_rojo = 114;
   duty_verde = 118;
   duty_azul = 97;

    while (1)
    {
        coloracion = readChar();
        switch (coloracion)
        {
             case 'r':
                while (duty_rojo == 114)
                {
                    duty_rojo = (int)readChar();
                }
                PWM0->_0_CMPB = 2000-((int)(duty_rojo*1000)/50);
                duty_rojo = 114;
                break;
        
            case 'a':
                while (duty_azul == 97)
                {
                    duty_azul = (int)readChar();
                }
                PWM0->_1_CMPA = 2000-((int)(duty_azul*1000)/50);
                duty_azul = 97;
                break;

            case 'v':
                while (duty_verde == 118)
                {
                    duty_verde = (int)readChar();
                }
                PWM0->_2_CMPA = 2000-((int)(duty_verde*1000)/50);
                duty_verde = 118;
                break;

            default:
            break;
        }
    }
    
}

