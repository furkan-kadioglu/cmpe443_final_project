#include "LPC407x_8x_177x_8x.h"

#include "MOTOR.h"
#include "Signal.h"
#include "HM10.h"
#include "ADC.h"


enum MODES {TEST, AUTO};
extern uint32_t MODE;
static inline char *stringFromMode(uint32_t mode)
{
    static char *strings[] = { "TEST", "AUTO"};
    return strings[mode];
}

enum MOVEMENT_DIRS {MOVING_FORWARD, MOVING_BACKWARD, TURNING_LEFT, TURNING_RIGHT, STOPPED};
extern uint32_t MOVEMENT_DIR;

extern uint32_t isStoppedForLight;

extern uint32_t ultrasonicSensorDistance;

void AUTONOMOUS (void);
void TESTING (void);

void FORWARD (void);
void BACK (void);
void STOP (void);
void RIGHT (uint32_t DEGREE);
void LEFT (uint32_t DEGREE);


void STATUS (void);
void FINISH (void);

