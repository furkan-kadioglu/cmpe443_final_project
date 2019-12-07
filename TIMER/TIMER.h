#include <stdint.h>

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
             uint32_t reserved;

    volatile uint32_t EMR;      // External Match Register  
             uint32_t reserved[12];
    volatile uint32_t CTCR;     // Count Control Register
    
}TIMER_Type;

#define TIMER_Base_Address 0x0x40004000
#define TIMER_0 ((TIMER_Type *) TIMER_Base_Address)
#define TIMER_1 ((TIMER_Type *) (TIMER_Base_Address + 0x4000))
#define TIMER_2 ((TIMER_Type *) (TIMER_Base_Address + 0x90000))
#define TIMER_3 ((TIMER_Type *) (TIMER_Base_Address + 0x94000))

void TIMER_Init();
