#include "worldlogic.h"

#include <iostream>

#include "utils/tostring.h"

#include "world.h"
#include "god.h"
#include "glow/AutoTimer.h"

#include <glow/AutoTimer.h>


WorldLogic::WorldLogic(World &world):
    m_world(world)
{

}

void WorldLogic::update(float deltaSecs) {
    m_mover.moveWorldObjects(deltaSecs);

    m_voxelCollisionAccumulator.parse(m_mover.voxelCollisions());
    m_voxelCollisionAccumulator.applyOnCollsionHooks();

    m_damageImpactGenerator.parse(m_voxelCollisionAccumulator.worldObjectCollisions());
    m_elasticImpulseGenerator.parse(m_voxelCollisionAccumulator.worldObjectCollisions());

    m_elasticImpulsor.parse(m_elasticImpulseGenerator.worldObjectImpulses());
    damageForwardLoop(m_damageImpactGenerator.damageImpacts());

    m_splitDetector.searchSplitOffs(m_damager.worldObjectModifications());
    m_splitter.split(m_splitDetector.splitDataList());

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

    glow::AutoTimer t("damageForwardLoop");

    while(damageImpacts.size() > 0) {
        // only treat clusters that aren't scheduled for removal anyway
        for (WorldObject* object : m_world.god().scheduledRemovals()){
            std::list<DamageImpact>::iterator iter = damageImpacts.begin();
            while (iter != damageImpacts.end()){
                if (iter->worldObject() == object){
                    damageImpacts.erase(iter++);
                } else {
                    ++iter;
                }
            }
        }

        m_damager.applyDamages(damageImpacts);

        m_damageForwarder.forwardDamageImpacts(m_damager.deadlyDamageImpacts());
        m_damageForwarder.dontForwardTo(m_damager.deadVoxels());

        m_voxelHangman.applyOnDestructionHooks(m_damager.deadlyDamageImpacts());
        m_voxelHangman.removeDestroyedVoxels(m_damager.deadlyDamageImpacts());

        damageImpacts = m_damageForwarder.forwardedDamageImpacts();
    }
}

