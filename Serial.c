#include "Serial.h"
char serialBuffer[10];
uint8_t serialNewDataAvailable = 0;
uint32_t serialReceiverCurrentIndex = 0;

char* serialTransmitData;
uint8_t serialTransmitCompleted = 0;

void Serial_Init() {
	//Change the function of TX and RX pins for UART.
	Serial_UART_TX_PIN &= ~3;
	Serial_UART_TX_PIN |= 4;
	Serial_UART_RX_PIN |= 4; 
	Serial_UART_RX_PIN &= ~3;
	p2 &= ~7;
	p3 &= ~7;
	p2 |= 1;
	p3 |= 1;
	
	//Turn on UART0.
	PCONP |= 8;
	
	//Enable FIFO for UART0.
	Serial_UART->FCR |= 1;
	
	//In order to change the DLM, DLL and FDR values, Write correct code for enabling the access to Divisor Latches.
	Serial_UART->LCR |= 128;
	
	//Write correct DLM, DLL and FDR values for 115200 baudrate
	Serial_UART->DLL = 0xD9;
	Serial_UART->DLM = 0x0;
	Serial_UART->FDR = (0x4 | 0x5 << 4);
	//DL=0xD9, DIV=4, MUL=5, BR=9600
	//DL=13, DIV=5, MUL=7, BR=115200
	
	//Write correct code for disabling the access to Divisor Latches.
	Serial_UART->LCR &=  ~128;
	
	//Change LCR register value for 8-bit character transfer, 1 stop bits and No Parity.
	Serial_UART->LCR &= ~0xF;
	Serial_UART->LCR |= 0x3;
							
	//Enable the Receive Data Available and THRE Interrupt.
	Serial_UART->IER |= 3;
	
	//Enable UART0_IRQn Interrupt.
	NVIC_EnableIRQ(UART0_IRQn);
	
	//Set UART0_IRQn Priority to 5.
	NVIC_SetPriority(UART0_IRQn, 5);
}

void UART0_IRQHandler() {	
	uint32_t currentInterrupt = (Serial_UART->IIR & 0xE)/2; 
	
	// Receive Data Available interrupt.
	if(currentInterrupt == 0x2) {
		serialBuffer[serialReceiverCurrentIndex++] = Serial_UART->RBR;
		serialBuffer[serialReceiverCurrentIndex] = 0;
		serialNewDataAvailable = 1;
	}
	
	// THRE interrupt
	else if(currentInterrupt == 0x1) {
		if(*serialTransmitData > 0) {
			Serial_WriteData(*serialTransmitData++);
		}
		else {
			Clear_serialBuffer();
			serialTransmitCompleted = 1;
		}
	}
}

void Clear_serialBuffer(){
	serialReceiverCurrentIndex = 0;
	strcpy(serialBuffer,"");
}

void Serial_WriteData(const char data) {
	serialTransmitCompleted = 0;
	Serial_UART->THR = data;
}

