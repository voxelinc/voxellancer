#include "instancedbulletprototype.h"


InstancedBulletPrototype::InstancedBulletPrototype(const std::string& name):
    m_initialized(false)
{
}

void InstancedBulletPrototype::add(InstancedBullet* bullet) {

}

void InstancedBulletPrototype::remove(InstancedBullet* bullet) {

}

void InstancedBulletPrototype::draw(const Camera& camera) {

}

void InstancedBulletPrototype::initialize() {

    m_initialized = true;
}

