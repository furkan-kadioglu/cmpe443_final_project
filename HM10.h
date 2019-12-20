#ifndef HM10_H
#define HM10_H

#include "LPC407x_8x_177x_8x.h"
#include "Serial.h"

extern uint8_t HM10_Connected;

void Request(char* request);
void Response(void);
void HM10_Init(void);
uint8_t HM10_Check_Connection(void);


#endif
