#pragma once

#include "property/property.h"

#include "voxelparticleremovecheck.h"

#include "geometry/sphere.h"

class Player;
class VoxelParticleEngine;
struct VoxelParticleData;


/*
    Regular check that removes particles that intersect with WorldObjects
*/
class VoxelParticleIntersectionCheck: public VoxelParticleRemoveCheck {
public:
    VoxelParticleIntersectionCheck(const VoxelParticleEngine& engine);

    virtual bool isDead(const VoxelParticleData& particle) override;

    virtual void setPlayer(Player& player) override;

protected:
    const VoxelParticleEngine& m_particleEngine;
    Player* m_player;
    Sphere m_Sphere;
    Property<float> m_maxCheckDistance;

    virtual void beforeCheck();

};

