#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


class HUD;


/*
    Hudget, named after Widget - is an element on the HUD
*/
class Hudget {
public:
    Hudget(HUD* hud);

    HUD* hud();

    virtual glm::vec3 position() const = 0;
    virtual glm::quat orientation() const = 0;

    virtual void update(float deltaSec) = 0;
    virtual void draw() = 0;


protected:
    HUD* m_hud;
};

