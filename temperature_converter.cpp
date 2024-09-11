#include "./temperature_converter.h"

// Function to convert Celsius to Fahrenheit
float TemperatureConverter::convertToFahrenheit(float tempC) {
    return (tempC * 9 / 5) + 32;
}

// Function to convert Fahrenheit to Celsius
float TemperatureConverter::convertToCelsius(float tempF) {
    return (tempF - 32) * 5 / 9;
}

// Helper function to convert numbers to string
template<typename T>
std::string TemperatureConverter::to_string_custom(T value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
