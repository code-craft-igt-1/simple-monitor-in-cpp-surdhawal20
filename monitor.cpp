#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// Monitor constructor
Monitor::Monitor(const std::string& language, const std::string& tempUnit)
    : msgHandler(language), tempUnit(tempUnit) {}

// Helper function to check upper limit
VitalAlertLevel checkUpperLimit(float value, float upperLimit, float tolerance) {
    if (value > upperLimit) {
        return VitalAlertLevel::CRITICAL;
    }
    if (value >= upperLimit - tolerance) {
        return VitalAlertLevel::WARNING;
    }
    return VitalAlertLevel::OK;
}

// Helper function to check lower limit
VitalAlertLevel checkLowerLimit(float value, float lowerLimit, float tolerance) {
    if (value < lowerLimit) {
        return VitalAlertLevel::CRITICAL;
    }
    if (value <= lowerLimit + tolerance) {
        return VitalAlertLevel::WARNING;
    }
    return VitalAlertLevel::OK;
}

// Unified function to check if a value is within limits (including warning level)
VitalAlertLevel Monitor::checkValue(float value, float lowerLimit, float upperLimit) {
    float tolerance = 0.015f * upperLimit;  // Tolerance as 1.5% of the upper limit

    // Check both lower and upper limits
    VitalAlertLevel lowerCheck = checkLowerLimit(value, lowerLimit, tolerance);
    if (lowerCheck != VitalAlertLevel::OK) return lowerCheck;

    return checkUpperLimit(value, upperLimit, tolerance);
}

// Function to check temperature specifically
VitalAlertLevel Monitor::checkTemperature(float temperature) {
    if (tempUnit == "C") {
        temperature = tempConverter.convertToFahrenheit(temperature);
    }
    return checkValue(temperature, 95.0f, 102.0f);
}

// Helper function to convert numbers to string
template<typename T>
std::string Monitor::to_string_custom(T value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Function to format temperature with the correct unit
std::string Monitor::formatTemperature(float temperature) {
    if (tempUnit == "C") {
        temperature = tempConverter.convertToCelsius(temperature);
        return to_string_custom(temperature) + " \u00B0C";
    } else {
        return to_string_custom(temperature) + " \u00B0F";
    }
}

// Helper function to handle critical alert animation
void Monitor::displayCriticalAlertAnimation() {
    for (int i = 0; i < 6; ++i) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

void Monitor::displayAlertLevel(const std::string& message, VitalAlertLevel level) {
    if (level == VitalAlertLevel::CRITICAL) {
        cout << message << "\n";
        displayCriticalAlertAnimation();
    } else if (level == VitalAlertLevel::WARNING) {
        cout << "Warning: " << message << "\n";
    }
}

// Handle individual vital checks and return the appropriate level
VitalAlertLevel Monitor::checkVital(float value, float lowerLimit, float upperLimit, 
const std::string& paramName) {
    // For temperature, use the checkTemperature function
    if (paramName == "TEMPERATURE") {
        return checkTemperature(value);
    }
    // For pulse rate and SpO2, use the generic checkValue function
    return checkValue(value, lowerLimit, upperLimit);
}

// Function to process alerts based on the level
bool Monitor::processAlert(const std::string& paramName, float value, VitalAlertLevel level) {
    // Mapping of VitalAlertLevel to alert type (critical or warning)
    static const std::map<VitalAlertLevel, std::string> alertTypeMap = {
        {VitalAlertLevel::CRITICAL, "CRITICAL_"},
        {VitalAlertLevel::WARNING, "WARNING_"}
    };

    // If level is OK, no alert needed, return early
    if (level == VitalAlertLevel::OK) {
        return true;
    }

    // Get the alert type based on level (it will be either CRITICAL_ or WARNING_)
    std::string alertType = alertTypeMap.at(level);

    // Build the alert message
    std::string alertMessage = msgHandler.getMessage(alertType + paramName) +
        (paramName == "TEMPERATURE" ? " " + formatTemperature(value) : "");

    // Display the alert
    displayAlertLevel(alertMessage, level);

    // Return true for WARNING, false for CRITICAL
    return level != VitalAlertLevel::CRITICAL;
}


// Main function
int Monitor::vitalsOk(float temperature, float pulseRate, float spo2) {
    // Define the vital checks
    std::vector<std::tuple<float, float, float, std::string>> checks = {
        { temperature, 95.0f, 102.0f, "TEMPERATURE" },
        { pulseRate, 60.0f, 100.0f, "PULSE" },
        { spo2, 90.0f, 100.0f, "SPO2" }
    };

    // Loop through each vital sign, check its value, and process the alert
    for (const auto& [value, lowerLimit, upperLimit, paramName] : checks) {
        VitalAlertLevel level = checkVital(value, lowerLimit, upperLimit, paramName);
        if (!processAlert(paramName, value, level)) {
            return 0; //  Return 0 if a critical alert is detected
        }
    }

    return 1; //  Return 1 if all vitals are OK or only in the warning range
}
