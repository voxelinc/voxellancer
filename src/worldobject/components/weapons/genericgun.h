#pragma once

#include <string>

#include "property/property.h"

#include "utils/genericentity.h"

#include "genericweapon.h"
#include "gun.h"


class GenericGun: public GenericWeapon, public Gun {
public:
    GenericGun(const std::string& propertyPrefix);

    virtual float bulletLifetime() const override;
    virtual float bulletSpeed() const override;


protected:
    Property<float> m_bulletSpeed;
    Property<float> m_bulletLifetime;
    Property<std::string> m_bulletName;

    virtual Bullet* createBullet() override;
};

