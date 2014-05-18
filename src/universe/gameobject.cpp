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
    m_universe = universe;
    m_sector = nullptr;

    doSpawn();
}

void GameObject::spawn(Sector* sector) {
    m_universe = sector->universe();
    m_sector = sector;

    doSpawn();
}

