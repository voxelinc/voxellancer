#include "instancedbulletcontainer.h"

#include <cassert>
#include <iostream>

#include <glow/Program.h>

#include "resource/worldelementbuilder.h"

#include "equipment/weapons/worldobjectbullet.h"

#include "voxel/voxel.h"

#include "instancedbullet.h"
#include "instancedbulletcontainerrenderer.h"


InstancedBulletContainer::InstancedBulletContainer(BulletEngine& engine, const std::string& name):
    m_engine(engine),
    m_name(name),
    m_renderer(new InstancedBulletContainerRenderer(*this))
{
    m_prototype.reset(WorldElementBuilder(m_name).buildWorldObjectBullet());

    for (auto& pair : m_prototype->voxelMap()) {
        m_gridPrototype.push_back(pair.second->data());
    }

    allocateSlots(1);
}

BulletEngine& InstancedBulletContainer::engine() {
    return m_engine;
}

const std::string& InstancedBulletContainer::name() const {
    return m_name;
}

WorldObjectBullet& InstancedBulletContainer::prototype() {
    return *m_prototype;
}

const std::vector<VoxelData>& InstancedBulletContainer::gridPrototype() const {
    return m_gridPrototype;
}

const std::vector<InstancedBulletData>& InstancedBulletContainer::bulletData() const {
    return m_bulletData;
}

void InstancedBulletContainer::add(InstancedBullet* bullet) {
    assert(this == bullet->container());

    m_bullets.insert(bullet);

    if (m_freeSlots.empty()) {
        allocateSlots(m_bullets.size() * 2);
    }

    int slot = m_freeSlots.top();
    m_freeSlots.pop();

    bullet->setBufferSlot(slot);
    m_bulletData[slot] = *bullet->data();

    invalidateSlot(slot);
}

void InstancedBulletContainer::remove(InstancedBullet* bullet) {
    assert(this == bullet->container());

    m_bullets.erase(bullet);

    int slot = bullet->bufferSlot();
    m_freeSlots.push(slot);
    m_bulletData[slot].active = false;

    invalidateSlot(slot);
}

void InstancedBulletContainer::update(float deltaSec) {
    for (InstancedBullet* bullet : m_bullets) {
        if (bullet->dataChanged()) {
            m_bulletData[bullet->bufferSlot()] = *bullet->data();
            invalidateSlot(bullet->bufferSlot());
            bullet->setDataChanged(false);
        }
    }
}

void InstancedBulletContainer::draw(glow::Program* program) {
    program->setUniform("scale", m_prototype->transform().scale());
    m_renderer->draw();
}

void InstancedBulletContainer::allocateSlots(int slotCount) {
    assert(slotCount >= m_bullets.size());

    for (int i = m_bullets.size(); i < slotCount; i++) {
        m_freeSlots.push(i);
    }

    m_bulletData.resize(slotCount);
}

void InstancedBulletContainer::invalidateSlot(int slot) {
    m_renderer->invalidateSlot(slot);
}

