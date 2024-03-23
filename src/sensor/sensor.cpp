#include "sensor.h"

float AnalogSensor::getRead(){
    this->has_change = false;
    return this->value * this->scale;
}

float AnalogSensor::getScale() {
    return this->scale;
}

void AnalogSensor::setScale(float new_scale) {
    if (new_scale > 0){
        this->scale = new_scale;
    }
}

uint8_t AnalogSensor::getId(){
    return this->id;
}

long AnalogSensor::read(){
    this->temp_read[this->temp_index] = analogRead(this->pin);
}

void AnalogSensor::call(){
    this->read();
    this->temp_index++;
    if (this->temp_index >= 5){
        this->temp_index = 0;
        long sum = 0;
        for (int i = 0; i < 5; i++){
            sum += this->temp_read[i];
        }
        this->value = sum / 5;
        this->has_change = true;
    }
}

void DigitalSensor::call(){
    bool temp_value = digitalRead(this->pin);
    if (temp_value != this->value){
        this->value = temp_value;
        this->has_change = true;
    }
    else {
        this->has_change = false;
    }
}

bool DigitalSensor::getRead(){
    this->has_change = false;
    return this->value;
}