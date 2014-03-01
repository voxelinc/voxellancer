#pragma once

class Player;
struct VoxelParticleData;

class VoxelParticleRemoveCheck {
public:
    virtual bool isDead(const VoxelParticleData& particle) = 0;
    virtual void setPlayer(const Player& player);
};