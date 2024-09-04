#include "./monitor.h"
#include "gtest/gtest.h"

// Separate test cases for temperature being out of range
TEST(Monitor, TemperatureTooHigh) {
    ASSERT_FALSE(vitalsOk(103, 75, 95));  // High temperature
}

TEST(Monitor, TemperatureTooLow) {
    ASSERT_FALSE(vitalsOk(94, 75, 95));   // Low temperature
}

TEST(Monitor, TemperatureNormal) {
    ASSERT_TRUE(vitalsOk(98.6, 75, 95));  // Normal temperature
}

TEST(Monitor, TemperatureHighNormal) {
    ASSERT_TRUE(vitalsOk(101.9, 75, 95)); // High normal temperature
}

// Separate test cases for pulse rate being out of range
TEST(Monitor, PulseRateTooHigh) {
    ASSERT_FALSE(vitalsOk(98.6, 101, 95));  // High pulse rate
}

TEST(Monitor, PulseRateTooLow) {
    ASSERT_FALSE(vitalsOk(98.6, 59, 95));   // Low pulse rate
}

TEST(Monitor, PulseRateNormalLow) {
    ASSERT_TRUE(vitalsOk(98.6, 60, 95));    // Low normal pulse rate
}

TEST(Monitor, PulseRateNormalHigh) {
    ASSERT_TRUE(vitalsOk(98.6, 100, 95));   // High normal pulse rate
}

// Separate test cases for oxygen saturation being out of range
TEST(Monitor, OxygenSaturationTooLow) {
    ASSERT_FALSE(vitalsOk(98.6, 75, 89));   // Low oxygen saturation
}

TEST(Monitor, OxygenSaturationNormalLow) {
    ASSERT_TRUE(vitalsOk(98.6, 75, 90));    // Low normal oxygen saturation
}

TEST(Monitor, OxygenSaturationNormalHigh) {
    ASSERT_TRUE(vitalsOk(98.6, 75, 100));   // High normal oxygen saturation
}

// Test cases for multiple vitals being out of range
TEST(Monitor, MultipleVitalsOutOfRange) {
    ASSERT_FALSE(vitalsOk(103, 101, 89));   // All vitals out of range
}

TEST(Monitor, MultipleVitalsOutOfRange2) {
    ASSERT_FALSE(vitalsOk(95, 50, 80));     // All vitals out of range
}

TEST(Monitor, AllVitalsNormal) {
    ASSERT_TRUE(vitalsOk(98.6, 75, 95));    // All vitals within range
}

// Test cases for boundary conditions
TEST(Monitor, LowerBoundaryConditions) {
    ASSERT_TRUE(vitalsOk(95, 60, 90));      // Lower boundary for all vitals
}

TEST(Monitor, UpperBoundaryConditions) {
    ASSERT_TRUE(vitalsOk(102, 100, 90));    // Upper boundary for temperature and pulse rate
}

TEST(Monitor, PulseRateJustBelowLowerBoundary) {
    ASSERT_FALSE(vitalsOk(95, 59, 90));     // Pulse rate just below the lower boundary
}
