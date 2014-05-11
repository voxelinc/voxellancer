#pragma once

#include "explosion.h"


class RingExplosion : public Explosion {
public:
    RingExplosion();
    virtual ~RingExplosion() override;

    virtual void spawn(const glm::vec3& position) override;
};
