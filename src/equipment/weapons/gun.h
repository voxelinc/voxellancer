#pragma once

#include <glm/glm.hpp>

#include "equipment/weapon.h"

#include "sound/soundproperties.h"


class Bullet;

class Gun: public Weapon {
public:
    Gun(const std::string& equipmentKey);

    float bulletSpeed() const;
    void setBulletSpeed(float bulletSpeed);

    const SoundProperties& fireSound() const;
    void setFireSound(const SoundProperties& fireSound);

    virtual void fireAtPoint(const glm::vec3& point);

    virtual void update(float deltaSec) override;


protected:
    void setupBullet(Bullet* bullet, const glm::vec3& point);


protected:
    float m_bulletSpeed;
    Visuals m_visuals;
    SoundProperties m_fireSound;
};

