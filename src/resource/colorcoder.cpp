#include "colorcoder.h"

ColorCoder::ColorCoder() :
    prop_keyEngine("colorcode.keyEngine"),
    prop_colorEngine("colorcode.colorEngine"),
    prop_keyHardpoint("colorcode.keyHardpoint"),
    prop_colorHardpoint("colorcode.colorHardpoint"),
    prop_keyCockpit("colorcode.keyCockpit"),
    prop_colorCockpit("colorcode.colorCockpit")
{
    
}

ColorCoder::~ColorCoder(){

}

int ColorCoder::colorToInt(cvec3 color){
    return color.r << 16 | color.g << 8 | color.b;
}

Voxel* ColorCoder::decodeToInstance(cvec3 gridCell, cvec3 color){
    int colorInt = colorToInt(color);

    /*if (colorInt == prop_keyEngine){
        return new EngineVoxel(gridCell, prop_colorEngine);
    } else if (colorInt == prop_keyHardpoint){
        return new HardpointVoxel(gridCell, prop_colorHardpoint);
    } else if (colorInt == prop_keyCockpit){
        return new CockpitVoxel(gridCell, prop_colorCockpit);
    } else {*/
        return new Voxel(gridCell, color);
    //}

}