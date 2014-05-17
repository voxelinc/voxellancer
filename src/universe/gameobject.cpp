#include "gameobject.h"


GameObject::GameObject():
    m_universe(nullptr),
    m_sector(nullptr)
    m_removalScheduled(false)
{
}

GameObject::~GameObject() = default;

Universe* GameObject::universe() {
    return m_universe;
}

Sector* GameObject::sector() {
    return m_sector;
}

bool GameObject::removalScheduled() const {
    return m_removalScheduled
}

void GameObject::scheduleRemoval() {
    m_removalScheduled = true;
}

void GameObject::update(float deltaSecs) {

}

void GameObject::spawn(Universe* universe) {
    doSpawn(universe, nullptr);
}

void GameObject::spawn(Sector* sector) {
    doSpawn(sector->universe(), sector);
}

