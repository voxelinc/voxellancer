#pragma once

#include "property/property.h"

#include "voxelparticleremovecheck.h"

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

    virtual void setPlayer(const Player& player) override;

protected:
    const VoxelParticleEngine& m_particleEngine;
    const Player* m_player;
    Property<float> m_maxCheckDistance;

};

