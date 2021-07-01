#include "Bypass.h"
#include <SimpleMemory/SimpleMemory.h>

void Bypass::init(){
    uint32_t base = sm::internal::base_address();
    sm::internal::write_container<char>(base+0x202AC8, {'\xE9', '\x1C', '\x01', '\x00'});

}

void Bypass::uninit(){

}