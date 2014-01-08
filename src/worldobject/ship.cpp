#include "ship.h"

#include "hardpoint.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "worldobject/weapons/gun.h"
#include "worldobject/weapons/rocketlauncher.h"
#include "ai/character.h"

Ship::Ship() :
    WorldObject(CollisionFilterClass::Ship),
    m_hardpoints(),
	prop_maxSpeed("ship.maxSpeed"),
	prop_maxRotSpeed("ship.maxRotSpeed"),
    m_targetObject(nullptr),
    m_character(new Character(*this)),
    m_boardComputer(*this)
{
}

void Ship::update(float deltaSec){
    m_character->update(deltaSec);
    for(Hardpoint *hardpoint : m_hardpoints){
        hardpoint->update(deltaSec);
    }
}

void Ship::addHardpointVoxel(HardpointVoxel* voxel){
    Hardpoint* point;
    //TODO: Adding the actual Launcher here is wrong, this is test code
    //point = new Hardpoint(this, glm::vec3(voxel->gridCell()), new Gun());
    if (m_hardpoints.size() % 3 == 0)
        point = new Hardpoint(this, glm::vec3(voxel->gridCell()), new RocketLauncher());
    else
        point = new Hardpoint(this, glm::vec3(voxel->gridCell()), new Gun());
    voxel->setHardpoint(point);
    m_hardpoints.push_back(point);
    addVoxel(voxel);
}

void Ship::removeHardpoint(Hardpoint *hardpoint){
    std::vector<Hardpoint*>::iterator iterator = m_hardpoints.begin();
    while (iterator != m_hardpoints.end()){
        if (*iterator == hardpoint){
            delete *iterator;
            m_hardpoints.erase(iterator);
            break;
        }
        ++iterator;
    }
}

void Ship::setTargetObject(WorldObject* target){
    m_targetObject = target;
}
WorldObject* Ship::targetObject(){
    return m_targetObject;
}

void Ship::fireAtPoint(glm::vec3 target){
    for (Hardpoint* hardpoint : m_hardpoints){
        if (hardpoint->aimType() == Point){
            hardpoint->shootAtPoint(target);
        }
    }
}

void Ship::fireAtObject(){
    for (Hardpoint* hardpoint : m_hardpoints){
        if (hardpoint->aimType() == Object){
            hardpoint->shootAtObject(m_targetObject);
        }
    }
}

float Ship::minAimDistance(){ // is this needed ?!
    float range = 1000;
    for (Hardpoint *hardpoint : m_hardpoints){
        if (hardpoint->aimRange() != -1)
            range = glm::min(hardpoint->aimRange(), range);
    }
    return range;
}

void Ship::accelerate(const glm::vec3& direction) {
    m_physics->accelerate(direction * prop_maxSpeed.get());
}


void Ship::accelerateAngular(const glm::vec3& axis) {
    m_physics->accelerateAngular(axis * prop_maxRotSpeed.get());
}

void Ship::setCharacter(Character* character){
    m_character.reset(character);
}

Character* Ship::character(){
    return m_character.get();
}