#pragma once

#include <stdint.h>



class ColorHelper {
public:
    // Flips bytes from human readable format to OpenGL format
    static uint32_t flipColorForGPU(uint32_t humanReadable);
};
