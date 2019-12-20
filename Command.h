#include "LPC407x_8x_177x_8x.h"

#include "MOTOR.h"
#include "Signal.h"
#include "HM10.h"


enum MODES {TEST, AUTO};
static uint32_t MODE = TEST;

void AUTONOMOUS (void);
void TESTING (void);

void FORWARD (void);
void BACK (void);
void STOP (void);
void RIGHT (uint32_t DEGREE);
void LEFT (uint32_t DEGREE);


void STATUS (void);
void FINISH (void);

