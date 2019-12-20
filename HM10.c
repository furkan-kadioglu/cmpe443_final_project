#include "HM10.h"

uint8_t HM10_Connected = 0;

// Baud Rate, Parity, Word length configurations
void HM10_Init(){
	serialTransmitData = "AT\r\n";
	Serial_WriteData(*serialTransmitData++);
	serialTransmitData = "AT+NAMEbill\r\n";
	Serial_WriteData(*serialTransmitData++);
	serialTransmitData = "AT+RESET\r\n";
	Serial_WriteData(*serialTransmitData++);
}

