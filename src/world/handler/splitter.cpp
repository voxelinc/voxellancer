#include "splitter.h"

#include "world/helper/worldobjectsplit.h"

#include "worldobject/worldobject.h"
#include "voxel/voxel.h"

void Splitter::split(std::list<WorldObjectSplit*> &splits) {
    m_splitOffWorldObjects.clear();

    for(WorldObjectSplit *split : splits) {
        WorldObject *worldObject = createWorldObjectFromOrphan(split);
        m_splitOffWorldObjects.push_back(worldObject);
        removeExtractedVoxelsFromEx(split);
    }
}

std::list<WorldObject*> &Splitter::splitOffWorldObjects() {
    return m_splitOffWorldObjects;
}

WorldObject *Splitter::createWorldObjectFromOrphan(WorldObjectSplit *split) {
    glm::ivec3 gridCellShift;
    WorldObject *worldObject;

    worldObject = new WorldObject(split->exWorldObject()->transform().scale());
    gridCellShift = split->gridLlf();

    for(Voxel *voxel : split->splitOffVoxels()) {
        Voxel *voxelClone = new Voxel(voxel->gridCell() - gridCellShift, voxel->color(), voxel->mass());
        worldObject->addVoxel(voxelClone);
    }

   // voxelCluster->recalculateCenterAndMass(); TODO
    return worldObject;
}

void Splitter::removeExtractedVoxelsFromEx(WorldObjectSplit *split) {
    for(Voxel *voxel : split->splitOffVoxels()) {
        split->exWorldObject()->removeVoxel(voxel->gridCell());
    }
}

