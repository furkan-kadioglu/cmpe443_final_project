#include "HM10.h"

uint8_t HM10_Connected = 0;

// Baud Rate, Parity, Word length configurations

void Request(char* request){
	serialTransmitData = request;
	Serial_WriteData(*serialTransmitData++);
}

void Response(){
	serialTransmitData = serialBuffer;
	Serial_WriteData(*serialTransmitData++);
}

void HM10_Init(){
}

