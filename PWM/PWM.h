#include <stdint.h>
#include "../Library.h"

typedef struct 
{
    volatile uint32_t IR;       // Interrupt Register  
    volatile uint32_t TCR;      // Timer Control Register
    volatile uint32_t TC;       // Timer Counter
    volatile uint32_t PR;       // Prescale Register
    volatile uint32_t PC;       // Prescale Counter
    volatile uint32_t MCR;      // Match Control Register
    
    volatile uint32_t MR0;
    volatile uint32_t MR1;
    volatile uint32_t MR2;
    volatile uint32_t MR3;

    volatile uint32_t CCR;      // Capture Control Register
    volatile uint32_t CR0;
    volatile uint32_t CR1;
             uint32_t reserved[3];

    volatile uint32_t MR4;      
    volatile uint32_t MR5;
    volatile uint32_t MR6;

    volatile uint32_t PCR;      // PWM Control Register
    volatile uint32_t LER;      // Load Enable Register
             uint32_t reserved[7];
    volatile uint32_t CTCR;     // Count Control Register
    
}PWM_Type;

#define PWM_Base_Address 0x40014000
#define PWM_0 ((PWM_Type *) PWM_Base_Address)
#define PWM_1 ((PWM_Type *) (PWM_Base_Address + 0x4000))

void PWM_Init();
