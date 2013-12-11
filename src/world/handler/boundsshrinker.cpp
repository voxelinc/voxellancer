#include "boundsshrinker.h"

#include "worldobject/worldobject.h"


void BoundsShrinker::shrink(std::list<WorldObjectModification>& worldObjectModifications) {
    for(WorldObjectModification& worldObjectModification : worldObjectModifications) {
        worldObjectModification.worldObject()->collisionDetector().recalculateAABB();
    }
}
