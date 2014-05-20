#include "worldobjectmanager.h"

#include "worldtree/worldtree.h"

#include "sector.h"


WorldObjectManager::WorldObjectManager(Sector& sector):
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
