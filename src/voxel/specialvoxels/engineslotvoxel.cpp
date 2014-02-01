#include "enginevoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/engine.h"
#include "worldobject/worldobject.h"


EngineVoxel::EngineVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, int index, Property<int>("voxels.engineSlot.color"), Property<float>("voxels.engineSlot.mass"), Property<float>("voxels.engineSlot.hp")),
    m_engineSlot(nullptr)
{
}

void EngineVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);

    m_engineSlot = new EngineSlot(&worldObject->components(), this);
    worldObject->components().addEngineSlot(m_engineSlot);
}

void EngineVoxel::onRemoval() {
    if (m_engineSlot){
        m_engineSlot->onVoxelRemoval();
        m_engineSlot = nullptr;
    }
    Voxel::onRemoval();
}

void EngineVoxel::onDestruction() {
    Voxel::onDestruction();
}

