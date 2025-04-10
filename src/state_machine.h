#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR
} State;

typedef enum {
    EVENT_START,
    EVENT_STOP,
    EVENT_ERROR
} Event;

typedef enum {
    LED_V,
    LED_O,
    LED_R
} LED_Type;

typedef enum {
    LED_OFF,
    LED_ON,
    LED_BLINK
} LED_State;


typedef struct {
    State currentState;
} StateMachine;

void initStateMachine(StateMachine *sm);
void handleStateMachine(StateMachine *sm, Event event);
void setLedState(LED_Type led, LED_State state);
void setLedBlinkRate(LED_Type led, int rate_hz);


#endif
