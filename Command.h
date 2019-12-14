#include "LPC407x_8x_177x_8x.h"

#include "MOTOR.h"
#include "Signal.h"

enum MODES {TEST, AUTO};
static uint32_t MODE = TEST;

void AUTONOMOUS (void);
void TESTING (void);

void FORWARD (void);
void BACK (void);
void STOP (void);
void RIGHT (void);
void LEFT (void);

void STATUS (void);
void START (void);
void FINISH (void);

