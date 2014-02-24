#pragma once

#include <glm/glm.hpp>

#include "worldobject/components/weapon.h"


class SoundProperties;
class Bullet;

class Gun: public Weapon {
public:
    Gun(const std::string& equipmentKey);

    virtual const SoundProperties& fireSound() const = 0;
    
    virtual float bulletLifetime() const = 0;
    virtual float bulletSpeed() const = 0;

    virtual void fireAtPoint(const glm::vec3& point);

    virtual void update(float deltaSec) override;


protected:
    virtual Bullet* createBullet() = 0;
    void setupBullet(Bullet* bullet, const glm::vec3& point);
};

