#include "ship.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

Ship::Ship() {
    m_world = World::instance();
}

void Ship::update(float deltasec){
	for(Hardpoint *hardpoint : m_hardpoints){
		hardpoint->update(deltasec);
	}
}

void Ship::addHardpointVoxel(HardpointVoxel* voxel){
    Hardpoint* point = new Hardpoint(this, glm::vec3(voxel->gridCell()), new Gun(100, 400, 0.2f));
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

void Ship::shootAt(glm::vec3 point){
    for (Hardpoint* hardpoint : m_hardpoints){
        if (hardpoint->aimType() == AimType::Point){
            hardpoint->shootAtPoint(point);
        }
    }
}

float Ship::minAimDistance(){ // is this needed ?!
    float range = 1000;
    for (Hardpoint *hardpoint : m_hardpoints){
        if (hardpoint->range() != -1)
            range = glm::min(hardpoint->range(), range);
    }
    return range;
}
