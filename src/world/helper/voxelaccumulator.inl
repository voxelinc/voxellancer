#pragma once

#include <algorithm>
#include <set>
#include <iostream>

template<typename Accumulatable>
void VoxelAccumulator<Accumulatable>::clear() {
    m_voxelAccumulatableMap.clear();
    m_accumulatables.clear();
}

template<typename Accumulatable>
void VoxelAccumulator<Accumulatable>::parse(const Accumulatable& accumulatable) {
    typename std::map<const Voxel*, Accumulatable>::iterator i = m_voxelAccumulatableMap.find(accumulatable.voxel());
    if(i == m_voxelAccumulatableMap.end()) {
        m_voxelAccumulatableMap.insert(std::pair<const Voxel*, Accumulatable>(accumulatable.voxel(), accumulatable));
    }
    else {
        i->second.add(accumulatable);
    }
}

template<typename Accumulatable>
void VoxelAccumulator<Accumulatable>::parse(const std::list<Accumulatable> &accumulatables) {
    for(const Accumulatable& accumulatable : accumulatables) {
        parse(accumulatable);
    }
}

template<typename Accumulatable>
void VoxelAccumulator<Accumulatable>::dontAffect(const std::list<Voxel*> voxels) {
    std::set<const Voxel*> dontAffectSet(voxels.begin(), voxels.end());

    for(auto i = m_voxelAccumulatableMap.begin(); i != m_voxelAccumulatableMap.end();) {
        if(dontAffectSet.find(i->first) != dontAffectSet.end()) {
            i = m_voxelAccumulatableMap.erase(i);
        }
        else {
            ++i;
        }
    }
}

template<typename Accumulatable>
std::list<Accumulatable>& VoxelAccumulator<Accumulatable>::accumulatables() {
    m_accumulatables.clear();

    for(auto& pair : m_voxelAccumulatableMap) {
        m_accumulatables.push_back(pair.second);
    }

    return m_accumulatables;
}

