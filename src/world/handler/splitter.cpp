#include "splitter.h"
#include <unordered_set>

#include <glow/AutoTimer.h>

#include "world/helper/worldobjectsplit.h"

#include "worldobject/worldobject.h"
#include "voxel/voxel.h"

void Splitter::split(std::list<WorldObjectSplit*> &splits) {
    std::unordered_set<WorldObject*> splittedWorldObjects;

    m_splitOffWorldObjects.clear();

    for(WorldObjectSplit *split : splits) {
        glow::AutoTimer t("Splitter: " + split->exWorldObject()->objectInfo().name());
        WorldObject *worldObject = createWorldObjectFromSplitOff(split);
        m_splitOffWorldObjects.push_back(worldObject);
        splittedWorldObjects.insert(split->exWorldObject());
        removeExtractedVoxelsFromEx(split);
    }

    for (WorldObject* splitted : splittedWorldObjects) {
        splitted->collisionDetector().rebuildVoxelTree();
    }
}

std::list<WorldObject*> &Splitter::splitOffWorldObjects() {
    return m_splitOffWorldObjects;
}

WorldObject *Splitter::createWorldObjectFromSplitOff(WorldObjectSplit *split) {
    WorldObject *worldObject;
    WorldTransform transform = split->exWorldObject()->transform();
    transform.setCenter(transform.center()/* - glm::vec3(split->llf())*/);

    worldObject = new WorldObject(transform, split->exWorldObject()->collisionFilterClass());


    worldObject->objectInfo().setName(split->exWorldObject()->objectInfo().name() + " - splitoff");
    worldObject->objectInfo().setCanLockOn(false);
    worldObject->objectInfo().setShowOnHud(false);

    worldObject->physics().setSpeed(worldObject->physics().speed());
    worldObject->physics().setAngularSpeed(worldObject->physics().angularSpeed());

    for(Voxel *voxel : split->splitOffVoxels()) {
        Voxel *voxelClone = new Voxel(voxel->gridCell()/*-split->llf()*/, voxel->color(), voxel->mass(), voxel->hp());
        worldObject->addVoxel(voxelClone);
    }

    worldObject->recalculateCenterAndMass();

    return worldObject;
}

void Splitter::removeExtractedVoxelsFromEx(WorldObjectSplit *split) {
    for(Voxel *voxel : split->splitOffVoxels()) {
        split->exWorldObject()->removeVoxel(voxel->gridCell());
    }
}

