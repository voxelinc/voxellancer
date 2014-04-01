#pragma once

#include <vector>
#include <unordered_set>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/intersect.hpp>


class WorldObject;
class Ray;
template<class T> class Handle;

class GeometryHelper {
public:
    // checks for intersection of Ray and rectangle defined by clockwise points p,q,r,s.
    static bool intersectRectangle(const Ray* ray, const glm::vec3& p, const glm::vec3& q, const glm::vec3& r, const glm::vec3& s);
    static bool intersectRectangle(const Ray* ray, const glm::vec3& p, const glm::vec3& q, const glm::vec3& r, const glm::vec3& s, glm::vec3& intersection);

    // Returns the plane, set up by points p, q and r
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
    static WorldObject* closestObject(WorldObject& self, std::vector<Handle<WorldObject>>* objects);

    // Normalize, and return value again if glm::length(value) is 0
    template<typename T>
    static T safeNormalize(const T& value);
};

#include "geometryhelper.inl"
