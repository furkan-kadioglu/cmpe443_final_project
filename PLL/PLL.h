#include <stdint.h>
#include "../Library.h"

typedef struct 
{
    volatile uint32_t PLLCON;      
    volatile uint32_t PLLCFG;
    volatile uint32_t PLLSTAT;
    volatile uint32_t PLLFEED;

}PLL_Type;

#define PLL_Base_Address 0x400FC080
#define PLL_0 ((PLL_Type *) PLL_Base_Address)
#define PLL_1 ((PLL_Type *) (PLL_Base_Address + 0x20))

#define EMCCLKSEL ((uint32_t *) 0x400FC100)
#define CCLKSEL ((uint32_t *) 0x400FC104)
#define USBCLKSEL ((uint32_t *) 0x400FC108)
#define CLKSRCSEL ((uint32_t *) 0x400FC10C)
#define PCLKSEL ((uint32_t *) 0x400FC1A8)
#define SPIFICLKSEL ((uint32_t *) 0x400FC1B4)

void PLL_Init();
void PLL_Feed();
