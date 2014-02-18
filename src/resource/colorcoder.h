#pragma once

#include "property/property.h"


class Voxel;

class ColorCoder {
public:
    ColorCoder();

    Voxel* newCodedVoxel(const Voxel& voxel);


protected:
    Property<int> m_engineSlotPrefix;
    Property<int> m_hardpointPrefix;
    Property<int> m_cockpitPrefix;
    Property<int> m_fuelPrefix;
    Property<int> m_crucialPrefix;
};

