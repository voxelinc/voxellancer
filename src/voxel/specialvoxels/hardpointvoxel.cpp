#include "hardpointvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/components/hardpoint.h"
#include "worldobject/worldobject.h"


HardpointVoxel::HardpointVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<int>("voxels.hardpoint.color"), Property<float>("voxels.hardpoint.mass"), Property<float>("voxels.hardpoint.hp")),
    m_hardpoint(nullptr)
{
}

void HardpointVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);

    m_hardpoint = new Hardpoint(&worldObject->components(), this);
    worldObject->components().addHardpoint(m_hardpoint);
}

void HardpointVoxel::onRemoval() {
    if (m_hardpoint) {
        m_hardpoint->onVoxelRemoval();
        m_hardpoint = nullptr;
    }
    Voxel::onRemoval();
}

void HardpointVoxel::onDestruction() {
    //Drop Ammo?
    Voxel::onDestruction();
}

