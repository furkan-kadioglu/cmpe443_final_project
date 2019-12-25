#include "ADC.h"

uint32_t LDR1_Last = 0;
uint32_t LDR2_Last = 0;
uint32_t Potentiometer_Last = 0;
uint8_t ADC_Available = 0;

uint32_t LDR1_Last_Light_Level = 0;
uint32_t LDR2_Last_Light_Level = 0;

void ADC_Init() {
	
	// IOCON
	LDR1_IOCON &= ~(0xE << 1 | 1 << 7);
	LDR2_IOCON &= ~(0xE << 1 | 1 << 7);
	Potentiometer_IOCON &= ~(0xF << 1 | 1 << 7);
	
	LDR1_IOCON |= 3;
	LDR2_IOCON |= 3;
	Potentiometer_IOCON |= 1;
	
	//Turn on ADC.
	PCONP |= (1<<12);
	
	//Set the CLKDIV and make the A/D converter operational without Burst mode.
	ADC->CR &= ~(0xFF << 8);
	ADC->CR |= (ADC_CLKDIV << 8);

	//Make the A/D converter operational
	ADC->CR |= (1 << 21);
	
	//Make sure conversions are software controlled and require 31 clocks (Do not use Burst mode)
	ADC->CR &= ~(1 << 16);

	//Configure CR SEL bits for sampled and converting corresponding pin.
	ADC->CR &= ~(0xFF);
	ADC->CR |= (4 | 16 | 32);
	
	//Enable interrupt for corresponding pin.
	ADC->INTEN |= (1 << 8);
	
	//Enable ADC_IRQn (Interrupt Request).
	NVIC_EnableIRQ(ADC_IRQn);
	NVIC_ClearPendingIRQ(ADC_IRQn);
}

void ADC_Start () {
	//Write a code for starting A/D conversion on a rising edge on the TIMER 1 MATCH 1.
	ADC->CR &= ~(0xF << 24);
	ADC->CR |= (7 << 24);

}


void ADC_IRQHandler() {
	ADC->GDR &= ~((uint32_t)1 << 31);
	
	//Write the converted data (only the converted data) to ADC_Last variable.
	Potentiometer_Last = (ADC->DR[2] & (0xFFF0)) / 16;
	LDR1_Last = (ADC->DR[4] & (0xFFF0)) / 16; 
	LDR2_Last = (ADC->DR[5] & (0xFFF0)) / 16;
	ADC_Available = 1;
	 

}

uint32_t Calc_LDR_Light_Level(uint32_t LDR_Last){
	return 1024 - (LDR_Last * 1024 / 0xFFF);
}
