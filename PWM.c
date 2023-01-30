
#include "lib/include.h"

/* Tomando el Módulo0PWM0 Generador 0 -> PB6
   Tomando el Módulo0PWM3 Generador 1 -> PB5
   Tomando el Módulo0PWM5 Generador 2 -> PE5*/

extern void Configura_Reg_PWM1(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1<<0); // Enable reloj de modulo PWM1 pag 354 Habilitamos PWM0 correspondiente al experimento 1
    SYSCTL->RCGCGPIO |= (1<<1) | (1<<4); //Habilitamos el GPIOB según lo requerido en el experimento 1 pág 340 y 1233 y también encendemos GPIOD 
    SYSCTL->RCC &= ~(1<<20);  // Deshabilitamo el divisor según lo requerido en el experimento 1 

    GPIOB->AFSEL |= (1<<5); // Habilita función alternativa 672 IMMPORTANTE RECORDAR QUE ESTE ESTA CONTROLADO POR EL PW3
    GPIOB->AFSEL |= (1<<6); //Recordar que este está controlado689 por el PWM1
    GPIOE->AFSEL|= (1<<5); //Recordar que este está controlado por el PWM5

    GPIOB->DIR = (1<<5); // Configura i/o Pag 663 IMMPORTANTE RECORDAR QUE ESTE ESTA CONTROLADO POR EL PW3
    GPIOB->DIR = (1<<6); //Recordar que este está controlado por el PWM1
    GPIOE->DIR = (1<<5); //Recordar que este está controlado por el PWM5

    GPIOB->PCTL |= (GPIOB->PCTL&0xF00FFFFF) | 0x04400000; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689*/
    // GPIOB->PCTL |= (GPIOB->PCTL&0x0FFFFFFF) | 0x40000000; Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOE->PCTL |= (GPIOE->PCTL&0xFF0FFFFF) | 0x00400000; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689*/

    GPIOB->DEN |= (1<<6)|(1<<5); // para decirle si es digital o no Pag 682 IMMPORTANTE RECORDAR QUE ESTE ESTA CONTROLADO POR EL PW3
    // GPIOB->DEN |= (1<<7); Recordar que este está controlado por el PWM1
    GPIOE->DEN |= (1<<5); //Recordar que este está controlado por el PWM5

    PWM0->_0_CTL = (0<<0); // PWM0 gen 0
    PWM0->_1_CTL = (0<<0); // PWM0 gen 1
    PWM0->_2_CTL = (0<<0); // PWM0 gen 2

    PWM0->_0_GENA = 0X0000008C; //Configuración en pág 1239
    PWM0->_1_GENA = 0x0000008C; // Establecemos el modo de trabajo de cuenta regresiva pág 1285 y 1239
    PWM0->_2_GENA = 0X0000008C;

    PWM0->_0_LOAD = 2000;
    PWM0->_1_LOAD = 2000; // Cuentas = (Frecuencia de reloj/Frecuencia PWM) Cuentas = (20000000/10000) = 2000
    PWM0->_2_LOAD = 2000;

    PWM0->_0_CMPB = 1600;
    PWM0->_1_CMPA = 1600; // Estoy utilizando el 80% del ciclo de trabajo (2000 - 100% ) x = ?
    PWM0->_2_CMPA = 1600;

    PWM0->_0_CTL = (1<<0);
    PWM0->_1_CTL = (1<<0);// Se activa el generador 1 del PWM0
    PWM0->_2_CTL = (1<<0);


    PWM0->ENABLE = (1<<5)|(1<<3)|(1<<0); //Encedemos el PWW1 para trabajar con generador 0
   // PWM0->ENABLE = (1<<3); Encedemos el PWM2 para trabajar con generador 1 según la tabla de la pág 1233 
    // PWM0->ENABLE = (1<<5); Encedemos el PW4 para trbajar con el generador 2
}
