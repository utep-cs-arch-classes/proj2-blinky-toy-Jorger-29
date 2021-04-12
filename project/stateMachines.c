#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"

char state_song = 0;

void toggle_red()		/* always toggle! */
{
  static char interrupts = 0;
  
  switch (state_red) {
  case 0:
    red_on = 1;
    break;
  case 1:
    if(interrupts < 70){
      interrupts++;
    }else{
      red_on ^= 1;
      interrupts = 0;
    }
    break;
  }
  led_update();			/* always changes an led */
}

void toggle_green()	/* only toggle green if red is on!  */
{
  static char interrupts = 0;
  
  switch (state_green) {
  case 0:
    green_on = 0;
    break;
  case 1:
    if(interrupts < 3){
      green_on = 0;
      interrupts++;
    }else{
      green_on = 1;
      interrupts = 0;
    }
    break;
  case 2:   
    green_on ^= 1;
    break;
  case 3:
    green_on = 0;;
    break;
  case 4:   
    if(interrupts < 3){
      green_on = 1;
      interrupts++;
    }else{
      green_on = 0;
      interrupts = 0;
    }
    break;
  case 5:
    green_on = 1;
    break;
  }
  led_update();
}

void do_blink()
{
  if(state_green == 3){
    green_on = 0;
    toggle_red();
  }else{
    red_on = 0;
    toggle_green();
  }  
}

void state_advance()
{
  static enum {B=0, F=1} moving_green = F;

  switch (state_green) {
  case 0:
    moving_green = F;
    state_green = 1;
    break;
  case 1:
    state_green = moving_green ? 2 : 0;
    break;
  case 2:
    state_green = moving_green ? 3 : 1;
    break;
  case 3:
    state_green = moving_green ? 4 : 2;
    state_red ^= 1;
    break;
  case 4:
    state_green = moving_green ? 5 : 3;
    break;
  case 5:
    moving_green = B;
    state_green = 4;
    break;
  }
}

void change_buzzer() { 
  if(switch_down_3){
    buzzer_set_period(1000);
  }else if(switch_down_2){
    switch(state_song){
    case 0:
      buzzer_set_period(630);
      break;
    case 1:
      buzzer_set_period(750);
      break;
    case 2:
      buzzer_set_period(630);
      break;
    case 3:
      buzzer_set_period(750);
      break;
    case 4:
      buzzer_set_period(630);
      break;
    case 5:
      buzzer_set_period(950);
      break;
    case 6:
      buzzer_set_period(840);
      break;
    case 7:
      buzzer_set_period(750);
      break;
    case 8:
      buzzer_set_period(1260);
      break;
    }   
  }else{
    buzzer_set_period(0);
  }
}
