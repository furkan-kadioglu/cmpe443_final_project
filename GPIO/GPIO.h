#include <stdint.h>

typedef struct GPIO_Type
{
    volatile uint32_t DIR;      
             uint32_t reserved[3];
    volatile uint32_t MASK;
    volatile uint32_t PIN;
    volatile uint32_t SET;
    volatile uint32_t CLR;
};

#define GPIO_Base_Address 0x20098000
#define GPIO_0 ((GPIO_Type *) GPIO_Base_Address)
#define GPIO_1 ((GPIO_Type *) (GPIO_Base_Address + 0x20))
#define GPIO_2 ((GPIO_Type *) (GPIO_Base_Address + 0x40))
#define GPIO_3 ((GPIO_Type *) (GPIO_Base_Address + 0x60))
#define GPIO_4 ((GPIO_Type *) (GPIO_Base_Address + 0x80))
#define GPIO_5 ((GPIO_Type *) (GPIO_Base_Address + 0xA0))

void GPIO_Init();