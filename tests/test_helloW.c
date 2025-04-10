/*

#include "unity.h"
#include "fff.h"
#include "helloW.h"
#include <stdio.h>

#define TEST_F(SUITE, NAME) void NAME()

// Enable FFF's global variables
DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(const char*, getGreeting);

void setUp(void) {
    RESET_FAKE(getGreeting); 
    FFF_RESET_HISTORY();
}

void tearDown(void) {
}

TEST_F(HelloTests, getGreeting_called_once) {
    getGreeting_fake.return_val = "Hello, everyOne!";
    hello();
    TEST_ASSERT_EQUAL(getGreeting_fake.call_count, 1);
}

TEST_F(HelloTests, hello_returns_correct_greeting) {
    const char* expectedGreeting = "Hello, everyOne!";
    getGreeting_fake.return_val = expectedGreeting;
    const char* result = hello();

    // Assert
    TEST_ASSERT_EQUAL_STRING(expectedGreeting, result); // Check if the result matches the expected greeting
    }

int main(){

    UNITY_BEGIN(); 
    setUp(); // Call setup before running tests
    printf("-------------\n");
    printf("Running Tests\n");
    printf("-------------\n\n");

    RUN_TEST(getGreeting_called_once);
    RUN_TEST(hello_returns_correct_greeting);
    
    printf("\n-------------\n");
    printf("Complete\n");
    printf("-------------\n\n");


    return UNITY_END();
}
*/