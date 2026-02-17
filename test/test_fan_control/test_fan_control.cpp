#include <unity.h>
#include "fan_control.h"

void setUp(void) {}
void tearDown(void) {}

// --- dutyToCompare tests ---

void test_dutyToCompare_0_percent(void) {
    TEST_ASSERT_EQUAL_UINT16(0, dutyToCompare(0));
}

void test_dutyToCompare_50_percent(void) {
    // 50 * 320 / 100 = 160
    TEST_ASSERT_EQUAL_UINT16(160, dutyToCompare(50));
}

void test_dutyToCompare_100_percent(void) {
    // 100 * 320 / 100 = 320
    TEST_ASSERT_EQUAL_UINT16(320, dutyToCompare(100));
}

void test_dutyToCompare_10_percent(void) {
    // 10 * 320 / 100 = 32
    TEST_ASSERT_EQUAL_UINT16(32, dutyToCompare(10));
}

// --- nextDuty tests ---

void test_nextDuty_from_50(void) {
    TEST_ASSERT_EQUAL_UINT8(60, nextDuty(50));
}

void test_nextDuty_from_90(void) {
    TEST_ASSERT_EQUAL_UINT8(100, nextDuty(90));
}

void test_nextDuty_wraps_from_100(void) {
    // FR-0002: 100 → 10
    TEST_ASSERT_EQUAL_UINT8(10, nextDuty(100));
}

void test_nextDuty_from_10(void) {
    TEST_ASSERT_EQUAL_UINT8(20, nextDuty(10));
}

void test_nextDuty_full_cycle(void) {
    // Walk through an entire cycle starting from initial 50%
    uint8_t duty = DUTY_INITIAL;  // 50
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(60, duty);
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(70, duty);
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(80, duty);
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(90, duty);
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(100, duty);
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(10, duty);   // wrap
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(20, duty);
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(30, duty);
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(40, duty);
    duty = nextDuty(duty);  TEST_ASSERT_EQUAL_UINT8(50, duty);   // back to start
}

// --- debounceAccept tests ---

void test_debounce_accept_after_500ms(void) {
    TEST_ASSERT_TRUE(debounceAccept(500, 0));
}

void test_debounce_accept_well_after(void) {
    TEST_ASSERT_TRUE(debounceAccept(1000, 0));
}

void test_debounce_reject_within_window(void) {
    // NFR-0002: reject presses within 500 ms
    TEST_ASSERT_FALSE(debounceAccept(499, 0));
}

void test_debounce_reject_same_time(void) {
    TEST_ASSERT_FALSE(debounceAccept(0, 0));
}

void test_debounce_accept_exactly_at_boundary(void) {
    // 600 - 100 = 500, should accept
    TEST_ASSERT_TRUE(debounceAccept(600, 100));
}

void test_debounce_reject_just_under_boundary(void) {
    // 599 - 100 = 499, should reject
    TEST_ASSERT_FALSE(debounceAccept(599, 100));
}

// --- initial value tests ---

void test_initial_duty_is_50(void) {
    // FR-0001
    TEST_ASSERT_EQUAL_UINT8(50, DUTY_INITIAL);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_dutyToCompare_0_percent);
    RUN_TEST(test_dutyToCompare_50_percent);
    RUN_TEST(test_dutyToCompare_100_percent);
    RUN_TEST(test_dutyToCompare_10_percent);

    RUN_TEST(test_nextDuty_from_50);
    RUN_TEST(test_nextDuty_from_90);
    RUN_TEST(test_nextDuty_wraps_from_100);
    RUN_TEST(test_nextDuty_from_10);
    RUN_TEST(test_nextDuty_full_cycle);

    RUN_TEST(test_debounce_accept_after_500ms);
    RUN_TEST(test_debounce_accept_well_after);
    RUN_TEST(test_debounce_reject_within_window);
    RUN_TEST(test_debounce_reject_same_time);
    RUN_TEST(test_debounce_accept_exactly_at_boundary);
    RUN_TEST(test_debounce_reject_just_under_boundary);

    RUN_TEST(test_initial_duty_is_50);

    return UNITY_END();
}
