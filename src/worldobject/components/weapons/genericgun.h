#pragma once

#include <string>

#include "property/property.h"

#include "utils/genericentity.h"

#include "gun.h"


class GenericGun: public Gun, public GenericEntity {
public:
    GenericGun(const std::string& propertyPrefix);

    virtual float cooldownTime() const override;
    virtual float bulletLifetime() const override;
    virtual float bulletSpeed() const override;


protected:
    Property<float> m_cooldownTime;
    Property<float> m_bulletSpeed;
    Property<float> m_bulletLifetime;
    Property<std::string> m_bulletName;

    virtual Bullet* createBullet() override;
};

