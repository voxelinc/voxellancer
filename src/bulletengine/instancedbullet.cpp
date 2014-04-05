#include "instancedbullet.h"

#include "bulletengine/bulletengine.h"

#include "world/world.h"


InstancedBullet::InstancedBullet(const std::string& name):
    m_name(name)
{
}

const std::string& InstancedBullet::name() const {
    return m_name;
}

Transform& InstancedBullet::transform() {

}

void InstancedBullet::setTransform(const Transform& transform) {

}

void InstancedBullet::setSpeed(const Speed& speed) {

}

void InstancedBullet::update(float deltaSec) {

}

void InstancedBullet::spawn() {
    World::instance()->bulletEngine().add(this);
}

void InstancedBullet::remove() {
    World::instance()->bulletEngine().remove(this);
}

float InstancedBullet::length() {

}

