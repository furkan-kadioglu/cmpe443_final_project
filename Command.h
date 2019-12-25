#include "LPC407x_8x_177x_8x.h"

#include "MOTOR.h"
#include "Signal.h"
#include "HM10.h"
#include "ADC.h"

#define NUMBER_OF_CYCLE_PER_DEGREE 6


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


extern uint32_t DEGREE_OF_TURN;
extern uint32_t NUMBER_OF_TURN;
extern uint32_t REMAINING_DEGREE_OF_TURN;

uint32_t CALC_REMAINING_DEGREE_OF_TURN(void);

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

