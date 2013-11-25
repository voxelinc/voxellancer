#include "worldlogic.h"

#include "world.h"

#include <iostream>


void WorldLogic::update() {
    m_mover.moveVoxelClusters();

    m_impactAccumulator.parse(m_mover.collisions());
    m_impactResolver.alterVelocities(m_impactAccumulator.clusterImpacts());

    std::list<VoxelImpact> damageImpacts = m_impactAccumulator.voxelImpacts();
    m_impactAccumulator.clear(); // TODO: Copying the list is UGLY, but the accumulator needs to be cleared at some point..
    while(damageImpacts.size() > 0) {
        m_damager.applyDamages(damageImpacts);
        m_damageForwarder.forwardDamage(m_damager.dampedDeadlyVoxelImpacts());
        m_voxelHangman.applyOnDestructionHooks(m_damager.deadVoxels());
        m_voxelHangman.removeDestroyedVoxels(m_damager.deadVoxels());
        damageImpacts = m_damageForwarder.forwardedDamageImpacts();
    }

    m_splitDetector.searchOrphans(m_damager.modifiedVoxelClusters());
    m_splitter.split(m_splitDetector.voxelClusterOrphans());
    World::instance()->god().scheduleSpawns(m_splitter.splitOffVoxelClusters());

    m_wrecker.detectWreckages(m_damager.modifiedVoxelClusters());
    //m_wrecker.applyOnWreckageHooks();
    World::instance()->god().scheduleRemovals(m_wrecker.wreckages());
    World::instance()->god().scheduleSpawns(m_wrecker.recycled());

    m_garbageCollector.check(m_damager.modifiedVoxelClusters());
    //m_garbageCollector.applyOnGarbageHooks();
    World::instance()->god().scheduleRemovals(m_garbageCollector.garbageVoxelClusters());

    World::instance()->god().remove();
    World::instance()->god().spawn();
}

