#include <stdint.h>

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

void PLL_Init();
