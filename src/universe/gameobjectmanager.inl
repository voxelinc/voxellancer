#pragma once

template<typename GameObjectType>
GameObjectManager::GameObjectManager() {

}

template<typename GameObjectType>
GameObjectManager::~GameObjectManager() = default;

template<typename GameObjectType>
void GameObjectManager::addObject(GameObjectType* object) {

}

template<typename GameObjectType>
std::list<glow::ref_ptr<GameObjectType>> GameObjectManager::objects() {

}

template<typename GameObjectType>
void GameObjectManager::update(float deltaSec) {
    for (auto& iter = m_objects.begin(); iter != m_objects.end();) {
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

