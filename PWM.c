
#include "lib/include.h"

/* Tomando el Módulo 0 del PWM1 Generador 0 -> PB7
   Tomando el Módulo0  del PWM2 Generador 1 -> PB4
   Tomando el Módulo0P del PWM4 Generador 2 -> PE4*/

extern void Configura_Reg_PWM1(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1<<0); // Enable reloj de modulo PWM1 pag 354 Habilitamos PWM0 correspondiente al experimento 3
    SYSCTL->RCGCGPIO |= (1<<1) | (1<<4); //Habilitamos el GPIOB Y GPIO E según lo requerido para el experimento 3
    SYSCTL->RCC &= ~(1<<20);  // Deshabilitamo el divisor según lo requerido en el experimento 3 

    GPIOB->AFSEL |= (1<<4); // Habilita función alternativa 672 IMMPORTANTE RECORDAR QUE ESTE ESTA CONTROLADO POR EL PWM2
    GPIOB->AFSEL |= (1<<7); //Recordar que este está controlado por el PWM1
    GPIOE->AFSEL|= (1<<4); //Recordar que este está controlado por el PWM4

    GPIOB->DIR = (1<<4); // Configura i/o Pag 663 IMMPORTANTE RECORDAR QUE ESTE ESTA CONTROLADO POR EL PW2
    GPIOB->DIR = (1<<7); //Recordar que este está controlado por el PWM1
    GPIOE->DIR = (1<<4); //Recordar que este está controlado por el PWM4

    GPIOB->PCTL |= (GPIOB->PCTL&0x0FF0FFFF) | 0x40040000; //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOE->PCTL |= (GPIOE->PCTL&0xFFF0FFFF) | 0x00040000; //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689

    GPIOB->DEN |= (1<<7)|(1<<4); //Para decirle si es digital o no Pag 682
    GPIOE->DEN |= (1<<4); //Para decir si es digital o no Pag 682

    PWM0->_0_CTL = (0<<0); // PWM0 gen 0
    PWM0->_1_CTL = (0<<0); // PWM0 gen 1
    PWM0->_2_CTL = (0<<0); // PWM0 gen 2

    PWM0->_0_GENB = 0X0000080C; //Configuración en pág 1239
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


    PWM0->ENABLE = (1<<4)|(1<<2)|(1<<1); //Encedemos el PWW1, PWM2 Y PWM4 para trabajar con generador 0
}
