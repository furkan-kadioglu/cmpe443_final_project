#include <stdint.h>

typedef struct PLL_Type
{
    volatile uint32_t PLLCON;      
    volatile uint32_t PLLCFG;
    volatile uint32_t PLLSTAT;
    volatile uint32_t PLLFEED;
};

#define PLL_Base_Adress 0x400FC080
#define PLL_0 ((PLL_Type *) PLL_Base_Adress)
#define PLL_1 ((PLL_Type *) (PLL_Base_Adress + 0x20))

void PLL_Init();