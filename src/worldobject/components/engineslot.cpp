#include "engineslot.h"

#include <cassert>

#include "voxel/specialvoxels/engineslotvoxel.h"

#include "worldobject/components/engine.h"
#include "worldobject/worldobjectcomponents.h"


EngineSlot::EngineSlot(WorldObjectComponents* components, EngineSlotVoxel* voxel):
    WorldObjectSlot(components, voxel->index()),
    m_voxel(voxel),
    m_engine(nullptr)
{
}

EngineSlotVoxel* EngineSlot::voxel() {
    return m_voxel;
}

const glm::vec3& EngineSlot::direction() {
    return m_direction;
}

void EngineSlot::setDirection(const glm::vec3& direction) {
    m_direction = direction;
}

Engine* EngineSlot::engine() {
    return m_engine;
}

void EngineSlot::setEngine(Engine* engine) {
    assert(mountable(engine->equipmentKey()));
    m_engine = engine;
    m_engine->setEngineSlot(this);
}

void EngineSlot::update(float deltaSec) {
    if(m_engine) {
        m_engine->update(deltaSec);
    }
}

void EngineSlot::onVoxelRemoval() {
    m_components->removeEngineSlot(this);
}

