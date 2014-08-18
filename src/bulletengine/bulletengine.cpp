#include "bulletengine.h"

#include <iostream>

#include "equipment/weapons/worldobjectbullet.h"

#include "bulletenginerenderer.h"
#include "instancedbullet.h"
#include "instancedbulletcontainer.h"
#include "instancedbulletcontainerrenderer.h"


BulletEngine::BulletEngine():
    m_renderer(new BulletEngineRenderer())
{
}

BulletEngine::~BulletEngine() = default;

BulletEngineRenderer& BulletEngine::renderer() {
    return *m_renderer;
}

void BulletEngine::add(InstancedBullet* bullet) {
    container(bullet->name())->add(bullet);
    m_bullets.insert(std::unique_ptr<InstancedBullet>(bullet));
}

InstancedBulletContainer* BulletEngine::container(const std::string& name) {
    auto iter = m_containers.find(name);
    if (iter == m_containers.end()) {
        iter = m_containers.emplace(name, std::unique_ptr<InstancedBulletContainer>(new InstancedBulletContainer(*this, name))).first;
        m_renderer->add(iter->second.get());
    }
    return iter->second.get();
}

InstancedBullet* BulletEngine::createBullet(const std::string& name) {
    return new InstancedBullet(container(name)->handle<InstancedBulletContainer>(), name);
}

void BulletEngine::update(float deltaSec) {
    for (auto iter = m_bullets.begin(); iter != m_bullets.end();) {
        InstancedBullet* bullet = iter->get();

        bullet->update(deltaSec);
        if (bullet->alive()) {
            ++iter;
        } else {
            bullet->container()->remove(bullet);
            iter = m_bullets.erase(iter);
        }
    }

    for (auto& pair : m_containers) {
        pair.second->update(deltaSec);
    }
}

void BulletEngine::draw(const Camera& camera) {
    m_renderer->draw(camera);
}

