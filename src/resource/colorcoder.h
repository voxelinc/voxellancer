#pragma once

#include "property/property.h"

class Voxel;

class ColorCoder {
public:
    ColorCoder();

    Voxel* newCodedVoxel(Voxel& voxel);


protected:
    Property<int> prop_engineKey, prop_engineColor;
    Property<float> prop_engineMass, prop_engineHP;
    Property<int> prop_hardpointKey, prop_hardpointColor;
    Property<float> prop_hardpointMass, prop_hardpointHP;
    Property<int> prop_cockpitKey, prop_cockpitColor;
    Property<float> prop_cockpitMass, prop_cockpitHP;
    Property<int> prop_fuelKey, prop_fuelColor;
    Property<float> prop_fuelMass, prop_fuelHP;
    Property<int> prop_crucialKey, prop_crucialColor;
    Property<float> prop_crucialMass, prop_crucialHP;
};
