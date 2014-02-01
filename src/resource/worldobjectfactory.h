#pragma once

#include <string>


class Ship;
class WorldObject;

class WorldObjectFactory {
public:
    WorldObjectFactory();

    template<typename T>
    T* build(const std::string& name);


protected:
    WorldObject* m_worldObject;
    std::string m_name;

    void setupHardpoints();
    void setupEngineSlots();
};

#include "worldobjectfactory.inl"
