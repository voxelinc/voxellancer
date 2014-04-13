#include "worldelement.h"

#include <iostream>

#include "scripting/scriptengine.h"

#include "world/world.h"


WorldElement::WorldElement(World* world):
    m_world(nullptr),
    m_parent(nullptr)
{
    if (world) {
        world->addElement(this);
    }
}

WorldElement::WorldElement(WorldElement* parent):
    WorldElement(parent->world())
{
    if (world()) {
        parent->addChild(this);
    }
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
    for (auto child : m_children) {
        m_world->removeElement(child);
    }
    m_children.clear();

    if (m_parent) {
        m_parent->removeChild(this);
    }
    m_parent = nullptr;

    HandleOwner::invalidate();
}

void WorldElement::registerInWorldComponents() {

}

void WorldElement::deregisterInWorldComponents() {

}

std::list<WorldElement*> WorldElement::children() const {
    std::list<WorldElement*> result;
    for (auto child : m_children) {
        result.push_back(child);
    }

    return result;
}

void WorldElement::addChild(WorldElement* child) { std::cout << "Adding child " << child << std::endl;
    m_children.push_back(child);
}

void WorldElement::removeChild(WorldElement* child) {std::cout << "Removing child " << child << std::endl;
    m_children.remove(child);
}

void WorldElement::update(float deltaSec) {

}


