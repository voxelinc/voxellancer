#pragma once

#include "property/property.h"
#include "voxel/voxel.h"

class ColorCoder {
public:
    ColorCoder();
    ~ColorCoder();

    Voxel* decodeToInstance(cvec3 gridCell, cvec3 color);

private:
    int colorToInt(cvec3 color);

    Property<int> prop_keyEngine, prop_colorEngine,
                    prop_keyHardpoint, prop_colorHardpoint,
                    prop_keyCockpit, prop_colorCockpit;
};