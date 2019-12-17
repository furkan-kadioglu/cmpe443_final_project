#ifndef ADC_H
#define ADC_H

#include "LPC407x_8x_177x_8x.h"

#include "SystemStructures.h"

typedef struct {
  volatile	uint32_t CR;
  volatile	uint32_t GDR;
						uint32_t RESERVED0;
  volatile	uint32_t INTEN;
  volatile	uint32_t DR[8];
  volatile	uint32_t STAT;
  volatile	uint32_t TRM;
} ADC_TypeDef;

#define ADC_CLOCK_FREQUENCY 1000000

//Write the IOCON address of Analog Pin
#define	LDR1_IOCON_ADDRESS	0x4002C0F8
#define	LDR2_IOCON_ADDRESS	0x4002C0FC
#define	Potentiometer_IOCON_ADDRESS	0x4002C064
#define LDR1_IOCON	*((volatile uint32_t*)(LDR1_IOCON_ADDRESS))
#define LDR2_IOCON	*((volatile uint32_t*)(LDR2_IOCON_ADDRESS))
#define Potentiometer_IOCON	*((volatile uint32_t*)(Potentiometer_IOCON_ADDRESS))

//Write the max value of ADC.
#define ADC_MAX_VALUE 0xFFF

//Define a ADC_CLKDIV variable for given ADC_CLOCK_FREQUENCY.
#define ADC_CLKDIV 59

#define ADC_BASE	0x40034000
#define ADC	((ADC_TypeDef*) ADC_BASE)

extern uint32_t LDR1_Last;
extern uint32_t LDR2_Last;
extern uint32_t Potentiometer_Last;

void ADC_Init(void);
void ADC_Start(void);
void ADC_Stop(void);

#endif
