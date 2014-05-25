#include "splitter.h"

#include <unordered_set>

#include "universe/helper/splitdata.h"

#include "physics/physics.h"

#include "voxel/voxel.h"

#include "worldobject/worldobjectinfo.h"
#include "worldobject/worldobject.h"


void Splitter::split(std::vector<std::shared_ptr<SplitData>> &splits) {
    for (std::shared_ptr<SplitData> split : splits) {
        performSplit(split);
    }
}

void Splitter::performSplit(std::shared_ptr<SplitData> split) {
    WorldObject *worldObject;
    Transform transform = split->exWorldObject()->transform();
    transform.setCenter(transform.center()/* - glm::vec3(split->llf())*/);

    worldObject = new WorldObject(transform);

    worldObject->info().setName(split->exWorldObject()->info().name() + " - splitoff");
    worldObject->physics().setSpeed(worldObject->physics().speed());

    for(Voxel* voxel : split->splitOffVoxels()) {
        Voxel* voxelClone = new Voxel(*voxel);
        worldObject->addVoxel(voxelClone);
        split->exWorldObject()->removeVoxel(voxel);
    }

    worldObject->spawn(*split->exWorldObject()->sector());
}

