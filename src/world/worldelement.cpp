#include "worldelement.h"

#include <iostream>

#include "scripting/scriptengine.h"

#include "world/world.h"



WorldElement::WorldElement():
    m_world(nullptr),
    m_alive(true)
{

}

WorldElement::~WorldElement() = default;

World* WorldElement::world() {
    return m_world;
}

void WorldElement::setWorld(World* world) {
    m_world = world;
}

bool WorldElement::alive() const {
    return m_alive;
}

void WorldElement::kill() {
    m_alive = false;
}

void WorldElement::update(float deltaSec) {

}


