#include "hardpointvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "equipment/hardpoint.h"
#include "equipment/weapon.h"
#include "worldobject/worldobject.h"


HardpointVoxel::HardpointVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<int>("voxels.hardpoint.color"), Property<float>("voxels.hardpoint.mass"), Property<float>("voxels.hardpoint.hp")),
    m_hardpoint(nullptr)
{

}

Visuals HardpointVoxel::visuals() const {
    return Visuals(
        m_hardpoint->weapon() ? m_hardpoint->weapon()->visuals() : Voxel::visuals()
    );
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

