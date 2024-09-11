#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <vector>
#include <tuple>
#include "message_handler.h"
#include "temperature_converter.h"

// Enum for Vital alert levels
enum class VitalAlertLevel {
    OK,
    WARNING,
    CRITICAL
};

class Monitor {
private:
    std::string tempUnit;
    MessageHandler msgHandler;
    TemperatureConverter tempConverter;

    // Unified function to check if a value is within limits
    VitalAlertLevel checkValue(float value, float lowerLimit, float upperLimit);

    // Function to check temperature specifically
    VitalAlertLevel checkTemperature(float temperature);

    // Function to display the temperature with the appropriate unit
    std::string formatTemperature(float temperature);

    // Function to display alert levels
    void displayAlertLevel(const std::string& message, VitalAlertLevel level);

public:
    Monitor(const std::string& language, const std::string& tempUnit);
    int vitalsOk(float temperature, float pulseRate, float spo2);

    // Wrapper function to expose checkTemperature for testing
    VitalAlertLevel testCheckTemperature(float temperature) {
        return checkTemperature(temperature);
    }

    // Wrapper function to expose checkValue for testing
    VitalAlertLevel testCheckValue(float value, float lowerLimit, float upperLimit) {
        return checkValue(value, lowerLimit, upperLimit);
    }
};

#endif
