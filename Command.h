#include "LPC407x_8x_177x_8x.h"

#include "MOTOR.h"
#include "HM10.h"
#include "ADC.h"
#include "Ultrasonic.h"
#include "MotorSpeedSensor.h"

enum MODES {TEST, AUTO};
extern uint32_t MODE;
static inline char *stringFromMode(uint32_t mode)
{
    static char *strings[] = { "TEST", "AUTO"};
    return strings[mode];
}

enum LAST_ACTIONS {STOP_ACTION, FORWARD_ACTION, BACK_ACTION, LEFT_ACTION, RIGHT_ACTION};
extern uint32_t ACTION;

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
