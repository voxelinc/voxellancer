#pragma once

#include <glm/glm.hpp>

#include "display/rendering/visuals.h"

#include "equipment/weapon.h"

#include "sound/soundproperties.h"


class Bullet;

class Gun: public Weapon {
public:
    Gun(const std::string& equipmentKey);

    float bulletLifetime() const;
    void setBulletLifetime(float bulletLifetime);

    float bulletSpeed() const;
    void setBulletSpeed(float bulletSpeed);

    const Visuals& visuals() const;
    void setVisuals(const Visuals& visuals);

    const SoundProperties& fireSound() const;
    void setFireSound(const SoundProperties& fireSound);

    float cooldownTime() const;
    void setCooldownTime(float cooldownTime);

    const std::string& bulletName() const;
    void setBulletName(const std::string& bulletName);

    virtual void fireAtPoint(const glm::vec3& point);

    virtual void update(float deltaSec) override;


protected:
    void setupBullet(Bullet* bullet, const glm::vec3& point);


protected:
    float m_bulletSpeed;
    float m_bulletLifetime;
    float m_cooldownTime;
    Visuals m_visuals;
    SoundProperties m_fireSound;
    std::string m_bulletName;
};

