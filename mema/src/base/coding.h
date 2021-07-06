#pragma once
#include <stdint.h>

#include "iostream"
//reference from leveldb coding.cc
using namespace std;
namespace mema{

inline uint32_t DecodeFixd32(const char* ptr){
    const uint8_t* const buffer = reinterpret_cast<const uint8_t*>(ptr);

    uint32_t qq = ((static_cast<uint32_t>(buffer[0]))    |
           ((static_cast<uint32_t>(buffer[1]))<<8 ) |
           ((static_cast<uint32_t>(buffer[2]))<<16) |
           ((static_cast<uint32_t>(buffer[3]))<<24) ) ;
    cout << qq  <<endl;
    return (static_cast<uint32_t>(buffer[0]))    |
           ((static_cast<uint32_t>(buffer[1]))<<8 ) |
           ((static_cast<uint32_t>(buffer[2]))<<16) |
           ((static_cast<uint32_t>(buffer[3]))<<24) ;
}

}// end namespace

