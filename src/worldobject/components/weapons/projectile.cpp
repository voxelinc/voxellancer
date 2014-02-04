#include "projectile.h"

#include "world/god.h"
#include "world/world.h"


Projectile::Projectile():
    m_creator(nullptr),
    m_lifetime(0.0f)
{
}

WorldObject* Projectile::creator() {
    return m_creator;
}

void Projectile::setCreator(WorldObject* creator) {
    m_creator = creator;
}

float Projectile::lifetime() const {
    return m_lifetime;
}

void Projectile::setLifetime(float lifetime) {
    m_lifetime = lifetime;
}

bool Projectile::specialIsCollideableWith(const CollisionFilterable* other) const {
    return static_cast<CollisionFilterable*>(m_creator) != other;
}

void Projectile::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_lifetime -= deltaSec;

    if (m_lifetime <= 0.0f) {
        World::instance()->god().scheduleRemoval(this);
    }
}

