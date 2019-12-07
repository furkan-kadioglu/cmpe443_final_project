#include "ADC/ADC.c"
#include "EXT/EXT.c"
#include "GPIO/GPIO.c"
#include "IOCON.h"
#include "PWM/PWM.c"
#include "PLL/PLL.c"
#include "TIMER/TIMER.c"

#include "Library.h"


void init(){
    // __enable_irq();
}

void update(){
    
}


int main (){
    init();
    while(1){

        // __WFI();
        update();
    }
}