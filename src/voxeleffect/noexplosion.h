#pragma once

#include "explosion.h"


class NoExplosion : public Explosion {
public:
    NoExplosion();
    virtual ~NoExplosion() override;

    virtual void spawn(const glm::vec3& position) override;
};

