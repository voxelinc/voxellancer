#include "spawnhelper.h"

#include "ai/character.h"

#include "factions/faction.h"

#include "resource/worldobjectbuilder.h"

#include "world/god.h"
#include "world/world.h"

#include "worldobject/ship.h"


SpawnHelper::SpawnHelper(World* world):
    m_world(world)
{
}

Ship* SpawnHelper::spawnShip(const std::string& name, const glm::vec3& position, Faction& faction) {
    Ship *ship = WorldObjectBuilder(name).buildShip();
    ship->transform().setPosition(position);
    ship->character()->setFaction(faction);
    m_world->god().scheduleSpawn(ship);
    return ship;
}

