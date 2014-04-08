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

    virtual void fireAtPoint(const glm::vec3& point, bool checkFriendlyFire = false);

    virtual void update(float deltaSec) override;

    virtual void setHardpoint(Hardpoint* hardpoint) override;

protected:
    virtual Bullet* createBullet() = 0;
    void setupBullet(Bullet* bullet, const glm::vec3& point);
    bool isBulletPathClear(const glm::vec3& point, bool checkFriendlyFire);
    WorldObject* m_owner;
};

