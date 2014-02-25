#pragma once

#include <memory>
#include <string>

#include "display/rendering/visuals.h"

#include "bullet.h"
#include "gun.h"



class GenericGun: public Gun {
public:
    GenericGun(const std::string& name);

    virtual float bulletLifetime() const override;
    void setBulletLifetime(float bulletLifetime);

    virtual float bulletSpeed() const override;
    void setBulletSpeed(float bulletSpeed);

    virtual Visuals visuals() const override;
    void setVisuals(const Visuals& visuals);

    virtual float cooldownTime() const override;
    void setCooldownTime(float cooldownTime);

    const std::string& bulletName() const;
    void setBulletName(const std::string& bulletName);


protected:
    float m_bulletSpeed;
    float m_bulletLifetime;
    float m_cooldownTime;
    Visuals m_visuals;
    std::string m_bulletName;

    virtual Bullet* createBullet() override;
};

