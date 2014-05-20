#pragma once

#include <type_traits>

#include <glow/ref_ptr.h>

#include "gameobject.h"


class Universe;

template<typename GameObjectType>
class GameObjectManager {
    static_assert(std::is_base_of<GameObject, GameObjectType>::value, "Needs to be derived from GameObject");

public:
    GameObjectManager(Universe& universe);
    virtual ~GameObjectManager();

    void addObject(GameObjectType* object);
    std::list<glow::ref_ptr<GameObjectType>>& objects();

    void update(float deltaSec);


protected:
    Universe& m_universe;
    std::list<glow::ref_ptr<GameObjectType>> m_objects;

    virtual void onObjectAddtition(GameObjectType* object);
    virtual void onObjectRemoval(GameObjectType* object);
};


#include "gameobjectmanager.inl"
