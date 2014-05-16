#include "impulseaccumulator.h"

#include <algorithm>
#include <set>

#include "worldobject/worldobject.h"


void ImpulseAccumulator::clear() {
    m_voxelImpulseMap.clear();
    m_impulses.clear();
}

/*
 * Makes sure every voxel only receives one impulse
 */
void ImpulseAccumulator::parse(const std::list<Impulse> &impulses) {
    for(const Impulse& impulse : impulses) {
        std::map<const Voxel*, Impulse>::iterator i = m_voxelImpulseMap.find(impulse.voxel());
        if(i == m_voxelImpulseMap.end()) {
            m_voxelImpulseMap.insert(std::pair<const Voxel*, Impulse>(impulse.voxel(), impulse));
        }
        else {
            i->second.add(impulse);
        }
    }
}

void ImpulseAccumulator::dontImpulse(const std::list<Voxel*>& voxels) {
    std::set<const Voxel*> dontImpulseSet(voxels.begin(), voxels.end());

    for(auto i = m_voxelImpulseMap.begin(); i != m_voxelImpulseMap.end();) {
        if(dontImpulseSet.find(i->first) != dontImpulseSet.end()) {
            i = m_voxelImpulseMap.erase(i);
        }
        else {
            ++i;
        }
    }
}

std::list<Impulse>& ImpulseAccumulator::impulses() {
    m_impulses.clear();

    for(auto& pair : m_voxelImpulseMap) {
        m_impulses.push_back(pair.second);
    }

    return m_impulses;
}
