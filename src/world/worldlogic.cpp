#include "worldlogic.h"

#include <iostream>

#include "world.h"
#include "god.h"


WorldLogic::WorldLogic(World &world):
    m_world(world)
{

}

void WorldLogic::update(float deltaSecs) {
    m_mover.moveVoxelClusters(deltaSecs);

    m_impactAccumulator.parse(m_mover.collisions());
    //m_impactResolver.alterVelocities(m_impactAccumulator.clusterImpacts());

    damageForwardLoop(m_impactAccumulator.impacts());
    m_impactAccumulator.clear();

    //m_splitDetector.searchOrphans(m_damager.modifiedWorldObjects());
    //m_splitter.split(m_splitDetector.voxelClusterOrphans());
    m_world.god().scheduleSpawns(m_splitter.splitOffVoxelClusters());

//    m_wrecker.detectWreckages(m_damager.modifiedVoxelClusters());
//    //m_wrecker.applyOnWreckageHooks();
//    m_world.god().scheduleRemovals(m_wrecker.wreckages());
//    m_world.god().scheduleSpawns(m_wrecker.recycled());

//    m_garbageCollector.check(m_damager.modifiedVoxelClusters());
    //m_garbageCollector.applyOnGarbageHooks();
//    m_world.god().scheduleRemovals(m_garbageCollector.garbageVoxelClusters());

    m_world.god().remove();
    m_world.god().spawn();
}

void WorldLogic::damageForwardLoop(std::list<Impact> damageImpacts) {
    while(damageImpacts.size() > 0) {
        m_damager.applyDamages(damageImpacts);
        m_damageForwarder.forwardDamage(m_damager.deadlyImpact());
        m_voxelHangman.applyOnDestructionHooks(m_damager.deadlyImpact());
        m_voxelHangman.removeDestroyedVoxels(m_damager.deadlyImpact());
        damageImpacts = m_damageForwarder.forwardedDamageImpacts();
    }
}
