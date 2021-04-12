#include <msp430.h>
#include "led.h"
#include "switches.h"

unsigned char red_on = 0, green_on = 0;
unsigned char state_red = 0, state_green = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};


void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  led_update();
}

void led_update()
{
  
  if (switch_down_1) {
    char ledFlags = 0;

    ledFlags |= switch_down_1 ? LED_GREEN : 0;
    ledFlags |= switch_down_1 ? LED_RED : 0;
    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;		  
  }else{
    char ledFlags = redVal[red_on] | greenVal[green_on];
    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;		  
  }
}
