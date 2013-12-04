#pragma once

#include "handler/mover.h"
#include "handler/damageforwarder.h"
#include "handler/damager.h"
#include "handler/impactaccumulator.h"
#include "handler/impactresolver.h"
#include "handler/splitdetector.h"
#include "handler/splitter.h"
#include "handler/garbagecollector.h"
#include "handler/wrecker.h"
#include "handler/voxelhangman.h"


class World;

class WorldLogic
{
public:
    WorldLogic(World &world);
    void update(float deltaSecs);


protected:
    World &m_world;

    Mover m_mover;
    Damager m_damager;
    DamageForwarder m_damageForwarder;
    ImpactAccumulator m_impactAccumulator;
    //ImpactResolver m_impactResolver;
    SplitDetector m_splitDetector;
    Splitter m_splitter;
    //Wrecker m_wrecker;
    GarbageCollector m_garbageCollector;
    VoxelHangman m_voxelHangman;

    void damageForwardLoop(std::list<Impact> damageImpacts);
};

