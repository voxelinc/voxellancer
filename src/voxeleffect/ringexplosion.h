#pragma once

#include <glm/gtc/quaternion.hpp>

#include "explosion.h"


class RingExplosion : public Explosion {
public:
    RingExplosion();
    virtual ~RingExplosion() override;

    virtual void spawn(const glm::vec3& position) override;


protected:
    glm::quat m_planeOrientation;

    void inner(const glm::vec3& position);
    void outer(const glm::vec3& position);
    void fire(const glm::vec3& position);
};

