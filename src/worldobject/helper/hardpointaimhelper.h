#pragma once

#include <glm/glm.hpp>


class Hardpoint;
class WorldObject;

/*
    Identifies the direction a hardpoint must shoot to hit a worldObject
    given the movement of this other WorldObject doesn't change too
    much
*/
class HardpointAimHelper {
public:
    HardpointAimHelper(Hardpoint* shooter, WorldObject* targetObject);

    void aim();

    /*
        For some reason it might be impossible to hit the target
        (e.g. ship faster than bullet) then this will return false.
        direction() and point() are invalid then.
    */
    bool isHitable();

    const glm::vec3& direction();
    const glm::vec3& point();


protected:
    Hardpoint* m_shooter;
    WorldObject* m_targetObject;

    bool m_aimed;

    glm::vec3 m_shooterPosition;
    glm::vec3 m_targetPosition;
    float m_bulletSpeed;
    glm::vec3 m_targetSpeed;

    bool m_hitable;

    glm::vec3 m_direction;
    glm::vec3 m_point;


    float bulletTravelTime(const glm::vec3& point);
    glm::vec3 targetPositionIn(float deltaSec);
};

