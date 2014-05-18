#pragma once

#include <type_traits>s

#include <glow/ref_ptr.h>

#include "gameobject.h"


template<typename GameObjectType>
class GameObjectManager {
    static_assert(std::is_base_of<GameObjectType, GameObject>::value, "Needs to be derived from GameObject");

public:
    GameObjectManager();
    virtual ~GameObjectManager();

    void addObject(GameObjectType* object);
    std::list<glow::ref_ptr<GameObjectType>> objects();

    void update(float deltaSec);


protected:
    std::list<glow::ref_ptr<GameObjectType>> m_objects;
};


#include "gameobjectmanager.inl"
