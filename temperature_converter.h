#ifndef TEMPERATURE_CONVERTER_H_
#define TEMPERATURE_CONVERTER_H_

#include <string>
#include <sstream>

class TemperatureConverter {
 public:
    float convertToFahrenheit(float tempC);
    float convertToCelsius(float tempF);
    template<typename T>
    std::string to_string_custom(T value);
};

#endif //TEMPERATURE_CONVERTER_H_
