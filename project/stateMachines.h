#ifndef stateMachine_included
#define stateMachine_included

void change_buzzer();
void state_advance();
void do_blink();
void toggle_green();
void toggle_red();

extern char state_buzzer, state_song;

#endif // included
