#include <stdint.h>

typedef struct ADC_Type
{
    volatile uint32_t CR;           // Control Register
    volatile uint32_t GDR;          // Global Data Register
             uint32_t reserved;
    volatile uint32_t INTEN;        // Interrupt Enable Register
    volatile uint32_t DR0;          // Data Registers
    volatile uint32_t DR1;
    volatile uint32_t DR2;
    volatile uint32_t DR3;
    volatile uint32_t DR4;
    volatile uint32_t DR5;
    volatile uint32_t DR6;
    volatile uint32_t DR7;
    volatile uint32_t STAT;         // Status Register
    volatile uint32_t TRM;          // Trim Register

};

#define ADC_Base_Address 0x40034000
#define ADC ((ADC_Type *) ADC_Base_Address)

void ADC_Init();