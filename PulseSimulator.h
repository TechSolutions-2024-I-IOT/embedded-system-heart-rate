#ifndef PULSE_SIMULATOR_H
#define PULSE_SIMULATOR_H

#include <Arduino.h>

class PulseSimulator {
public:
    void begin(int pin);
    float readVoltage();
    void enableSimulation(bool enable);

private:
    int _pin;
    bool _simulationEnabled;
    float _voltage;
    unsigned long _lastUpdateTime;
    void simulatePulse();
};

#endif
