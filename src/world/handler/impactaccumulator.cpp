#include "impactaccumulator.h"

#include <algorithm>
#include <set>
#include <iostream>

#include "worldobject/worldobject.h"

void ImpactAccumulator::clear() {
    m_voxelImpactMap.clear();
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

//void ImpactAccumulator::parse(const std::list<PhysicalVoxelImpact> &physicalVoxelImpact) {
//
//}

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

//std::list<PhysicalVoxelClusterImpact> &ImpactAccumulator::clusterImpacts() {
//    return m_clusterImpacts;
//}

std::list<Impact> ImpactAccumulator::impacts() {
    std::list<Impact> impacts;

    for(auto& pair : m_voxelImpactMap) {
        impacts.push_back(pair.second);
    }

    return impacts;
}

void ImpactAccumulator::applyOnImpactHooks(){
    std::set<WorldObject*> objects;
    for (auto& pair : m_voxelImpactMap) {
        objects.insert(pair.second.worldObject());
    }
    for (WorldObject* object : objects) {
        object->onImpact();
    }
}