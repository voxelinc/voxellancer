#pragma once

#include "property/property.h"
#include "voxel/voxel.h"

class ColorCoder {
public:
    ColorCoder();
    ~ColorCoder();

    Voxel* cloneCoded(Voxel* voxel);

private:
    int colorToInt(cvec3 color);
    cvec3 intToColor(int color);

    Property<int> prop_keyEngine, prop_colorEngine,
                    prop_keyHardpoint, prop_colorHardpoint,
                    prop_keyCockpit, prop_colorCockpit;
};