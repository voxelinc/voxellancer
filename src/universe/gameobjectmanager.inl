#pragma once

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
std::list<glow::ref_ptr<GameObjectType>>& GameObjectManager<GameObjectType>::objects() {
    return m_objects;
}

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::update(float deltaSec) {
    for (auto iter = m_objects.begin(); iter != m_objects.end();) {
        GameObjectType* object = *iter;

        if (!object->removalScheduled()) {
            object->update(deltaSec);
        }

        if (object->removalScheduled()) {
            m_universe.scriptEngine().unregisterScriptable(object);
            onObjectRemoval(object);
            iter = m_objects.erase(iter);
        } else {
            ++iter;
        }
    }
}

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::onObjectAddtition(GameObjectType* object) {

}

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::onObjectRemoval(GameObjectType* object) {

}

