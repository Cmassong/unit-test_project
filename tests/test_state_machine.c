#include "../src/state_machine.h"
#include "unity.h"
#include "fff.h"

#define TEST_F(SUITE, NAME) void NAME()


DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC(setLedState, LED_Type, LED_State);
FAKE_VOID_FUNC(setLedBlinkRate, LED_Type, int );



void setUp(void) {
    RESET_FAKE(setLedState);
    RESET_FAKE(setLedBlinkRate);
    // Optional: Setup code before each test
}

void tearDown(void) {
    // Optional: Cleanup after each test
}

TEST_F(FsmTest, initial_state_is_idle){
    StateMachine sm;
    initStateMachine(&sm);
    TEST_ASSERT_EQUAL(STATE_IDLE, sm.currentState);
}

TEST_F(FsmTest, transition_from_idle_to_running_on_start_event){
    StateMachine sm;
    initStateMachine(&sm);
    handleStateMachine(&sm, EVENT_START);
    TEST_ASSERT_EQUAL(STATE_RUNNING, sm.currentState);
}

TEST_F(FsmTest, transition_from_running_to_idle_on_stop_event){
    StateMachine sm;
    initStateMachine(&sm);
    handleStateMachine(&sm, EVENT_START); // Transition to RUNNING first
    handleStateMachine(&sm, EVENT_STOP);  // Then to IDLE
    TEST_ASSERT_EQUAL(STATE_IDLE, sm.currentState);
}

TEST_F(FsmTest, no_transition_on_invalid_event_in_idle_state){
    StateMachine sm;
    initStateMachine(&sm);
    handleStateMachine(&sm, EVENT_ERROR); // Invalid event in IDLE state
    TEST_ASSERT_EQUAL(STATE_IDLE, sm.currentState); // Should remain in IDLE
}

TEST_F(FsmTest, leds_are_updated_immediately_on_state_change) {
    StateMachine sm;
    initStateMachine(&sm);

    RESET_FAKE(setLedState);
    RESET_FAKE(setLedBlinkRate);
    
    handleStateMachine(&sm, EVENT_START); // Transition IDLE → RUNNING

    TEST_ASSERT_EQUAL(1, setLedState_fake.call_count);
    TEST_ASSERT_EQUAL(LED_V, setLedState_fake.arg0_val); 
    TEST_ASSERT_EQUAL(LED_ON, setLedState_fake.arg1_val); 
    TEST_ASSERT_EQUAL(0, setLedBlinkRate_fake.call_count); 
}

int main(void) {
    UNITY_BEGIN();
    printf("-------------\n");
    printf("Running Tests\n");
    printf("-------------\n\n");

    RUN_TEST(initial_state_is_idle);
    RUN_TEST(transition_from_idle_to_running_on_start_event);
    RUN_TEST(transition_from_running_to_idle_on_stop_event);
    RUN_TEST(no_transition_on_invalid_event_in_idle_state);
    RUN_TEST(leds_are_updated_immediately_on_state_change);

    printf("\n-------------\n");
    printf("Complete\n");
    printf("-------------\n\n");

    return UNITY_END();
}
