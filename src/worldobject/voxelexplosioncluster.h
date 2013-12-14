#pragma once

#include <vector>
#include "worldobject.h"
#include "hardpoint.h"
#include "world/world.h"
#include "world/god.h"

class World;
class God;

class VoxelExplosionCluster : public WorldObject {
public:
    VoxelExplosionCluster(float scale, float lifetime);
    virtual void update(float deltasec);

    virtual void onCollision() override;

protected:
    float m_lifetime;
};
