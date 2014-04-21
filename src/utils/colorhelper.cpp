#include "colorhelper.h"


uint32_t ColorHelper::flipColorForGPU(uint32_t readable) {
    uint32_t r = readable >> 24;
    uint32_t g = (readable & 0x00FF0000) >> 16;
    uint32_t b = (readable & 0x0000FF00) >> 8;
    uint32_t a = (readable & 0x000000FF);
    return b | g << 8 | r << 16 | a << 24;
}