#include "engineslotvoxel.h"

#include "property/property.h"

#include "equipment/engine.h"
#include "equipment/engineslot.h"

#include "voxel/voxelcluster.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"


EngineSlotVoxel::EngineSlotVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<uint32_t>::get("voxels.engineSlot.color"), Property<float>::get("voxels.engineSlot.density"), Property<float>::get("voxels.engineSlot.hp")),
    m_engineSlot(nullptr)
{
}

EngineSlotVoxel::EngineSlotVoxel(const EngineSlotVoxel& other):
    SpecialVoxel(other)
{
    // m_engineSlot remains nullptr
}

void EngineSlotVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);
    m_engineSlot = std::make_shared<EngineSlot>(&worldObject->components(), this);
    worldObject->components().addEngineSlot(m_engineSlot);
}

Visuals EngineSlotVoxel::visuals() const {
    return Visuals(
        m_engineSlot->engine() ? m_engineSlot->engine()->visuals() : Voxel::visuals()
    );
}

void EngineSlotVoxel::onRemoval() {
    if (m_engineSlot){
        m_engineSlot->onVoxelRemoval();
        m_engineSlot = nullptr;
    }
    Voxel::onRemoval();
}

EngineSlotVoxel* EngineSlotVoxel::clone() const {
    return new EngineSlotVoxel(*this);
}

