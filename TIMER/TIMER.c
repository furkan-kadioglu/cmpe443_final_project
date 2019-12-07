#include "TIMER.h"

void TIMER_Init()
{
    // ** PCONP **
    // ** IOCON **
    
    // ** RESET ** 
    // PWM->TCR |= 2;
    // Timer or Counter Mode PWM->CTCR


    // ** PERIOD SETTINGS **
    // Adjust PWM->PR
    // PWM->MCR
    // MR registers' values

    // ** CAPTURE SETTINGS **
    // PWM->CCR

    // ** OUTPUT SETTINGS **
    // PWM->EMR


    // ** INTERRUPT SETTINGS **
    // PWM-> IR = 0xFFFF;
    // NVIC_EnableIRQ(IRQn_Type IRQn)
    // NVIC_ClearPendingIRQ(IRQn_Type IRQn)
    // NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)	


    // ** LET'S BEGIN ** 
    // Remove reset and enable PWM and Counter
    // PWM->TCR = 9; 
}
