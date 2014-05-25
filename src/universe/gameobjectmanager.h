#pragma once

#include <list>
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
    void removeObject(GameObjectType* object);

    void foreachObject(const std::function<void(glow::ref_ptr<GameObjectType>& object)>& function);

    void update(float deltaSec);


protected:
    Universe& m_universe;

    std::list<glow::ref_ptr<GameObjectType>> m_objects;
    std::list<glow::ref_ptr<GameObjectType>> m_removals;

    virtual void onObjectAddtition(GameObjectType* object);
    virtual void onObjectRemoval(GameObjectType* object);
};


#include "gameobjectmanager.inl"
