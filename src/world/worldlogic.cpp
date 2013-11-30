#include "worldlogic.h"

#include "world.h"
#include "god.h"


#include <iostream>


WorldLogic::WorldLogic(World & world):
    m_world(world)
{
    
}




void WorldLogic::update(float deltaSecs) {
    m_mover.moveVoxelClusters(deltaSecs);

    //m_impactAccumulator.parse(m_mover.collisions());
    //m_impactResolver.alterVelocities(m_impactAccumulator.clusterImpacts());

    std::list<VoxelImpact> damageImpacts = m_impactAccumulator.voxelImpacts();
    m_impactAccumulator.clear(); // TODO: Copying the list is UGLY, but the accumulator needs to be cleared at some point..
    while(damageImpacts.size() > 0) {
        m_damager.applyDamages(damageImpacts);
        m_damageForwarder.forwardDamage(m_damager.deadlyVoxelImpacts());
        m_voxelHangman.applyOnDestructionHooks(m_damager.deadlyVoxelImpacts());
        m_voxelHangman.removeDestroyedVoxels(m_damager.deadlyVoxelImpacts());
        damageImpacts = m_damageForwarder.forwardedDamageImpacts();
    }

    m_splitDetector.searchOrphans(m_damager.modifiedVoxelClusters());
    m_splitter.split(m_splitDetector.voxelClusterOrphans());
    m_world.god().scheduleSpawns(m_splitter.splitOffVoxelClusters());

    m_wrecker.detectWreckages(m_damager.modifiedVoxelClusters());
    //m_wrecker.applyOnWreckageHooks();
    m_world.god().scheduleRemovals(m_wrecker.wreckages());
    m_world.god().scheduleSpawns(m_wrecker.recycled());

    m_garbageCollector.check(m_damager.modifiedVoxelClusters());
    //m_garbageCollector.applyOnGarbageHooks();
    m_world.god().scheduleRemovals(m_garbageCollector.garbageVoxelClusters());

    m_world.god().remove();
    m_world.god().spawn();
}
