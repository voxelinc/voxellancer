#pragma once


class Weapon;
class Engine;

class ComponentFactory {
public:
    ComponentFactory();

    Weapon* weapon(const std::string& name);
    Engine* engine(const std::string& name);
};
