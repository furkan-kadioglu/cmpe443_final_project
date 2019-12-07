#include <stdint.h>

typedef struct EXT_Type
{
    volatile uint32_t EXTINT;       
             uint32_t reserved;
    volatile uint32_t EXTMODE;
    volatile uint32_t EXTPOLAR;           
};

#define EXT_Base_Address 0x0x400FC140
#define EXT ((EXT_Type *) EXT_Base_Address)

void EXT_Init();