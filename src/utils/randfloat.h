#pragma once
#include <stdint.h>


class RandFloat {
public:
    static float rand(float from, float to);
    static uint32_t _xor_rand();
    static float rand_xor(float from, float to);
    static float randomize(float value, float randomization);
};

