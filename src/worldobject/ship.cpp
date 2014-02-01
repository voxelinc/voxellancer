#include "ship.h"

#include "hardpoint.h"
#include "engine.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "voxel/specialvoxels/enginevoxel.h"
#include "worldobject/handle/handle.h"
#include "worldobject/weapons/gun.h"
#include "worldobject/weapons/rocketlauncher.h"
#include "ai/character.h"
#include "ai/boardcomputer.h"
#include "sound/sound.h"

Ship::Ship() :
    WorldObject(CollisionFilterClass::Ship),
    m_character(new Character(*this)),
    m_boardComputer(new BoardComputer(*this)),
    m_shipHandle(Handle<Ship>(this)),
    m_targetObjectHandle(Handle<WorldObject>(nullptr))
{
}

Ship::~Ship() {
    m_shipHandle.invalidate();
}

void Ship::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_character->update(deltaSec);
    m_components.update();

//    if (m_sound) {
//        m_sound->setPosition(m_transform.applyTo(m_enginePos));
//    }
}

Handle<Ship> Ship::shipHandle() {
    return m_shipHandle;
}

void Ship::setTargetObject(WorldObject* target) {
    m_targetObjectHandle = target ? target->handle() : Handle<WorldObject>(nullptr);
}

WorldObject* Ship::targetObject() {
    return m_targetObjectHandle.get();
}

void Ship::setCharacter(Character* character) {
    m_character.reset(character);
}

Character* Ship::character() {
    return m_character.get();
}

BoardComputer* Ship::boardComputer() {
    return m_boardComputer.get();
}

//void Ship::setEngineSound(std::shared_ptr<Sound> sound) {
//    m_sound = sound;
//    sound->setLooping(true);
//    sound->setPosition(m_transform.applyTo(m_enginePos));
//    sound->play();
//}

//void Ship::updateEnginePosition() {
//    m_enginePos = glm::vec3(0);
//    for (const Engine* engine : m_engines) {
//        m_enginePos += engine->positionInGrid();
//    }
//    m_enginePos /= m_engines.size();
//}
