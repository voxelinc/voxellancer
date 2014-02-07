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
#include "ai/squadlogic.h"
#include "sound/sound.h"
#include "collision/collisionfilter.h"


Ship::Ship() : Ship(new CollisionFilter(this, CollisionFilterClass::Ship))
{
}

Ship::Ship(CollisionFilter* collisionFilter):
    WorldObject(collisionFilter),
    m_hardpoints(),
    m_engines(),
    prop_maxSpeed("ship.maxSpeed"),
    prop_maxRotSpeed("ship.maxRotSpeed"),
    m_character(new Character(*this)),
    m_boardComputer(new BoardComputer(*this)),
    m_squadLogic(new SquadLogic(*this)),
    m_shipHandle(Handle<Ship>(this)),
    m_targetObjectHandle(Handle<WorldObject>(nullptr))
{

}


Ship::~Ship() {
    if (m_sound) {
        m_sound->stop();
    }
    m_shipHandle.invalidate();
}

void Ship::update(float deltaSec) {
    m_character->update(deltaSec);
    for(Hardpoint *hardpoint : m_hardpoints) {
        hardpoint->update(deltaSec);
    }

    for (Engine *engine : m_engines) {
        engine->update(deltaSec);
    }

    if (m_sound) {
        m_sound->setPosition(m_transform.applyTo(m_enginePos));
    }

    WorldObject::update(deltaSec);
}

void Ship::addHardpointVoxel(HardpointVoxel* voxel) {
    Hardpoint* point;
    //TODO: Adding the actual Launcher here is wrong, this is test code
    if (m_hardpoints.size() % 3 == 0) {
        point = new Hardpoint(this, voxel->gridCell(), std::make_shared<RocketLauncher>());
    } else {
        point = new Hardpoint(this, voxel->gridCell(), std::make_shared<Gun>());
    }
    voxel->setHardpoint(point);
    m_hardpoints.push_back(point);
    addVoxel(voxel);
}

void Ship::removeHardpoint(Hardpoint *hardpoint) {
    m_hardpoints.remove(hardpoint);
}

const std::list<Hardpoint*> Ship::hardpoints() const {
    return m_hardpoints;
}

void Ship::addEngineVoxel(EngineVoxel* voxel) {
    Engine* engine = new Engine(this, voxel);
    voxel->setEngine(engine);
    m_engines.push_back(engine);
    addVoxel(voxel);

    updateEnginePosition();

}

void Ship::removeEngine(Engine* engine) {
    m_engines.remove(engine);
}

void Ship::setTargetObject(WorldObject* target) {
    m_targetObjectHandle = target ? target->handle() : Handle<WorldObject>(nullptr);
}

WorldObject* Ship::targetObject() {
    return m_targetObjectHandle.get();
}

void Ship::fireAtPoint(glm::vec3 target) {
    for (Hardpoint* hardpoint : m_hardpoints) {
        if (hardpoint->aimType() == AimType::Point) {
            hardpoint->shootAtPoint(target);
        }
    }
}

void Ship::fireAtObject() {
    if(targetObject()) {
        for (Hardpoint* hardpoint : m_hardpoints) {
            if (hardpoint->aimType() == AimType::Object) {
                hardpoint->shootAtObject(targetObject());
            }
        }
    }
}

float Ship::minAimDistance() { // is this needed ?!
    float range = 1000;
    for (Hardpoint *hardpoint : m_hardpoints){
        if (hardpoint->range() > 0) {
            range = glm::min(hardpoint->range(), range);
        }
    }
    return range;
}

float Ship::maxAimDistance() { // is this needed ?!
    float range = 0;
    for (Hardpoint *hardpoint : m_hardpoints) {
        if (hardpoint->range() != -1)
            range = glm::max(hardpoint->range(), range);
    }
    return range;
}

void Ship::accelerate(const glm::vec3& direction) {
    m_physics.accelerate(direction * prop_maxSpeed.get());
}

void Ship::accelerateAngular(const glm::vec3& axis) {
    m_physics.accelerateAngular(axis * prop_maxRotSpeed.get());
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

SquadLogic* Ship::squadLogic() {
    return m_squadLogic.get();
}

void Ship::setEngineSound(std::shared_ptr<Sound> sound) {
    m_sound = sound;
    sound->setLooping(true);
    sound->setPosition(m_transform.applyTo(m_enginePos));
    sound->play();
}

void Ship::updateEnginePosition() {
    m_enginePos = glm::vec3(0);
    for (const Engine* engine : m_engines) {
        m_enginePos += engine->positionInGrid();
    }
    m_enginePos /= m_engines.size();
}

Handle<Ship> Ship::shipHandle() {
    return m_shipHandle;
}
