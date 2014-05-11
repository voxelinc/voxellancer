#pragma once

#include "explosion.h"


class DummyExplosion : public Explosion {
public:
    virtual ~DummyExplosion() override;

    virtual void spawn(const glm::vec3& position);
};

