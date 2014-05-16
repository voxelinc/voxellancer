#include "splitter.h"

#include <unordered_set>

#include "universe/helper/splitdata.h"

#include "physics/physics.h"

#include "voxel/voxel.h"

#include "worldobject/worldobjectinfo.h"
#include "worldobject/worldobject.h"


void Splitter::split(std::vector<std::shared_ptr<SplitData>> &splits) {
    std::unordered_set<WorldObject*> splittedWorldObjects;

    for (std::shared_ptr<SplitData> split : splits) {
        createWorldObjectFromSplitOff(split);

        splittedWorldObjects.insert(split->exWorldObject());
        removeExtractedVoxelsFromEx(split);
    }
}

void Splitter::createWorldObjectFromSplitOff(std::shared_ptr<SplitData> split) {
    WorldObject *worldObject;
    Transform transform = split->exWorldObject()->transform();
    transform.setCenter(transform.center()/* - glm::vec3(split->llf())*/);

    worldObject = new WorldObject(transform);

    worldObject->info().setName(split->exWorldObject()->info().name() + " - splitoff");
    worldObject->physics().setSpeed(worldObject->physics().speed());

    for(Voxel *voxel : split->splitOffVoxels()) {
        Voxel *voxelClone = new Voxel(*voxel);
        worldObject->addVoxel(voxelClone);
    }

    worldObject->spawn(split.exWorldObject()->sector());
}

void Splitter::removeExtractedVoxelsFromEx(std::shared_ptr<SplitData> split) {
    for(Voxel *voxel : split->splitOffVoxels()) {
        split->exWorldObject()->removeVoxel(voxel);
    }
}

