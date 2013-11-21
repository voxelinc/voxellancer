#pragma once


class ImpactForwarder
{
public:
    ImpactForwarder(ImpactAccumulator &impactAccumulator);

    void scheduleForwardedImpacts(std::list<VoxelImpact*> &deadlyVoxelImpacts);

};

