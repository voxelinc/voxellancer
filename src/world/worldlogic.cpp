#include "worldlogic.h"

#include <iostream>

#include "utils/tostring.h"

#include "world.h"
#include "god.h"
#include "glow/AutoTimer.h"


WorldLogic::WorldLogic(World &world):
    m_world(world)
{

}

void WorldLogic::update(float deltaSecs) {
    m_mover.moveWorldObjects(deltaSecs);

    m_voxelCollisionAccumulator.parse(m_mover.voxelCollisions());

    m_damageImpactGenerator.parse(m_voxelCollisionAccumulator.worldObjectCollisions());
    m_elasticImpulseGenerator.parse(m_voxelCollisionAccumulator.worldObjectCollisions());

    m_elasticImpulsor.parse(m_elasticImpulseGenerator.worldObjectImpulses());
    damageForwardLoop(m_damageImpactGenerator.damageImpacts());

    m_splitDetector.searchSplitOffs(m_damager.worldObjectModifications());
    m_splitter.split(m_splitDetector.worldObjectSplits());

    m_boundsShrinker.shrink(m_damager.worldObjectModifications());

    m_world.god().scheduleSpawns(m_splitter.splitOffWorldObjects());

//    m_wrecker.detectWreckages(m_damager.modifiedVoxelClusters());
//    //m_wrecker.applyOnWreckageHooks();
//    m_world.god().scheduleRemovals(m_wrecker.wreckages());
//    m_world.god().scheduleSpawns(m_wrecker.recycled());

    m_garbageCollector.check(m_world.worldObjects()/*m_damager.modifiedVoxelClusters()*/);
    //m_garbageCollector.applyOnGarbageHooks();
    m_world.god().scheduleRemovals(m_garbageCollector.garbageVoxelClusters());

    m_world.god().remove();
    m_world.god().spawn();
}

 DamageForwarder &WorldLogic::damageForwarder() {
    return m_damageForwarder;
 }

void WorldLogic::damageForwardLoop(std::list<DamageImpact> damageImpacts) {
    m_damager.reset();

    if(damageImpacts.empty()) {
        return;
    }



    while(damageImpacts.size() > 0) {
        m_damager.applyDamages(damageImpacts);

        m_damageForwarder.forwardDamageImpacts(m_damager.deadlyDamageImpacts());
        m_damageForwarder.dontForwardTo(m_damager.deadVoxels());

        m_voxelHangman.applyOnDestructionHooks(m_damager.deadlyDamageImpacts());
        m_voxelHangman.removeDestroyedVoxels(m_damager.deadlyDamageImpacts());

        damageImpacts = m_damageForwarder.forwardedDamageImpacts();
    }
}

