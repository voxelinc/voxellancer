#include "damageforwarder.h"

void DamageForwarder::forwardDamage(std::list<VoxelImpact> &deadlyVoxelImpacts) {
    m_forwardedDamageImpacts.clear();
}

std::list<VoxelImpact> &DamageForwarder::forwardedDamageImpacts() {
    return m_forwardedDamageImpacts;
}
