#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
/**
 * main.c
 */
int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x1E;            // SET PORTF PINS 4 PIN
    GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
    GPIO_PORTF_PUR_R  = 0x10;            // PORTF4 IS PULLED UP

    GPIO_PORTF_DATA_R = 0x0;             // LED OFF
    int colours[] = {0x0, 0x2, 0x6, 0x4, 0xC, 0x8, 0xA, 0xE};
    int state = 0;
    int prev = GPIO_PORTF_DATA_R & 0x10;
    int curr = GPIO_PORTF_DATA_R & 0x10;
    while(1)
    {
        curr = GPIO_PORTF_DATA_R & 0x10;

        if (prev && !curr){
            state++;
            state = state % 8;
            prev = 0;
            GPIO_PORTF_DATA_R = colours[state];
        }
        if (!prev && curr){
            prev = 16;
        }




    }
}
