#pragma once

#include <list>

#include "handler/mover.h"
#include "handler/damageforwarder.h"
#include "handler/damager.h"
#include "handler/voxelcollisionaccumulator.h"
#include "handler/damageimpactgenerator.h"
#include "handler/elasticimpulsegenerator.h"
#include "handler/splitter.h"
#include "handler/garbagecollector.h"
#include "handler/wrecker.h"
#include "handler/elasticimpulsor.h"
#include "handler/voxelhangman.h"
#include "handler/splitdetector.h"


class World;

class WorldLogic {
public:
    WorldLogic(World &world);

    void addDamageImpact(const DamageImpact& damageImpact);

    void update(float deltaSecs);

    DamageForwarder &damageForwarder();


protected:
    World &m_world;
    std::list<DamageImpact> m_damageImpacts;

    Mover m_mover;
    VoxelCollisionAccumulator m_voxelCollisionAccumulator;
    ElasticImpulseGenerator m_elasticImpulseGenerator;
    ElasticImpulsor m_elasticImpulsor;
    Damager m_damager;
    DamageForwarder m_damageForwarder;
    DamageImpactGenerator m_damageImpactGenerator;
    SplitDetector m_splitDetector;
    Splitter m_splitter;
    Wrecker m_wrecker;
    GarbageCollector m_garbageCollector;
    VoxelHangman m_voxelHangman;

    void damageForwardLoop(std::list<DamageImpact> damageImpulses);
};

