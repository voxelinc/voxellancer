#include "wrecker.h"

#include "physics/physics.h"

#include "voxel/voxel.h"

#include "universe/helper/worldobjectmodification.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectinfo.h"


void Wrecker::wreck(std::list<WorldObjectModification>& worldObjectModifications) {
    for (WorldObjectModification& modification : worldObjectModifications) {
        WorldObject* object = modification.worldObject();

        if (object->isCrucialVoxelDestroyed()) {
            object->unspawn();
            createWreckFromObject(object);
        }
    }
}

void Wrecker::createWreckFromObject(WorldObject* object) {
    WorldObject* wreckage = new WorldObject(object->transform());

    wreckage->info().setName(object->info().name() + " - wreck");
    wreckage->physics().setSpeed(object->physics().speed());

    for (auto& pair : object->voxelMap()) {
        wreckage->addVoxel(new Voxel(*pair.second));
    }

    wreckage->spawn(*object->sector());
}

