#pragma once

#include <glm/glm.hpp>


class Explosion {
public:
    Explosion();
    virtual ~Explosion();

    virtual void spawn(const glm::vec3& position) = 0;
};

