#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include <vector>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;
using std::function;
using std::string;
using std::vector;

void displayCriticalAlert(const std::string& message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

bool isTemperatureCritical(float temperature) {
    return temperature > 102 || temperature < 95;
}

bool isPulseRateOutOfRange(float pulseRate) {
    return pulseRate < 60 || pulseRate > 100;
}

bool isSpo2OutOfRange(float spo2) {
    return spo2 < 90;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    // Define a vector of functions that perform the vital checks
    vector<std::tuple<function<bool()>, string>> checks = {
        { [temperature]() { return isTemperatureCritical(temperature); },
        "Temperature is critical!" },
        { [pulseRate]() { return isPulseRateOutOfRange(pulseRate); },
        "Pulse Rate is out of range!" },
        { [spo2]() { return isSpo2OutOfRange(spo2); },
        "Oxygen Saturation out of range!" }
    };

    // Iterate through each check and display an alert if the check fails
    for (auto& [check, message] : checks) {
        if (check()) {
            displayCriticalAlert(message);
            return 0;
        }
    }

    return 1;
}
