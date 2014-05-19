#include "sectorlogic.h"

#include "sector.h"


SectorLogic::SectorLogic(Sector& sector):
    m_sector(sector)
{
}

void SectorLogic::update(float deltaSecs) {
    m_mover.moveWorldObjects(m_sector.worldObjects(), deltaSecs);

    m_voxelCollisionAccumulator.parse(m_mover.voxelCollisions());
    m_voxelCollisionAccumulator.applyOnCollsionHooks();

    m_damageImpactGenerator.parse(m_voxelCollisionAccumulator.worldObjectCollisions());
    m_elasticImpulseGenerator.parse(m_voxelCollisionAccumulator.worldObjectCollisions());

    m_elasticImpulsor.parse(m_elasticImpulseGenerator.worldObjectImpulses());
    damageForwardLoop(m_damageImpactGenerator.damageImpacts());

    m_splitDetector.searchSplitOffs(m_damager.worldObjectModifications());
    m_splitter.split(m_splitDetector.splitDataList());

    m_wrecker.wreck(m_damager.worldObjectModifications());

    m_garbageCollector.check(m_sector.worldObjects());
}

 DamageForwarder &SectorLogic::damageForwarder() {
    return m_damageForwarder;
 }

void SectorLogic::damageForwardLoop(std::list<DamageImpact> damageImpacts) {
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

