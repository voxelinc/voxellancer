#include "engineslotvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/components/engine.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"


EngineSlotVoxel::EngineSlotVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<uint32_t>("voxels.engineSlot.color"), Property<float>("voxels.engineSlot.mass"), Property<float>("voxels.engineSlot.hp")),
    m_engineSlot(nullptr)
{
}

void EngineSlotVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);
    m_engineSlot = std::make_shared<EngineSlot>(&worldObject->components(), this);
    worldObject->components().addEngineSlot(m_engineSlot);
}

Visuals EngineSlotVoxel::visuals() const {
    return Visuals(
        m_engineSlot->engine() ? m_engineSlot->engine()->visuals() : SpecialVoxel::visuals()
    );
}

void EngineSlotVoxel::onRemoval() {
    if (m_engineSlot){
        m_engineSlot->components()->removeEngineSlot(m_engineSlot);
        m_engineSlot = nullptr;
    }
    SpecialVoxel::onRemoval();
}

void EngineSlotVoxel::onDestruction(const WorldObject* owner) {
    SpecialVoxel::onDestruction(owner);
}

