#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static int state_count = 0;
  static int song_count = 0;
  static char blink_count = 0;

  if (++state_count == 400){
    state_advance();
    state_count = 0;
  }
  
  if (++blink_count == 1) {
    do_blink();    
    blink_count = 0;
  }

  if (++song_count == 100){
    state_song++;
    song_count = 0;
    if(state_song == 9){
      state_song = 0;
    }
  }
}
