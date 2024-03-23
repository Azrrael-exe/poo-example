#include <Arduino.h>
#include <vector>

#include "sensor/sensor.h"
#include "constants.h"
#include "comm/comm.h"
#include "read/read.h"
#include "read/parser.h"

AnalogSensor analogSensor = AnalogSensor(
  0xAA,
  Constants::analogSensorPin, 1
);

AnalogSensor analogSensor_1 = AnalogSensor(
  0xAB,
  Constants::analogSensorPin, 2
);

Comm comm = Comm(0x7E, 64);

long sample_timer = millis();
long execution_timer = millis() + 300;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (millis() - sample_timer > 1000){
    analogSensor.call();
    analogSensor_1.call();
    sample_timer = millis();
    if (comm.hasMessage(Serial)) {
      std::vector<uint8_t> buffer = comm.getQueue();
      std::vector<Read> reads = parser(buffer);
      for (int i = 0; i < reads.size(); i++){
        Serial.print("Key: ");
        Serial.print(reads[i].getKey());
        Serial.print(" Value: ");
        Serial.println(reads[i].getValue());
      }
    };
  }
  if (millis() - execution_timer > 20000){
    if(analogSensor.hasChange() || analogSensor_1.hasChange()){
      uint16_t value = 521;
      uint16_t value_1 = 1023;
      comm.addToBuffer(analogSensor.getId(), value);
      comm.addToBuffer(analogSensor_1.getId(), value_1);
      comm.sendBuffer(Serial);
      execution_timer = millis();
    }
  }
} uint8_t myBuffer[] = {1, 2, 3, 4, 5};