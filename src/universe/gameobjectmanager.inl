#pragma once

#include <algorithm>

#include "scripting/scriptengine.h"

#include "universe/universe.h"


template<typename GameObjectType>
GameObjectManager<GameObjectType>::GameObjectManager(Universe& universe):
    m_universe(universe)
{
}

template<typename GameObjectType>
GameObjectManager<GameObjectType>::~GameObjectManager() = default;

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::addObject(GameObjectType* object) {
    m_objects.push_back(object);
    m_universe.scriptEngine().registerScriptable(object);
    onObjectAddtition(object);
}

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::removeObject(GameObjectType* object) {
    m_removals.push_back(object);
    m_universe.scriptEngine().unregisterScriptable(object);
    onObjectRemoval(object);
}

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::foreachObject(const std::function<void(glow::ref_ptr<GameObjectType>& object)>& function) {
    for (glow::ref_ptr<GameObjectType>& object : m_objects) {
        if (std::find(m_removals.begin(), m_removals.end(), object) == m_removals.end()) {
            function(object);
        }
    }
}

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::update(float deltaSec) {
    foreachObject([&] (glow::ref_ptr<GameObjectType>& object) {
        object->update(deltaSec);
    });

    for (glow::ref_ptr<GameObjectType>& object : m_removals) {
        m_objects.remove(object);
    }
    m_removals.clear();
}

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::onObjectAddtition(GameObjectType* object) {

}

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::onObjectRemoval(GameObjectType* object) {

}

