#include "ship.h"

Ship::Ship() {
    m_world = World::instance();
}



void Ship::shootAt(glm::vec3 point){
    for (Hardpoint *hardpoint : m_hardpoints){
        Bullet *b = hardpoint->shootAt(point);
        if (b != NULL)
            m_world->god().scheduleSpawn(b);
	}
}

float Ship::minAimDistance(){
    float range = 1000;
    for (Hardpoint *hardpoint : m_hardpoints){
        if (hardpoint->gun() != NULL)
            range = glm::min(hardpoint->gun()->range(), range);
    }
    return range;
}

void Ship::addHardpoint(Hardpoint *hardpoint){
	m_hardpoints.push_back(hardpoint);
}

void Ship::update(float deltasec){
	for(Hardpoint *hardpoint : m_hardpoints){
		hardpoint->update(deltasec);
	}
}
