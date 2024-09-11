#ifndef TEMPERATURE_CONVERTER_H_
#define TEMPERATURE_CONVERTER_H_

#include <string>
#include <sstream>

class TemperatureConverter {
 public:
    float convertToFahrenheit(float tempC);
    float convertToCelsius(float tempF);
};

#endif  // TEMPERATURE_CONVERTER_H_
