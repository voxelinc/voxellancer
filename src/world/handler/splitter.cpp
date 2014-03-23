#include "splitter.h"
#include <unordered_set>


#include "world/helper/splitdata.h"

#include "voxel/voxel.h"
#include "physics/physics.h"
#include "ui/objectinfo.h"
#include "worldobject/worldobject.h"

void Splitter::split(std::vector<std::shared_ptr<SplitData>> &splits) {
    std::unordered_set<WorldObject*> splittedWorldObjects;

    m_splitOffWorldObjects.clear();

    for (std::shared_ptr<SplitData> split : splits) {
        WorldObject *worldObject = createWorldObjectFromSplitOff(split);
        m_splitOffWorldObjects.push_back(worldObject);
        splittedWorldObjects.insert(split->exWorldObject());
        removeExtractedVoxelsFromEx(split);
    }
}

std::list<WorldObject*> &Splitter::splitOffWorldObjects() {
    return m_splitOffWorldObjects;
}

WorldObject* Splitter::createWorldObjectFromSplitOff(std::shared_ptr<SplitData> split) {
    WorldObject *worldObject;
    Transform transform = split->exWorldObject()->transform();
    transform.setCenter(transform.center()/* - glm::vec3(split->llf())*/);

    worldObject = new WorldObject(transform);

    worldObject->objectInfo().setName(split->exWorldObject()->objectInfo().name() + " - splitoff");
    worldObject->physics().setSpeed(worldObject->physics().speed());

    for(Voxel *voxel : split->splitOffVoxels()) {
        Voxel *voxelClone = new Voxel(*voxel);
        worldObject->addVoxel(voxelClone);
    }

    return worldObject;
}

void Splitter::removeExtractedVoxelsFromEx(std::shared_ptr<SplitData> split) {
    for(Voxel *voxel : split->splitOffVoxels()) {
        split->exWorldObject()->removeVoxel(voxel);
    }
}

