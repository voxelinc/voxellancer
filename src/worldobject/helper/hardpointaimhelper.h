#pragma once

#include <glm/glm.hpp>


class Hardpoint;
class Vpxel;
class WorldObject;

/**
 *   Identifies the direction a hardpoint must shoot to hit a moving WorldObject
 *   given the direction and the speed of this other WorldObject doesn't change too
 *   much
*/
class HardpointAimHelper {
public:
    HardpointAimHelper(Hardpoint* hardpoint, const WorldObject* targetObject);

    void aim(float maxOffset = 0.1f);

    /*
        For some reason it might be impossible to hit the target
        (e.g. ship faster than bullet) then this will return false.
        direction() and point() are invalid then.
    */
    bool isHitable();

    const glm::vec3& direction();
    const glm::vec3& point();


protected:
    Hardpoint* m_hardpoint;
    const WorldObject* m_targetObject;

    bool m_aimed;

    glm::vec3 m_hardpointPosition;

    glm::vec3 m_targetPosition;
    glm::vec3 m_targetSpeed;

    float m_bulletSpeed;
    float m_bulletLifetime;

    bool m_hitable;

    glm::vec3 m_direction;
    glm::vec3 m_point;


    float bulletTravelTime(const glm::vec3& point);
    glm::vec3 targetPositionIn(float deltaSec);
    float bulletSpeedInDirection(const glm::vec3& direction);
};

