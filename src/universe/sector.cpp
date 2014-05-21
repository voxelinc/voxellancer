#include "sector.h"

#include <glow/Program.h>

#include "collision/collisiondetector.h"
#include "collision/voxelcollision.h"

#include "display/rendering/skybox.h"

#include "voxel/voxelrenderer.h"

#include "voxeleffect/voxelparticleengine.h"

#include "worldobject/worldobjectinfo.h"

#include "worldtree/worldtree.h"

#include "gameobjectmanager.h"
#include "sectorlogic.h"
#include "universe.h"
#include "worldobjectmanager.h"


Sector::Sector(const std::string& name, Universe& universe):
    m_name(name),
    m_universe(universe),
    m_particleEngine(*this),
    m_sectorLogic(*this),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_lightDir(0.3f, 0.5f, 1.0f),
    m_functionalObjects(universe),
    m_worldObjects(*this)
{

}

Sector::~Sector() = default;

const std::string& Sector::name() const {
    return m_name;
}

Universe& Sector::universe() {
    return m_universe;
}

WorldTree& Sector::worldTree() {
    return m_worldTree;
}

VoxelParticleEngine& Sector::particleEngine() {
    return m_particleEngine;
}

std::list<glow::ref_ptr<FunctionalObject>>& Sector::functionalObjects() {
    return m_functionalObjects->objects();
}

std::list<glow::ref_ptr<WorldObject>>& Sector::worldObjects() {
    return m_worldObjects->objects();
}

void Sector::addFunctionalObject(FunctionalObject* object) {
    m_functionalObjects->addObject(object);
}

bool Sector::addWorldObject(WorldObject* object) {
    m_worldTree->insert(object);
    std::list<VoxelCollision> collisions = object->collisionDetector().checkCollisions();
    m_worldTree->remove(object);

    if (collisions.empty()) {
        object->setSpawnState(SpawnState::Spawned);
        m_worldObjects->addObject(object);

        return true;
    } else {
        glow::warning("Failed to spawn %;", object->info().name());

        object->setSpawnState(SpawnState::Rejected);
        object->onSpawnFail();

        return false;
    }
}

void Sector::update(float deltaSec) {
    m_sectorLogic->update(deltaSec);

    m_worldObjects->update(deltaSec);
    m_functionalObjects->update(deltaSec);

    m_particleEngine->update(deltaSec);
}

void Sector::draw(const Camera& camera) {
    m_skybox->draw(camera);

    m_voxelRenderer->program()->setUniform("lightdir", m_lightDir);

    m_voxelRenderer->prepareDraw(camera);

    for (glow::ref_ptr<WorldObject>& worldObject : m_worldObjects->objects()) {
        VoxelRenderer::instance()->draw(*worldObject);
    }

    m_voxelRenderer->afterDraw();

    m_particleEngine->draw(camera);
}

