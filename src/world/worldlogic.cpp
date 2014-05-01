#include "worldlogic.h"

#include "utils/tostring.h"

#include "world.h"
#include "god.h"


WorldLogic::WorldLogic(World &world):
    m_world(world)
{

}

void WorldLogic::addDamageImpact(const DamageImpact& damageImpact) {
    m_damageImpacts.push_back(damageImpact);
}

void WorldLogic::update(float deltaSecs) {
    m_world.god().remove();
    m_world.god().spawn();

    m_mover.moveWorldObjects(deltaSecs);

    m_voxelCollisionAccumulator.parse(m_mover.voxelCollisions());
    m_voxelCollisionAccumulator.applyOnCollsionHooks();

    m_damageImpactGenerator.parse(m_voxelCollisionAccumulator.worldObjectCollisions());
    m_damageImpactGenerator.parse(m_damageImpacts);

    m_impulseGenerator.parse(m_voxelCollisionAccumulator.worldObjectCollisions());

    m_impulsor.parse(m_impulseGenerator.worldObjectImpulses());

    damageForwardLoop(m_damageImpactGenerator.damageImpacts());

    m_splitDetector.searchSplitOffs(m_damager.worldObjectModifications());
    m_splitter.split(m_splitDetector.splitDataList());

    m_world.god().scheduleSpawn(m_splitter.splitOffWorldObjects());

    m_wrecker.detectWreckedObjects(m_damager.worldObjectModifications());
    //m_wrecker.applyOnWreckageHooks();

    m_world.god().scheduleRemovals(m_wrecker.wreckedObjects());
    m_world.god().scheduleSpawn(m_wrecker.newWreckages());

    m_garbageCollector.check(m_world.worldObjects()/*m_damager.modifiedVoxelClusters()*/);
    //m_garbageCollector.applyOnGarbageHooks();
    m_world.god().scheduleRemovals(m_garbageCollector.garbageVoxelClusters());

    m_world.god().remove();
    m_world.god().spawn();

    m_damageImpacts.clear();
}

 DamageForwarder &WorldLogic::damageForwarder() {
    return m_damageForwarder;
 }

void WorldLogic::damageForwardLoop(std::list<DamageImpact> damageImpacts) {
    m_damager.reset();

    while(!damageImpacts.empty()) {

        m_damager.applyDamages(damageImpacts);

        m_damageForwarder.forwardDamageImpacts(m_damager.deadlyDamageImpacts());
        m_damageForwarder.dontForwardTo(m_damager.deadVoxels());

        m_voxelHangman.applyOnDestructionHooks(m_damager.deadlyDamageImpacts());
        m_voxelHangman.removeDestroyedVoxels(m_damager.deadlyDamageImpacts());

        damageImpacts = m_damageForwarder.forwardedDamageImpacts();
    }
}

