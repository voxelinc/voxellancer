#include "worldelement.h"

#include <iostream>

#include "scripting/scriptengine.h"

#include "world/world.h"



WorldElement::WorldElement():
    m_world(nullptr)
{

}

WorldElement::~WorldElement() = default;

World* WorldElement::world() {
    return m_world;
}

void WorldElement::setWorld(World* world) {
    m_world = world;
}

bool WorldElement::isAddableToWorld(World* world) const {
    return true;
}

void WorldElement::onAddToWorld() {

}

void WorldElement::onRemovalFromWorld() {
    HandleOwner::invalidate();
}

void WorldElement::registerInWorldComponents() {

}

void WorldElement::deregisterInWorldComponents() {

}

void WorldElement::update(float deltaSec) {

}


