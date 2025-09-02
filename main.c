#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
/**
 * main.c
 */

#define RED 0x2
#define BLUE 0x4
#define GREEN 0x8
#define PURPLE 0x6

#define SW1 0x10
#define SW2 0x01
int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x1F;            // SET PORTF PINS 4 PIN
    GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
    GPIO_PORTF_PUR_R  = 0x11;            // PORTF4 IS PULLED UP

    GPIO_PORTF_DATA_R = 0x0;             // LED OFF
    while(1)
    {
        int curr = GPIO_PORTF_DATA_R;
        int red = curr & SW1;
        int blue = curr & SW2;

        if(!red && !blue){
            GPIO_PORTF_DATA_R = PURPLE;
        }
        else if (!blue){
            GPIO_PORTF_DATA_R = BLUE;
        }
        else if (!red){
            GPIO_PORTF_DATA_R = RED;
        }
        else{
            GPIO_PORTF_DATA_R = 0x0;
        }
    }
}
