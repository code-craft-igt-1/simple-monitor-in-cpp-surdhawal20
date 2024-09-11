#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// Monitor constructor
Monitor::Monitor(const std::string& language, const std::string& tempUnit)
    : msgHandler(language), tempUnit(tempUnit) {}

// Unified function to check if a value is within limits (including warning level)
VitalAlertLevel Monitor::checkValue(float value, float lowerLimit, float upperLimit) {
    constexpr float WARNING_TOLERANCE = 0.985f;  // 1.5% below the upper limit
    if (value > upperLimit) {
        return VitalAlertLevel::CRITICAL;
    }
    if (value >= upperLimit * WARNING_TOLERANCE) {
        return VitalAlertLevel::WARNING;
    }
    if (value < lowerLimit) {
        return VitalAlertLevel::CRITICAL;
    }
    return VitalAlertLevel::OK;
}

// Function to check temperature specifically
VitalAlertLevel Monitor::checkTemperature(float temperature) {
    if (tempUnit == "C") {
        temperature = tempConverter.convertToFahrenheit(temperature);
    }
    constexpr float TEMPERATURE_LOWER_F = 95.0;
    constexpr float TEMPERATURE_UPPER_F = 102.0;
    return checkValue(temperature, TEMPERATURE_LOWER_F, TEMPERATURE_UPPER_F);
}

// Function to format temperature with the correct unit
std::string Monitor::formatTemperature(float temperature) {
    if (tempUnit == "C") {
        temperature = tempConverter.convertToCelsius(temperature);
        return to_string(temperature) + " \u00B0C";
    } else {
        return to_string(temperature) + " \u00B0F";
    }
}

// Function to display alert levels (with language translation)
void Monitor::displayAlertLevel(const std::string& message, VitalAlertLevel level) {
    if (level == VitalAlertLevel::CRITICAL) {
        cout << message << "\n";
        for (int i = 0; i < 6; ++i) {
            cout << "\r* " << flush;
            sleep_for(seconds(1));
            cout << "\r *" << flush;
            sleep_for(seconds(1));
        }
    } else if (level == VitalAlertLevel::WARNING) {
        cout << "Warning: " << message << "\n";
    }
}

// Function to check all vitals
int Monitor::vitalsOk(float temperature, float pulseRate, float spo2) {
    std::vector<std::tuple<float, float, float, std::string>> checks = {
        { temperature, 95.0f, 102.0f, "TEMPERATURE" },
        { pulseRate, 60.0f, 100.0f, "PULSE" },
        { spo2, 90.0f, 100.0f, "SPO2" }
    };

    for (const auto& [value, lowerLimit, upperLimit, paramName] : checks) {
        VitalAlertLevel level = (paramName == "TEMPERATURE") ? checkTemperature(value) :
                                checkValue(value, lowerLimit, upperLimit);

        if (level == VitalAlertLevel::CRITICAL) {
            // Display alert message using the correct language for critical levels
            displayAlertLevel(msgHandler.getMessage("CRITICAL_" + paramName) +
                (paramName == "TEMPERATURE" ? " " + formatTemperature(value) : ""), level);
            return 0;  // Critical value, return immediately
        } else if (level == VitalAlertLevel::WARNING) {
            // Display alert message using the correct language for warning levels
            displayAlertLevel(msgHandler.getMessage("WARNING_" + paramName) +
                (paramName == "TEMPERATURE" ? " " + formatTemperature(value) : ""), level);
        }
    }

    return 1;  // Return 1 if all vitals are OK or in the warning range
}
