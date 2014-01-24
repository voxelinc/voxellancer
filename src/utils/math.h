#pragma once

#include <glm/gtx/quaternion.hpp>


class Math {
public:
    /*
    Returns the quaternion that is to be added to the local-coordinate-system view direction (0,0,-1)
    to look into the local-coordinate-system view direction dir
    */
    static glm::quat differenceFromViewDirection(const glm::vec3& dir);

    /*
    Returns the quaternion that from needs to be rotated around the x and y axis to point in the same
    direction as to
    */
    static glm::quat xyDifference(const glm::vec3& from, const glm::vec3& to);
};

