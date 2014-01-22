#pragma once

#include <vector>

#include "geometry/sphere.h"

#include "property/property.h"

#include "crosshair.h"


class Player;

class HUD {
public:
    HUD(Player* player);

    Player* player();
    const Sphere& sphere() const;
    CrossHair& crossHair();

    glm::vec3 position() const;
    glm::quat orientation() const;

    void setCrossHairOffset(const glm::vec2& mousePosition);

    void update(float deltaSec);
    void draw();


protected:
    Player* m_player;
    Sphere m_sphere;

    CrossHair m_crossHair;

    glm::vec3 m_position;
};

