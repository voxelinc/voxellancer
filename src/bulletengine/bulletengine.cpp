#include "bulletengine.h"

#include "bulletenginerenderer.h"
#include "genericinstancedbullet.h"


BulletEngine::BulletEngine():
    m_renderer(new BulletEngineRenderer(*this)),
    m_time(0.0f)
{

}

BulletEngine::~BulletEngine() = default;

float BulletEngine::time() const {
    return m_time;
}

void BulletEngine::add(InstancedBullet* bullet) {
    m_renderer->add(bullet);
}

void BulletEngine::remove(InstancedBullet* bullet) {
    m_renderer->remove(bullet);
}

InstancedBullet* BulletEngine::createBullet(const std::string& name) {
    return new GenericInstancedBullet(name);
}

void BulletEngine::update(float deltaSec) {
    m_time += deltaSec;
}

void BulletEngine::draw(const Camera& camera) {
    m_renderer->draw(camera);
}

