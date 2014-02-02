#include "engineslotvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/components/engine.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/worldobject.h"


EngineSlotVoxel::EngineSlotVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<int>("voxels.engineSlot.color"), Property<float>("voxels.engineSlot.mass"), Property<float>("voxels.engineSlot.hp")),
    m_engineSlot(nullptr)
{
}

void EngineSlotVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);

    m_engineSlot = new EngineSlot(&worldObject->components(), this);
    worldObject->components().addEngineSlot(m_engineSlot);
}

void EngineSlotVoxel::onRemoval() {
    if (m_engineSlot){
        m_engineSlot->onVoxelRemoval();
        m_engineSlot = nullptr;
    }
    Voxel::onRemoval();
}

void EngineSlotVoxel::onDestruction() {
    Voxel::onDestruction();
}

