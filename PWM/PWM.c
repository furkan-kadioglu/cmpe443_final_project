#include "PWM.h"

//default PWM_0
#define PWM PWM_0

void PWM_Init()
{
    // ** PCONP **
    // ** IOCON **
    
    // ** RESET ** 
    // PWM->TCR |= 2;
    // Timer or Counter Mode PWM->CTCR


    // ** PERIOD & DUTY CYCLE SETTINGS **
    // Adjust PWM->PR
    // PWM->MCR
    // MR registers' values
    // PWM->LER

    // ** OUTPUT SETTINGS **
    // PWM->PCR (single or double edge)&(enable PWM's channels)


    // ** INTERRUPT SETTINGS **
    // PWM-> IR = 0xFFFF;
    // NVIC_EnableIRQ(IRQn_Type IRQn)
    // NVIC_ClearPendingIRQ(IRQn_Type IRQn)
    // NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)	


    // ** LET'S BEGIN ** 
    // Remove reset and enable PWM and Counter
    // PWM->TCR = 9; 

}