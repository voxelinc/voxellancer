#pragma once

#include <string>

#include "equipment/weapons/bullet.h"


class InstancedBullet : public Bullet {
public:
    InstancedBullet(const std::string& name);

    const std::string& name() const;

    virtual void update(float deltaSec) override;

    virtual Transform& transform() override;
    virtual void setTransform(const Transform& transform) override;

    virtual void setSpeed(const Speed& speed) override;

    virtual void spawn() override;
    virtual void remove() override;

    virtual float length() override;


protected:
    std::string m_name;
};

