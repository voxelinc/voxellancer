#include "ship.h"

#include "ai/boardcomputer.h"
#include "ai/character.h"
#include "ai/formationlogic.h"

#include "collision/collisionfilter.h"

#include "sound/sound.h"

#include "voxel/specialvoxels/engineslotvoxel.h"

#include "worldobject/components/engineslot.h"


Ship::Ship():
    Ship(new CollisionFilter(this, CollisionFilterClass::Ship))
{
}

Ship::Ship(CollisionFilter* collisionFilter):
    WorldObject(collisionFilter),
    m_character(new Character(*this)),
    m_boardComputer(new BoardComputer(this)),
    m_formationLogic(new FormationLogic(*this)),
    m_shipHandle(Handle<Ship>(this)),
    m_targetObjectHandle(Handle<WorldObject>(nullptr))
{

}

Ship::~Ship() {
//    if (m_sound) {
//        m_sound->stop();
//    }
    m_shipHandle.invalidate();
}

void Ship::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_character->update(deltaSec);
    m_boardComputer->update(deltaSec);

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

FormationLogic* Ship::formationLogic() {
    return m_formationLogic.get();
}

//
//void Ship::setEngineSound(std::shared_ptr<Sound> sound) {
//    m_sound = sound;
//    sound->setLooping(true);
//    sound->setPosition(m_transform.applyTo(m_enginePos));
//    sound->play();
//}
//
//void Ship::updateEnginePosition() {
//    m_enginePos = glm::vec3(0);
//    int engineCount = 0;
//    for (EngineSlot* engineSlot : components().engineSlots()) {
//        if(engineSlot->engine()) {
//            m_enginePos += engineSlot->voxel()->gridCell();
//            engineCount++;
//        }
//    }
//
//    if(engineCount > 0) {
//        m_enginePos /= engineCount;
//    } else {
//        m_sound->stop();
//    }
//}


