#include "colorcoder.h"

#include "voxel/specialvoxels/enginevoxel.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "voxel/specialvoxels/cockpitvoxel.h"


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

cvec3 ColorCoder::intToColor(int color){
    return cvec3(   (color & 0xFF0000) >> 16, 
                    (color & 0x00FF00) >> 8, 
                    color & 0x0000FF);
}

Voxel* ColorCoder::cloneCoded(Voxel* voxel){
    int colorInt = colorToInt(voxel->color());

    if (colorInt == prop_keyEngine){
        return new EngineVoxel(voxel->gridCell(), intToColor(prop_colorEngine));
    } else if (colorInt == prop_keyHardpoint){
        return new HardpointVoxel(voxel->gridCell(), intToColor(prop_colorHardpoint));
    } else if (colorInt == prop_keyCockpit){
        return new CockpitVoxel(voxel->gridCell(), intToColor(prop_colorCockpit));
    } else {
        return new Voxel(voxel->gridCell(), voxel->color());
    }

}