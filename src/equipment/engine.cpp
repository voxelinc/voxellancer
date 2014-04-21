#include "engine.h"

#include "equipment/engineslot.h"

#include "physics/physics.h"

#include "utils/tostring.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"

#include "voxel/voxel.h"
#include "voxeleffect/enginetrailgenerator.h"
#include "voxel/specialvoxels/engineslotvoxel.h"

#include "equipment/engineslot.h"
#include "worldobject/worldobjectcomponents.h"
#include "worldobject/worldobject.h"


Engine::Engine(const std::string& key):
    Equipment(key),
    m_trailGenerator(nullptr)
{
}

Engine::~Engine() {
    if (m_sound) {
        m_sound->stop();
    }
}

const Visuals& Engine::visuals() const {
    return m_visuals;
}

void Engine::setVisuals(const Visuals& visuals) {
    m_visuals = visuals;
}

const SoundProperties& Engine::sound() const {
    return m_engineSound;
}

void Engine::setEngineSound(const SoundProperties& engineSound) {
    m_engineSound = engineSound;
}

EnginePower Engine::power() const {
    return m_power;
}

void Engine::setPower(const EnginePower& power) {
    m_power = power;
}

EngineSlot* Engine::engineSlot() {
    return m_engineSlot;
}

const EngineSlot* Engine::engineSlot() const {
    return m_engineSlot;
}

void Engine::setEngineSlot(EngineSlot* engineSlot) {
    m_engineSlot = engineSlot;

    m_trailGenerator.reset(new EngineTrailGenerator(*this, *m_engineSlot->components()->worldObject()));
    setupTrail();
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
        return Acceleration(power().accelerationAt(m_state) / worldObject->physics().maxMass());
    } else {
        return Acceleration();
    }
}

void Engine::setupTrail() {
    m_trailGenerator->setLifetime(Property<float>::get(equipmentKey() + ".trail.lifetime", 1.0f));
    m_trailGenerator->setColor(Property<uint32_t>::get(equipmentKey() + ".trail.color", 0x6666FFFF));
    m_trailGenerator->setEmissiveness(Property<float>::get(equipmentKey() + ".trail.emissiveness", 0.4f));
}

