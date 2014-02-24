#include "engine.h"

#include "utils/tostring.h"

#include "worldobject/worldobjectcomponents.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/worldobject.h"

#include "physics/physics.h"
#include "voxeleffect/enginetrailgenerator.h"
#include "voxel/specialvoxels/engineslotvoxel.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"


Engine::Engine(const std::string& key):
    Equipment(key),
    m_trailGenerator(new EngineTrailGenerator(this))
{
    setupTrail();
}

Engine::~Engine() {
    if (m_sound) {
        m_sound->stop();
    }
}

EngineSlot* Engine::engineSlot() {
    return m_engineSlot;
}

void Engine::setEngineSlot(EngineSlot* engineSlot) {
    m_engineSlot = engineSlot;
}

void Engine::update(float deltaSec) {
    if (!m_sound) {
        m_sound = SoundManager::current()->play(sound(), engineSlot()->voxel()->position());
    }
    m_sound->setPosition(engineSlot()->voxel()->position());

    m_trailGenerator->update(deltaSec);
}

const EngineState& Engine::state() const {
    return m_state;
}

void Engine::setState(const EngineState& state) {
    m_state = state;
}

Acceleration Engine::currentAcceleration() const {
    WorldObject* worldObject = (m_engineSlot ? m_engineSlot->components()->worldObject() : nullptr);
    if (worldObject) {
        return Acceleration(power().accelerationAt(m_state) / worldObject->physics().mass());
    } else {
        return Acceleration();
    }
}

void Engine::setupTrail() {
    m_trailGenerator->setLifetime(Property<float>(equipmentKey() + ".trail.lifetime"));
}

