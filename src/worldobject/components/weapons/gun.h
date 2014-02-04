#pragma once

#include <glm/glm.hpp>

#include "bullet.h"
#include "worldobject/components/weapon.h"


class Gun: public Weapon {
public:
    Gun(const std::string& equipmentKey);

    virtual float bulletLifetime() const = 0;
    virtual float bulletSpeed() const = 0;

    virtual void fireAtPoint(const glm::vec3& point);

    virtual void update(float deltaSec) override;


protected:
    virtual Bullet* createBullet() = 0;
    void setupBullet(Bullet* bullet, const glm::vec3& point);
};

