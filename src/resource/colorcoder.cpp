#include "colorcoder.h"

#include "voxel/specialvoxels/engineslotvoxel.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "voxel/specialvoxels/cockpitvoxel.h"
#include "voxel/specialvoxels/fuelvoxel.h"
#include "voxel/specialvoxels/crucialvoxel.h"


ColorCoder::ColorCoder():
    m_engineSlotPrefix("voxels.engineSlot.prefix"),
    m_hardpointPrefix("voxels.hardpoint.prefix"),
    m_cockpitPrefix("voxels.cockpit.prefix"),
    m_fuelPrefix("voxels.fuel.prefix"),
    m_crucialPrefix("voxels.crucial.prefix")
{
}

Voxel* ColorCoder::newCodedVoxel(const Voxel& voxel) {
    uint32_t color = voxel.color();
    uint32_t prefixBits = (color & 0xFFFF00) >> 8;
    int index = color & 0x0000FF;

    if(prefixBits == m_engineSlotPrefix) {
        return new EngineSlotVoxel(voxel.gridCell(), index);
    }
    if(prefixBits == m_hardpointPrefix) {
        return new HardpointVoxel(voxel.gridCell(), index);
    }
    if(prefixBits == m_cockpitPrefix) {
        return new CockpitVoxel(voxel.gridCell(), index);
    }
    if(prefixBits == m_fuelPrefix) {
        return new FuelVoxel(voxel.gridCell(), index);
    }
    if(prefixBits == m_crucialPrefix) {
        return new CrucialVoxel(voxel.gridCell(), index);
    }

    return new Voxel(voxel);
}

