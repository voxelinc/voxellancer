#pragma once

#include <string>


class Weapon;
class Engine;

class WorldObjectComponentFactory {
public:
    WorldObjectComponentFactory();

    Weapon* weapon(const std::string& name);
    Engine* engine(const std::string& name);


protected:
    void load(const std::string& category, const std::string& name);
};

