#include "worldlogic.h"

#include <iostream>

#include "utils/tostring.h"

#include "world.h"
#include "god.h"

#include <glow/AutoTimer.h>


WorldLogic::WorldLogic(World &world):
    m_world(world)
{

}

void WorldLogic::update(float deltaSecs) {
    m_mover.moveWorldObjects(deltaSecs);

    m_impactAccumulator.parse(m_mover.impacts());
    //m_impactResolver.alterVelocities(m_impactAccumulator.clusterImpacts());

    m_impactAccumulator.applyOnImpactHooks();

    damageForwardLoop(m_impactAccumulator.impacts());

    m_impactAccumulator.clear();

    m_splitDetector.searchSplitOffs(m_damager.worldObjectModifications());
    m_splitter.split(m_splitDetector.worldObjectSplits());
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

void WorldLogic::damageForwardLoop(std::list<Impact> damageImpacts) {
    m_damager.reset();

    if(damageImpacts.size() == 0) {
        return;
    }

    glow::AutoTimer t("damageForwardLoop");

    while(damageImpacts.size() > 0) {
        // only treat clusters that aren't scheduled for removal anyway
        for (WorldObject* object : m_world.god().scheduledRemovals()){
            std::list<Impact>::iterator iter = damageImpacts.begin();
            while (iter != damageImpacts.end()){
                if (iter->worldObject() == object){
                    damageImpacts.erase(iter++);
                } else {
                    ++iter;
                }
            }
        }

        m_damager.applyDamages(damageImpacts);

        m_damageForwarder.forwardDamageImpacts(m_damager.deadlyImpacts());
        m_damageForwarder.dontForwardTo(m_damager.deadVoxels());

        m_voxelHangman.applyOnDestructionHooks(m_damager.deadlyImpacts());
        m_voxelHangman.removeDestroyedVoxels(m_damager.deadlyImpacts());

        damageImpacts = m_damageForwarder.forwardedDamageImpacts();
    }
}
