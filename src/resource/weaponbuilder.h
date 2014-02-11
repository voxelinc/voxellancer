#pragma once

#include <string>


class Weapon;
class GenericGun;
class GenericRocketLauncher;

/*
    Dedicated to load either a GenericGun or GenericRocketLauncher
    from a given property-prefix or - if any is known by that name -
    a special engine that has its own  non-generic implementation
*/
class WeaponBuilder {
public:
    WeaponBuilder(const std::string& name);

    Weapon* build();


protected:
    const std::string& m_name;

    GenericGun* buildGenericGun();
    GenericRocketLauncher* buildGenericRocketLauncher();
};

