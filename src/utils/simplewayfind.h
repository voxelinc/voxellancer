#pragma once

#include <set>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"


class WorldObject;

// Very simple wayfinding algorithm. 
// Checks for an obstacle on the direct path to the target and aims next to it until the line is free again
class SimpleWayfind {
public:
    static glm::vec3 calculateTravelPoint(WorldObject& object, const glm::vec3& targetPoint);

protected:
    static glm::vec3 calculateEvasionPointFor(WorldObject& self, WorldObject& obstacle, const glm::vec3& targetPoint);
    static WorldObject* closestObjectExceptSelf(WorldObject& self, std::set<WorldObject*>* objects);
};

