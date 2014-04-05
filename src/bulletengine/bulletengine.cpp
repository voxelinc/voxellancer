#include "bulletengine.h"

#include "genericinstancedbullet.h"


BulletEngine::BulletEngine()
{

}

BulletEngine::~BulletEngine() = default;

InstancedBullet* BulletEngine::createBullet(const std::string& name) {
    return new GenericInstancedBullet();
}

void BulletEngine::update(float deltaSec) {

}

void BulletEngine::draw(const Camera& camera) {

}

