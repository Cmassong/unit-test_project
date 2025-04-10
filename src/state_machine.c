#include <stdio.h>
#include "state_machine.h"

void initStateMachine(StateMachine *sm) {
    sm->currentState = STATE_IDLE;
    setLedBlinkRate(LED_V, 1);
    setLedState(LED_V, LED_BLINK);
    setLedState(LED_O, LED_ON);
}

void handleStateMachine(StateMachine *sm, Event event) {
    switch (sm->currentState) {
        case STATE_IDLE:
            if (event == EVENT_START) {
                printf("Transitioning from IDLE to RUNNING.\n");
                sm->currentState = STATE_RUNNING;
                setLedState(LED_V, LED_ON);
            }
            break;
        case STATE_RUNNING:
            if (event == EVENT_STOP) {
                printf("Transitioning from RUNNING to IDLE.\n");
                sm->currentState = STATE_IDLE;
                setLedBlinkRate(LED_V, 1);
                setLedState(LED_V, LED_BLINK);
                setLedState(LED_O, LED_ON);
            } else if (event == EVENT_ERROR) {
                printf("Transitioning from RUNNING to ERROR.\n");
                sm->currentState = STATE_ERROR;
                setLedState(LED_R, LED_ON);
            }
            break;
        case STATE_ERROR:
            if (event == EVENT_START) {
                printf("Transitioning from ERROR to RUNNING.\n");
                sm->currentState = STATE_RUNNING;
                setLedState(LED_V, LED_ON);
            }
            break;
        default:
            break;
    }
}
