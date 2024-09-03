#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

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
    if (isTemperatureCritical(temperature)) {
        displayCriticalAlert("Temperature is critical!");
        return 0;
    }
    if (isPulseRateOutOfRange(pulseRate)) {
        displayCriticalAlert("Pulse Rate is out of range!");
        return 0;
    }
    if (isSpo2OutOfRange(spo2)) {
        displayCriticalAlert("Oxygen Saturation out of range!");
        return 0;
    }
    return 1;
}
