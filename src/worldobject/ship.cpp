#include "ship.h"

#include "hardpoint.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "worldobject/weapons/gun.h"
#include "worldobject/weapons/rocketlauncher.h"

Ship::Ship() :
    m_world(World::instance()),
    m_hardpoints(),
	prop_maxSpeed("ship.maxSpeed"),
	prop_maxRotSpeed("ship.maxRotSpeed"),
    m_targetObject(nullptr)
{
}

void Ship::update(float deltasec){
    for(Hardpoint *hardpoint : m_hardpoints){
        hardpoint->update(deltasec);
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

void Ship::accelerate(glm::vec3 direction) {
    direction *= prop_maxSpeed.get();
    m_physics->accelerate(direction);
}

void Ship::accelerateAngular(glm::vec3 axis) {
    axis *= prop_maxRotSpeed.get();
    m_physics->accelerateAngular(axis);
}
