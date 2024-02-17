#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

template <typename T>
class SensorABC {
public:
    SensorABC() {} // Default constructor
    virtual T getRead() = 0; // Pure virtual function
    virtual void call() = 0;
    bool hasChange() {
        return this->has_change;
    };
protected:
    bool has_change;
};

class AnalogSensor : public SensorABC<float> {
public:
    AnalogSensor(uint8_t pin, float scale) : pin(pin), scale(scale) {} // Constructor initialization list
    float getRead() override; // Override base class method
    float getScale(); // Declaration of the getScale method
    void setScale(float new_scale); // Declaration of the setScale method
    void call() override;
protected:
    uint8_t pin;
    float scale;
    float value;
    long temp_read[5];
    uint8_t temp_index = 0;
    long read();
};

class DigitalSensor : public SensorABC<bool> {
    public:
        DigitalSensor(uint8_t pin) : pin(pin) {}
        bool getRead() override;
        void call() override;
    protected:
        uint8_t pin;
        bool value;
};

#endif