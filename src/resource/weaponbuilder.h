#pragma once

#include <string>


class Gun;
class RocketLauncher;
class Weapon;

/*
    Dedicated to load either a Gun or GenericRocketLauncher
    from a given property-prefix or - if any is known by that name -
    a special engine that has its own  non-generic implementation
*/
class WeaponBuilder {
public:
    WeaponBuilder(const std::string& name);

    Weapon* build();

    Gun* buildGun();
    RocketLauncher* buildRocketLauncher();


protected:
    const std::string& m_name;
};

