#include <stdint.h>

typedef struct 
{
    volatile uint32_t P0;
    volatile uint32_t P1;
    volatile uint32_t P2;
    volatile uint32_t P3;
    volatile uint32_t P4;
    volatile uint32_t P5;
    volatile uint32_t P6;
    volatile uint32_t P7;
    volatile uint32_t P8;
    volatile uint32_t P9;
    volatile uint32_t P10;
    volatile uint32_t P11;
    volatile uint32_t P12;
    volatile uint32_t P13;
    volatile uint32_t P14;
    volatile uint32_t P15;
    volatile uint32_t P16;
    volatile uint32_t P17;
    volatile uint32_t P18;
    volatile uint32_t P19;
    volatile uint32_t P20;
    volatile uint32_t P21;
    volatile uint32_t P22;
    volatile uint32_t P23;
    volatile uint32_t P24;
    volatile uint32_t P25;
    volatile uint32_t P26;
    volatile uint32_t P27;
    volatile uint32_t P28;
    volatile uint32_t P29;
    volatile uint32_t P30;
    volatile uint32_t P31;

}IOCON_Type;

#define IOCON_Base_Address 0x4002C000
#define IOCON_0 ((IOCON_Type *) IOCON_Base_Address)
#define IOCON_1 ((IOCON_Type *) (IOCON_Base_Address + 0x80))
#define IOCON_2 ((IOCON_Type *) (IOCON_Base_Address + 0x100))
#define IOCON_3 ((IOCON_Type *) (IOCON_Base_Address + 0x180))
#define IOCON_4 ((IOCON_Type *) (IOCON_Base_Address + 0x200))
#define IOCON_5 ((IOCON_Type *) (IOCON_Base_Address + 0x280))
