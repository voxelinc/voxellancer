#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "equipment/weapon.h"

#include "sound/soundproperties.h"


class Bullet;
class Ray;
class WorldTreeQuery;
class Faction;
class Ship;

class Gun: public Weapon {
public:
    Gun(const std::string& equipmentKey);
    ~Gun();

    float bulletSpeed() const;
    void setBulletSpeed(float bulletSpeed);

    const SoundProperties& fireSound() const;
    void setFireSound(const SoundProperties& fireSound);

    virtual void fireAtPoint(const glm::vec3& point);

    virtual void update(float deltaSec) override;

    virtual void setHardpoint(Hardpoint* hardpoint) override;

    virtual bool isBulletPathClear(const glm::vec3& point, bool checkFriendlyFire = false);

    virtual void setProjectileName(const std::string& name) override;


protected:
    float m_bulletSpeed;
    Visuals m_visuals;
    SoundProperties m_fireSound;

    void setupBullet(Bullet* bullet, const glm::vec3& point);
    WorldObject* m_owner;

    void setBulletExtend();
    float m_spawnDistance;
    float m_bulletLength;
    float m_bulletMaxWidth;
};

