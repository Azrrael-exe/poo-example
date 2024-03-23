#ifndef COMM_H
#define COMM_H

#include <Arduino.h>
#include <vector>

class Comm {
    public:
        Comm(uint8_t header, uint8_t buffer_length) {
            this->header = header;
            this->buffer_length = buffer_length;
            this->buffer = new uint8_t[buffer_length];  
            this->input_buffer = new uint8_t[buffer_length];
        }
        void addToBuffer(uint8_t id, uint16_t payload);
        void sendBuffer(Stream &uart);
        bool hasMessage(Stream &uart);
        uint8_t queueLenght();
        std::vector<uint8_t> getQueue();
        
    private:
        uint8_t header;
        uint8_t *buffer;
        uint8_t *input_buffer;
        uint8_t buffer_index = 0;
        uint8_t read_index = 0;
        uint8_t buffer_length;
        uint8_t input_buffer_index = 0;
    };

bool Comm::hasMessage(Stream &uart){
    if (uart.available() > 0){
        if (uart.read() == header){
            uint8_t size = uart.read();
            uint16_t checksum = 0;
            uint8_t temp_buffer[size];
            uart.readBytes(temp_buffer, size);
            for (int i = 0; i < size; i++){
                checksum += temp_buffer[i];
            }
            uint8_t checksum_received = uart.read();
            if (checksum_received == byte(0xFF - checksum)){
                for (int i = 0; i < size; i++){
                    this->input_buffer[i] = temp_buffer[i];
                    this->input_buffer_index++;
                }
                return true;
            }
        }
    }
    return false;
}

uint8_t Comm::queueLenght(){
    return this->input_buffer_index;
}

std::vector<uint8_t> Comm::getQueue(){
    std::vector<uint8_t> queue;
    for (int i = 0; i < this->input_buffer_index; i++){
        queue.push_back(this->input_buffer[i]);
    }
    this->input_buffer_index = 0;
    return queue;
}

void Comm::addToBuffer(uint8_t id, uint16_t payload){
    buffer[buffer_index] = id;
    buffer_index++;
    buffer[buffer_index] = payload >> 8;
    buffer_index++;
    buffer[buffer_index] = payload;
    buffer_index++;
}

void Comm::sendBuffer(Stream &uart){
    uart.write(header);
    uart.write(buffer_index);
    uint16_t checksum  = 0;
    for (int i = 0; i < buffer_index; i++){
        checksum += buffer[i];
        uart.write(buffer[i]);
    }
    uart.write(0xFF - checksum);
    buffer_index = 0;
}
#endif