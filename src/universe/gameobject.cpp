#include "gameobject.h"

#include "sector.h"


GameObject::GameObject():
    m_universe(nullptr),
    m_sector(nullptr)
{
}

GameObject::~GameObject() = default;

Universe* GameObject::universe() const {
    return m_universe;
}

Sector* GameObject::sector() const {
    return m_sector;
}

void GameObject::update(float deltaSecs) {

}

bool GameObject::canSpawnFail() const {
    return doCanSpawnFail();
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
}

void GameObject::spawn(Sector& sector) {
    m_universe = &sector.universe();
    m_sector = &sector;

    doSpawn();
}

void GameObject::unspawn() {
    doUnspawn();
}

void GameObject::warp(Sector& sector) {
    doWarp(sector);
}

bool GameObject::doCanSpawnFail() const {
    return false;
}

bool GameObject::doCanSpawn(Universe& universe, Sector* sector) const {
    return false;
}

