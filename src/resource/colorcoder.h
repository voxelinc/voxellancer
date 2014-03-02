#pragma once

#include "property/property.h"


class Voxel;

class ColorCoder {
public:
    ColorCoder();

    Voxel* newCodedVoxel(const Voxel& voxel);


protected:
    Property<uint32_t> m_engineSlotPrefix;
    Property<uint32_t> m_hardpointPrefix;
    Property<uint32_t> m_cockpitPrefix;
    Property<uint32_t> m_fuelPrefix;
    Property<uint32_t> m_crucialPrefix;
};

