#include "genericweapon.h"


GenericWeapon::GenericWeapon(WeaponType type, const std::string& propertyPrefix):
    Weapon(type, propertyPrefix),
    GenericEntity(propertyPrefix),
    m_cooldownTime(propertyPrefix + ".general.cooldownTime"),
    m_color(propertyPrefix + ".visuals.color"),
    m_emissiveness(propertyPrefix + ".visuals.emissiveness")
{

}

Visuals GenericWeapon::visuals() const {
    return Visuals(
        m_color,
        m_emissiveness
    );
}

float GenericWeapon::cooldownTime() const {
    return m_cooldownTime;
}
