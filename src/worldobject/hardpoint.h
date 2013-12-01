#pragma once

#include "voxel/voxelcluster.h"
#include "gun.h"
#include "resource/clustercache.h"

class Ship;

class Hardpoint{
public:
    Hardpoint(Ship* ship, glm::vec3 position, Gun *gun);
    Bullet* shootAt(glm::vec3 point);
	void update(float deltasec);
    //void setGun(Gun *gun);
    //void removeGun();
    Gun *gun();

private:
    Ship* m_ship;
    glm::vec3 m_position;
    Gun* m_gun;
};