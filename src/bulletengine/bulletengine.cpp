#include "bulletengine.h"

#include "equipment/weapons/worldobjectbullet.h"

#include "bulletenginerenderer.h"
#include "genericinstancedbullet.h"
#include "instancedbulletcontainer.h"
#include "instancedbulletcontainerrenderer.h"


BulletEngine::BulletEngine():
    m_renderer(new BulletEngineRenderer())
{
}

BulletEngine::~BulletEngine() {
    for (InstancedBullet* bullet : m_bullets) {
        delete bullet;
    }
}

BulletEngineRenderer& BulletEngine::renderer() {
    return *m_renderer;
}

void BulletEngine::add(InstancedBullet* bullet) {
    container(bullet->name())->add(bullet);
    m_bullets.insert(bullet);
}

void BulletEngine::remove(InstancedBullet* bullet) {
    assert(bullet->container());
    bullet->container()->remove(bullet);
    m_bullets.erase(bullet);
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
    return new GenericInstancedBullet(container(name)->handle<InstancedBulletContainer>(), name);
}

void BulletEngine::update(float deltaSec) {
    for (InstancedBullet* bullet : m_bullets) {
        bullet->update(deltaSec);
    }

    for (auto& pair : m_containers) {
        pair.second->update(deltaSec);
    }
}

void BulletEngine::draw(const Camera& camera) {
    m_renderer->draw(camera);
}

