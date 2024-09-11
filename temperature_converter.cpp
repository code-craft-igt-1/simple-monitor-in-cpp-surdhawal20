#include "./temperature_converter.h"

// Function to convert Celsius to Fahrenheit
float TemperatureConverter::convertToFahrenheit(float tempC) {
    return (tempC * 9 / 5) + 32;
}

// Function to convert Fahrenheit to Celsius
float TemperatureConverter::convertToCelsius(float tempF) {
    return (tempF - 32) * 5 / 9;
}

