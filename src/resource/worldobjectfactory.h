#pragma once

#include <string>


class Ship;

class WorldObjectFactory {
public:
    WorldObjectFactory();

    template<typename T>
    T* build(const std::string& name);


protected:
    WorldObject* m_worldObject;
};

#include "worldobjectfactory.inl"
