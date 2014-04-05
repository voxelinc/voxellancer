#include "bulletenginerenderer.h"

#include "instancedbullet.h"
#include "instancedbulletprototype.h"


BulletEngineRenderer::BulletEngineRenderer() {

}

void BulletEngineRenderer::add(InstancedBullet* bullet) {
    auto iter = m_prototypes.find(bullet->name());

    if (iter == m_prototypes.end()) {
        iter = m_prototypes.emplace(bullet->name(), new InstancedBulletPrototype(bullet->name())).first;
    }

    iter->second->add(bullet);
}

void BulletEngineRenderer::remove(InstancedBullet* bullet) {
    auto iter = m_prototypes.find(bullet->name());
    assert(iter != m_prototypes.end());

    iter->second->remove(bullet);
}

void BulletEngineRenderer::draw(const Camera& camera) {
    for (auto pair : m_prototypes) {
        pair.second->draw(camera);
    }
}

