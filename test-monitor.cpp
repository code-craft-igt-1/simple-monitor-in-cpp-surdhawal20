#include "monitor.h"  // Include your header file
#include <gtest/gtest.h>  // Include the Google Test framework

// Test Fixture for the Monitor class
class MonitorTest : public ::testing::Test {
 protected:
    Monitor *monitor;  // Pointer to the Monitor object

    // Set up method that runs before each test
    void SetUp() override {
        monitor = new Monitor("EN", "F");  // Initialize monitor in English and Fahrenheit
    }

    // Tear down method that runs after each test
    void TearDown() override {
        delete monitor;  // Clean up the allocated monitor object
    }
};

// Test temperature conversion from Celsius to Fahrenheit
TEST_F(MonitorTest, ConvertToFahrenheit) {
    TemperatureConverter tempConverter;
    float tempC = 37.0;  // Normal human body temperature in Celsius
    float expectedF = 98.6;
    ASSERT_NEAR(tempConverter.convertToFahrenheit(tempC), expectedF, 0.1);
}

// Test temperature conversion from Fahrenheit to Celsius
TEST_F(MonitorTest, ConvertToCelsius) {
    TemperatureConverter tempConverter;
    float tempF = 98.6;  // Normal human body temperature in Fahrenheit
    float expectedC = 37.0;
    ASSERT_NEAR(tempConverter.convertToCelsius(tempF), expectedC, 0.1);
}

// Test critical temperature detection
TEST_F(MonitorTest, CriticalTemperature) {
    float criticalTempF = 103.0;  // Above the upper limit of 102.0 F
    VitalAlertLevel level = monitor->testCheckTemperature(criticalTempF);
    ASSERT_EQ(level, VitalAlertLevel::CRITICAL);  // Ensure it's flagged as critical
}

// Test warning temperature detection
TEST_F(MonitorTest, WarningTemperature) {
    float warningTempF = 101.5;  // Close to the upper limit, within warning range
    VitalAlertLevel level = monitor->testCheckTemperature(warningTempF);
    ASSERT_EQ(level, VitalAlertLevel::WARNING);  // Ensure it's flagged as warning
}

// Test normal temperature detection
TEST_F(MonitorTest, NormalTemperature) {
    float normalTempF = 98.6;  // Normal body temperature
    VitalAlertLevel level = monitor->testCheckTemperature(normalTempF);
    ASSERT_EQ(level, VitalAlertLevel::OK);  // Ensure it's flagged as OK
}

// Test critical pulse rate detection
TEST_F(MonitorTest, CriticalPulseRate) {
    float criticalPulse = 120.0;  // Above the upper limit of 100
    VitalAlertLevel level = monitor->testCheckValue(criticalPulse, 60.0, 100.0);
    ASSERT_EQ(level, VitalAlertLevel::CRITICAL);  // Should return CRITICAL
}

// Test normal pulse rate detection
TEST_F(MonitorTest, NormalPulseRate) {
    float normalPulse = 75.0;  // Normal pulse rate
    VitalAlertLevel level = monitor->testCheckValue(normalPulse, 60.0, 100.0);
    ASSERT_EQ(level, VitalAlertLevel::OK);  // Should return OK
}

// Test warning SpO2 detection
TEST_F(MonitorTest, WarningSpO2) {
    float warningSpO2 = 91.0;  // Close to the lower limit
    VitalAlertLevel level = monitor->testCheckValue(warningSpO2, 90.0, 100.0);
    ASSERT_EQ(level, VitalAlertLevel::WARNING);  // Should return WARNING
}

// Test critical SpO2 detection
TEST_F(MonitorTest, CriticalSpO2) {
    float criticalSpO2 = 85.0;  // Below the lower limit of 90
    VitalAlertLevel level = monitor->testCheckValue(criticalSpO2, 90.0, 100.0);
    ASSERT_EQ(level, VitalAlertLevel::CRITICAL);  // Should return CRITICAL
}

// Test vitals check for all normal vitals
TEST_F(MonitorTest, AllVitalsNormal) {
    int result = monitor->vitalsOk(98.6, 75.0, 95.0);  // All vitals within normal range
    ASSERT_EQ(result, 1);  // Should return 1 (all vitals OK)
}

// Test vitals check for critical vitals
TEST_F(MonitorTest, CriticalVitals) {
    int result = monitor->vitalsOk(103.0, 120.0, 85.0);  // All vitals are critical
    ASSERT_EQ(result, 0);  // Should return 0 (critical vital detected)
}
