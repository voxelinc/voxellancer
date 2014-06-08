#include "gameobject.h"

#include "sector.h"


GameObject::GameObject():
    m_universe(nullptr),
    m_sector(nullptr),
    m_spawnState(GameObjectSpawnState::Created)
{
}

GameObject::~GameObject() = default;

Universe* GameObject::universe() const {
    return m_universe;
}

Sector* GameObject::sector() const {
    return m_sector;
}

GameObjectSpawnState GameObject::spawnState() const {
    return m_spawnState;
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

    m_spawnState = GameObjectSpawnState::Spawned;
}

void GameObject::spawn(Sector& sector) {
    m_universe = &sector.universe();
    m_sector = &sector;

    doSpawn();

    m_spawnState = GameObjectSpawnState::Spawned;
}

void GameObject::unspawn() {
    doUnspawn();
    m_spawnState = GameObjectSpawnState::Unspawned;
}

void GameObject::warp(Sector& sector) {
    doWarp(sector);
}

bool GameObject::doCanSpawn(Universe& universe, Sector* sector) const {
    return false;
}

