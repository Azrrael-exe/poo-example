#ifndef PARSER_H
#define PARSER_H

#include <Arduino.h>
#include <vector>
#include "read/read.h"

std::vector<Read> parser(std::vector<uint8_t> buffer){
    std::vector<Read> reads;
    for (int i = 0; i < buffer.size(); i+=3){
        reads.push_back(Read(buffer[i], (buffer[i+1] << 8) | buffer[i+2]));
    }
    return reads;
}

#endif
