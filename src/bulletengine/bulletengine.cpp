#include "bulletengine.h"

#include "bulletenginerenderer.h"
#include "genericinstancedbullet.h"


BulletEngine::BulletEngine():
    m_renderer(new BulletEngineRenderer())
{

}

BulletEngine::~BulletEngine() = default;


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

}

void BulletEngine::draw(const Camera& camera) {
    m_renderer->draw(camera);
}

