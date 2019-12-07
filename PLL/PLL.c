#include "PLL.h"

// default PLL_0
#define PLL PLL_0

void PLL_Init()
{
    // Be sure PLL is not used

    // CLKSRCSEL to select external or internal clock

    // PLLCFG (MSEL & PSEL)

    // PLLCON
    //PLL->PLLCON = 1;
    
    //Feed the PLL to pass from PLLCON & PLLCFG to PLLSTAT
    //PLL_Feed();

    //Setup clock dividers

    // Wait for PLL is locked (10th bit of PLLSTAT)

    // Connect the PLL
}

void PLL_Feed()
{
    __disable_irq();
    PLL->PLLFEED = 0xAA;
    PLL->PLLFEED = 0x55;
    __enable_irq();
}