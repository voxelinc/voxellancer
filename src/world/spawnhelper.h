#pragma once

#include <string>

#include <glm/glm.hpp>


class Faction;
class Ship;
class World;

class SpawnHelper {
public:
    SpawnHelper(World* world);

    Ship* spawnShip(const std::string& name, const glm::vec3& position, Faction& faction);


protected:
    World* m_world;
};
