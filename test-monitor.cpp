#include "./monitor.h"
#include "gtest/gtest.h"

// Test cases for temperature, pulse rate, and oxygen saturation separately

TEST(Monitor, TemperatureCritical) {
    // Test cases where temperature is out of range
    ASSERT_FALSE(vitalsOk(103, 75, 95));  // High temperature
    ASSERT_FALSE(vitalsOk(94, 75, 95));   // Low temperature

    // Test cases where temperature is in range
    ASSERT_TRUE(vitalsOk(98.6, 75, 95));  // Normal temperature
    ASSERT_TRUE(vitalsOk(101.9, 75, 95)); // High normal temperature
}

TEST(Monitor, PulseRateOutOfRange) {
    // Test cases where pulse rate is out of range
    ASSERT_FALSE(vitalsOk(98.6, 101, 95)); // High pulse rate
    ASSERT_FALSE(vitalsOk(98.6, 59, 95));  // Low pulse rate

    // Test cases where pulse rate is in range
    ASSERT_TRUE(vitalsOk(98.6, 60, 95));   // Low normal pulse rate
    ASSERT_TRUE(vitalsOk(98.6, 100, 95));  // High normal pulse rate
}

TEST(Monitor, OxygenSaturationOutOfRange) {
    // Test cases where oxygen saturation is out of range
    ASSERT_FALSE(vitalsOk(98.6, 75, 89));  // Low oxygen saturation

    // Test cases where oxygen saturation is in range
    ASSERT_TRUE(vitalsOk(98.6, 75, 90));   // Low normal oxygen saturation
    ASSERT_TRUE(vitalsOk(98.6, 75, 100));  // High normal oxygen saturation
}

// Test cases for multiple vitals being off range
TEST(Monitor, MultipleVitalsOffRange) {
    // Test cases where more than one vital sign is out of range
    ASSERT_FALSE(vitalsOk(103, 101, 89));  // All vitals out of range
    ASSERT_FALSE(vitalsOk(95, 50, 80));    // All vitals out of range

    // Test cases where all vital signs are normal 
    ASSERT_TRUE(vitalsOk(98.6, 75, 95));   // All vitals within range
}

// General test cases
TEST(Monitor, EdgeCases) {
    // Test cases right on the boundary
    ASSERT_TRUE(vitalsOk(95, 60, 90));     // Lower boundary for all vitals
    ASSERT_TRUE(vitalsOk(102, 100, 90));   // Upper boundary for temperature and pulse rate
    ASSERT_FALSE(vitalsOk(95, 59, 90));    // Pulse rate just below the lower boundary
}