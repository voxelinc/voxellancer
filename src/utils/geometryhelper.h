#pragma once

#include <unordered_set>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

class WorldObject;

class GeometryHelper {
public:
    // Returns the angle between u and v
    static glm::vec3 plane(const glm::vec3& p, const glm::vec3& q, const glm::vec3& r);
    // Returns the angle between u and v
    static float angleBetween(const glm::vec3& u, const glm::vec3& v);
    // Returns the angle between vector u and plane with normal v
    static float angleBetweenVectorPlane(const glm::vec3& u, const glm::vec3& v);
    // Returns the quaternion that rotates from u to v
    static glm::quat quatFromTo(const glm::vec3& u, const glm::vec3& v);
    // Returns the quaternion from (0,0,-1) to dir
    static glm::quat quatFromViewDirection(const glm::vec3& dir);
    // Return the WorldObject from objects that is closest to self, measured position to position
    static WorldObject* closestObject(WorldObject& self, std::unordered_set<WorldObject*>* objects);

};

