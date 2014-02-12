#pragma once

#include "property/property.h"

#include "voxelparticleremovecheck.h"


class VoxelParticleEngine;
struct VoxelParticleData;


/*
    Regular check that de-allocates particledata-locations whose lifetime has passed
    Please note that the shader only draws particles that life, so performing this check
    over a long interval doesn't harm here.
*/
class VoxelParticleExpireCheck: public VoxelParticleRemoveCheck {
public:
    VoxelParticleExpireCheck(VoxelParticleEngine* engine);

    virtual void update(float deltaSec) override;


protected:
    Property<float> m_fullDeadCheckInterval;

    virtual bool check(VoxelParticleData* particleData) override;
    virtual bool isParallel(int checkCount) override;
};

