#ifndef DEVICE_H
#define DEVICE_H

#include "WiFiBackendManager.h"
#include "PulseSimulator.h"
#include "HeartRateLog.h"

class Device {
public:
    Device();
    void setup();
    void loop();

private:
    WiFiBackendManager wifiBackendManager;
    PulseSimulator pulseSimulator;
    HeartRateLog* heartRateLog;
    void sendDataToBackend(int heartRate);
    int calculateHeartRate(float voltage);
    void controlLed(int heartRate);
};

#endif // DEVICE_H