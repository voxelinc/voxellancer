#include "impactaccumulator.h"

#include <algorithm>
#include <set>
#include <iostream>


void ImpactAccumulator::clear() {
    m_voxelImpactMap.clear();
    m_impacts.clear();
}

void ImpactAccumulator::parse(const std::list<Collision> &collisions) {

}

/* Makes sure every voxel only receives one impact */
void ImpactAccumulator::parse(const std::list<Impact> &impacts) {
    for(const Impact& impact : impacts) {
        std::map<const Voxel*, Impact>::iterator i = m_voxelImpactMap.find(impact.voxel());
        if(i == m_voxelImpactMap.end()) {
            m_voxelImpactMap.insert(std::pair<const Voxel*, Impact>(impact.voxel(), impact));
        }
        else {
            i->second.add(impact);
        }
    }
}

void ImpactAccumulator::dontImpact(const std::list<Voxel*> voxels) {
    std::set<const Voxel*> dontImpactSet(voxels.begin(), voxels.end());

    for(auto i = m_voxelImpactMap.begin(); i != m_voxelImpactMap.end();) {
        if(dontImpactSet.find(i->first) != dontImpactSet.end()) {
            i = m_voxelImpactMap.erase(i);
        }
        else {
            ++i;
        }
    }
}

std::list<Impact>& ImpactAccumulator::impacts() {
    m_impacts.clear();

    for(auto& pair : m_voxelImpactMap) {
        m_impacts.push_back(pair.second);
    }

    return m_impacts;
}
