#include "ship.h"

#include "voxel/specialvoxels/hardpointvoxel.h"
#include "worldobject/weapons/launcher.h"
#include "worldobject/weapons/gun.h"

Ship::Ship() :
    m_world(World::instance()),
    m_hardpoints(),
    m_aimMode(Point),
    m_targetPoint(0),
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
    point = new Hardpoint(this, glm::vec3(voxel->gridCell()), new Gun());
    /*if (m_hardpoints.size() % 2 == 0)
        point = new Hardpoint(this, glm::vec3(voxel->gridCell()), new Gun(100, 400, 0.2f));
    else
        point = new Hardpoint(this, glm::vec3(voxel->gridCell()), new Gun(100, 400, 0.2f));*/
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

void Ship::setAimMode(AimType mode){
    m_aimMode = mode;
}

AimType Ship::aimMode(){
    return m_aimMode;
}

void Ship::setTargetPoint(glm::vec3 target){
    m_targetPoint = target;
}

glm::vec3 Ship::targetPoint(){
    return m_targetPoint;
}

void Ship::setTargetObject(WorldObject* target){
    m_targetObject = target;
}
WorldObject* Ship::targetObject(){
    return m_targetObject;
}

void Ship::fire(){
    if (m_aimMode == Point){
        for (Hardpoint* hardpoint : m_hardpoints){
            if (hardpoint->aimType() == Point){
                hardpoint->shootAtPoint(m_targetPoint);
            }
        }
    } else if (m_aimMode == Object){
        for (Hardpoint* hardpoint : m_hardpoints){
            if (hardpoint->aimType() == Object){
                hardpoint->shootAtPoint(m_targetPoint);
            }
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
