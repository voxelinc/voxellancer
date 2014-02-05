#pragma once

#include <string>
#include <stdint.h>

#include "property/property.h"

#include "utils/genericentity.h"

#include "worldobject/components/weapon.h"


class GenericWeapon: virtual public Weapon, public GenericEntity {
public:
    GenericWeapon(WeaponType type, const std::string& propertyPrefix);

    virtual Visuals visuals() const override;
    virtual float cooldownTime() const override;


protected:
    Property<float> m_cooldownTime;
    Property<uint32_t> m_color;
    Property<float> m_emissiveness;
};

