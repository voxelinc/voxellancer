#include "world.h"

#include "voxel/voxel.h"


World::World() :
    m_logic(*this)
{

}

World::~World() {

}

void World::update() {
    m_logic.update();
}

