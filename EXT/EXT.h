#include <stdint.h>

typedef struct 
{
    volatile uint32_t EXTINT;       
             uint32_t reserved;
    volatile uint32_t EXTMODE;
    volatile uint32_t EXTPOLAR;

}EXT_Type;

#define EXT_Base_Address 0x0x400FC140
#define EXT ((EXT_Type *) EXT_Base_Address)

void EXT_Init();
