#pragma once

#include "handler/mover.h"
#include "handler/damageforwarder.h"
#include "handler/damager.h"
#include "handler/voxelcollisionaccumulator.h"
#include "handler/damageimpactgenerator.h"
#include "handler/elasticimpactgenerator.h"
#include "handler/splitdetector.h"
#include "handler/splitter.h"
#include "handler/garbagecollector.h"
#include "handler/wrecker.h"
#include "handler/elasticimpactor.h"
#include "handler/voxelhangman.h"



class World;

class WorldLogic
{
public:
    WorldLogic(World &world);

    void update(float deltaSecs);

    DamageForwarder &damageForwarder();


protected:
    World &m_world;

    Mover m_mover;
    VoxelCollisionAccumulator m_voxelCollisionAccumulator;
    DamageImpactGenerator m_damageImpactGenerator;
    ElasticImpactGenerator m_elasticImpactGenerator;
    ElasticImpactor m_elasticImpactor;
    Damager m_damager;
    DamageForwarder m_damageForwarder;
    SplitDetector m_splitDetector;
    Splitter m_splitter;
    //Wrecker m_wrecker;
    GarbageCollector m_garbageCollector;
    VoxelHangman m_voxelHangman;

    void damageForwardLoop(std::list<Impact> damageImpacts);
};

