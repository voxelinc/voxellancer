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

void WorldElement::update(float deltaSec) {

}


