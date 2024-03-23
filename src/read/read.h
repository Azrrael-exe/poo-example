#ifndef READ_H
#define READ_H

#include <Arduino.h>

class Read{
    public:
        Read(){};
        Read(uint8_t key, uint16_t value){
            this->key = key;
            this->value = value; 
        };
        uint8_t getKey(){return this->key;};
        uint16_t getValue(){return this->value;};
    private:
        uint8_t key;
        uint16_t value;
};

#endif