#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"

char switch_down_1, switch_down_2, switch_down_3, state_buzzer;

static char 
switch_update_interrupt_sense()
{
  char p1val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();

  switch_down_1 = (p1val & SW1) ? 0 : 1;

  switch_down_2 = (p1val & SW2) ? 0 : 1;

  switch_down_3 = (p1val & SW3) ? 0 : 1;
  
  if(!(p1val & SW4)){
    state_advance();
  }
  change_buzzer();
  led_update();
}
