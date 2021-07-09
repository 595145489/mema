#pragma once
#include <stdint.h>

#include "iostream"
//reference from leveldb coding.cc
using namespace std;
namespace mema{

inline uint32_t DecodeFixd32(const char* ptr){
    const uint8_t* const buffer = reinterpret_cast<const uint8_t*>(ptr);
    return (static_cast<uint32_t>(buffer[0]))    |
           ((static_cast<uint32_t>(buffer[1]))<<8 ) |
           ((static_cast<uint32_t>(buffer[2]))<<16) |
           ((static_cast<uint32_t>(buffer[3]))<<24) ;
}

inline void EncodeFixed32(char* dst, uint32_t value) {
    uint8_t* const buffer = reinterpret_cast<uint8_t*>(dst);
      // Recent clang and gcc optimize this to a single mov / str instruction.  
      buffer[0] = static_cast<uint8_t>(value);
      buffer[1] = static_cast<uint8_t>(value >> 8);
      buffer[2] = static_cast<uint8_t>(value >> 16);
      buffer[3] = static_cast<uint8_t>(value >> 24);
}

}// end namespace

