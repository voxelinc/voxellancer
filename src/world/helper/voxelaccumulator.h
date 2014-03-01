#pragma once

#include <set>
#include <list>
#include <map>

class Voxel;

template<typename Accumulatable>
class VoxelAccumulator
{
public:
    void clear();
    void parse(const Accumulatable& accumulatable);
    void parse(const std::list<Accumulatable>& accumulatables);
    void dontAffect(const std::list<Voxel*>& voxels);

    std::list<Accumulatable>& accumulatables();


protected:
    std::map<const Voxel*, Accumulatable> m_voxelAccumulatableMap;
    std::list<Accumulatable> m_accumulatables;
};

#include "voxelaccumulator.inl"
