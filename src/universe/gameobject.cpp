#include "gameobject.h"

#include "sector.h"


GameObject::GameObject():
    m_universe(nullptr),
    m_sector(nullptr),
    m_state(GameObjectState::Created)
{
}

GameObject::~GameObject() = default;

Universe* GameObject::universe() const {
    return m_universe;
}

Sector* GameObject::sector() const {
    return m_sector;
}

GameObjectState GameObject::gameObjectState() const {
    return m_state;
}

void GameObject::update(float deltaSecs) {

}

bool GameObject::canSpawn(Universe& universe) const {
    return doCanSpawn(universe, nullptr);
}

bool GameObject::canSpawn(Sector& sector) const {
    return doCanSpawn(sector.universe(), &sector);
}

void GameObject::spawn(Universe& universe) {
    m_universe = &universe;
    m_sector = nullptr;

    doSpawn();

    m_state = GameObjectState::Spawned;
}

void GameObject::spawn(Sector& sector) {
    m_universe = &sector.universe();
    m_sector = &sector;

    doSpawn();

    m_state = GameObjectState::Spawned;
}

void GameObject::unspawn() {
    doUnspawn();
    m_state = GameObjectState::Unspawned;
}

void GameObject::warp(Sector& sector) {
    doWarp(sector);
}

bool GameObject::doCanSpawn(Universe& universe, Sector* sector) const {
    return false;
}

