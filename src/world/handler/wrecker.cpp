#include "wrecker.h"

#include "world/helper/worldobjectmodification.h"
#include "worldobject/worldobject.h"
#include "worldobject/worldobjectinfo.h"
#include "physics/physics.h"
#include "voxel/voxel.h"

void Wrecker::detectWreckedObjects(std::list<WorldObjectModification>& worldObjectModifications) {
    m_wreckedObjects.clear();
    m_newWreckages.clear();

    for (WorldObjectModification& modification : worldObjectModifications) {
        WorldObject* object = modification.worldObject();
        if (object->isCrucialVoxelDestroyed()) {
            m_wreckedObjects.push_back(object);
            m_newWreckages.push_back(wreckFromObject(object));
        }
    }

}

std::list<WorldObject*>& Wrecker::wreckedObjects() {
    return m_wreckedObjects;
}

std::list<WorldObject*>& Wrecker::newWreckages() {
    return m_newWreckages;
}

WorldObject* Wrecker::wreckFromObject(WorldObject* object) {
    WorldObject* wreckage = new WorldObject(object->transform());

    wreckage->info().setName(object->info().name() + " - wreck");
    wreckage->physics().setSpeed(object->physics().speed());

    for (auto& pair : object->voxelMap()) {
        wreckage->addVoxel(new Voxel(*pair.second));
    }

    return wreckage;
}

void Wrecker::applyOnWreckageHooks() {
    for (WorldObject* worldObject : m_wreckedObjects) {
        worldObject->onDeath();
    }
}
