#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "equipment/weapon.h"


class SoundProperties;
class Bullet;
class Ray;
class WorldTreeQuery;
class Faction;
class Ship;

class Gun: public Weapon {
public:
    Gun(const std::string& equipmentKey);
    ~Gun();

    virtual const SoundProperties& fireSound() const = 0;

    virtual float bulletLifetime() const = 0;
    virtual float bulletSpeed() const = 0;

    virtual void fireAtPoint(const glm::vec3& point);

    virtual void update(float deltaSec) override;

    virtual void setHardpoint(Hardpoint* hardpoint) override;

    virtual bool isBulletPathClear(const glm::vec3& point, bool checkFriendlyFire = false);


protected:
    virtual Bullet* createBullet() = 0;
    void setupBullet(Bullet* bullet, const glm::vec3& point);
    WorldObject* m_owner;

    Bullet* m_bulletPrototype;
    float m_spawnDistance;
    float m_bulletLength;
    float m_bulletMaxWidth;
};

