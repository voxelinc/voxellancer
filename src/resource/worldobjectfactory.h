#pragma once

#include <string>


class Ship;
class WorldObject;

/*
    To generate worldobjects by name and equip them with engines and weapons
*/
class WorldObjectFactory {
public:
    WorldObjectFactory();

    template<typename T>
    T* build(const std::string& name);

    void equipSomehow(WorldObject* worldObject);


protected:
    WorldObject* m_worldObject;
    std::string m_name;
};

#include "worldobjectfactory.inl"
