#pragma once

#include "mover.h"
#include "damageforwarder.h"
#include "damager.h"
#include "impactaccumulator.h"
#include "impactresolver.h"
#include "splitdetector.h"
#include "splitter.h"
#include "garbagecollector.h"
#include "wrecker.h"
#include "voxelhangman.h"


class WorldLogic
{
public:
    void update(float deltaSecs);


protected:
    Mover m_mover;
    Damager m_damager;
    DamageForwarder m_damageForwarder;
    ImpactAccumulator m_impactAccumulator;
    ImpactResolver m_impactResolver;
    SplitDetector m_splitDetector;
    Splitter m_splitter;
    Wrecker m_wrecker;
    GarbageCollector m_garbageCollector;
    VoxelHangman m_voxelHangman;
};

