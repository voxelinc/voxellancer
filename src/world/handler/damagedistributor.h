#pragma once

#include "world/helper/damageimpact.h"


class DamageImpact;

class DamageDistributor {
public:
    DamageDistributor(const DamageImpact& damageImpact);
    ~DamageDistributor();

    void distribute();


protected:
    DamageImpact m_damageImpact;
    DamageWave m_damageWave;
};
