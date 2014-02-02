#pragma once

#include <string>


class Weapon;
class Engine;

class WorldObjectEquipmentFactory {
public:
    WorldObjectEquipmentFactory();

    Weapon* weapon(const std::string& name);
    Engine* engine(const std::string& name);


protected:
    void load(const std::string& category, const std::string& name);
};

