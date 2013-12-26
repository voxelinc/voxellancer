#pragma once

#include <vector>
#include "worldobject/worldobject.h"
#include "worldobject/hardpoint.h"
#include "world/world.h"
#include "world/god.h"

class World;
class God;

class VoxelEffectParticle : public WorldObject {
public:
    VoxelEffectParticle(float scale, float lifetime);
    virtual void update(float deltasec);

    virtual void onCollision() override;

protected:
    float m_lifetime;
};
