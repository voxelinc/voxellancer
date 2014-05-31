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
    virtual ~Gun();

    float bulletSpeed() const;
    void setBulletSpeed(float bulletSpeed);

    float bulletLifetime() const;

    const SoundProperties& fireSound() const;
    void setFireSound(const SoundProperties& fireSound);

    virtual void fireAtPoint(const glm::vec3& point, bool checkFriendlyFire);
    virtual bool isBulletPathClear(const glm::vec3& point, bool checkFriendlyFire);

    virtual void update(float deltaSec) override;


protected:
    float m_bulletSpeed;
    Visuals m_visuals;
    SoundProperties m_fireSound;

    WorldObject* m_owner;

    float m_spawnDistance;
    float m_bulletLength;
    float m_bulletCapsuleRadius;
    float m_bulletLifetime;


    void setupBullet(Bullet* bullet, const glm::vec3& point);
    void setBulletExtend();
    virtual void onProjectileNameChanged() override;
};

