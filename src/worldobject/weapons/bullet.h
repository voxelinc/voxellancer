#pragma once

#include "worldobject/worldobject.h"
#include "resource/clustercache.h"


class Bullet : public WorldObject {

public:
    Bullet(WorldObject* creator, glm::vec3 position, glm::quat orientation, glm::vec3 direction, float speed, float range);

    WorldObject* creator() const;

    virtual bool specialIsCollideableWith(const CollisionFilterable* other) const override;

    virtual void update(float delta_sec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


private:
    WorldObject *m_creator;
	float m_lifetime;
};

