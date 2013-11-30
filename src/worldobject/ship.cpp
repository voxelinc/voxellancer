#include "ship.h"

Ship::Ship() {
    m_world = World::instance();
}



void Ship::shoot(glm::vec3 direction){
	for(Hardpoint *hardpoint : m_hardpoints)
	{
		Bullet *b = hardpoint->shoot(transform().matrix(),direction);
        if (b != NULL)
            m_world->god().scheduleSpawn(b);
	}
}



void Ship::addHardpoint(Hardpoint *hardpoint){
	m_hardpoints.push_back(hardpoint);
}

void Ship::update(float deltasec){
	for(Hardpoint *hardpoint : m_hardpoints){
		hardpoint->update(deltasec);
	}
}
