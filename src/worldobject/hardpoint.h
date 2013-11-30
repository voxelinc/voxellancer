#pragma once

#include "voxel/voxelcluster.h"
#include "gun.h"
#include "resource/clustercache.h"



class Hardpoint{
public:
    Hardpoint(glm::vec3 position, Gun *gun);
    Bullet* shoot(glm::vec3 shipPosition, glm::vec3 dir);
    Bullet* shoot(glm::mat4 shipMatrix,glm::vec3 dir);
	void update(float deltasec);
    void setGun(Gun *gun);
    void removeGun();

private:
    glm::vec3 m_position;
    Gun *m_gun;
};