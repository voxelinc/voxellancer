#pragma once

template<typename GameObjectType>
GameObjectManager<GameObjectType>::GameObjectManager() {

}

template<typename GameObjectType>
GameObjectManager<GameObjectType>::~GameObjectManager() = default;

template<typename GameObjectType>
void GameObjectManager<GameObjectType>::addObject(GameObjectType* object) {
    m_objects.push_back(object);
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
            iter = m_objects.erase(iter);
        } else {
            ++iter;
        }
    }
}

