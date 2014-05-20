#include "worldobjectmanager.h"

#include "worldtree/worldtree.h"

#include "sector.h"
#include "universe.h"


WorldObjectManager::WorldObjectManager(Sector& sector):
    GameObjectManager<WorldObject>(sector.universe()),
    m_sector(sector)
{
}

WorldObjectManager::~WorldObjectManager() = default;

void WorldObjectManager::onObjectAddtition(WorldObject* object) {
    m_sector.worldTree().insert(object);
}

void WorldObjectManager::onObjectRemoval(WorldObject* object) {
    m_sector.worldTree().remove(object);
}
