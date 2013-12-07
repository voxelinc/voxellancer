#pragma once

#include "voxel/voxelcluster.h"
#include "gun.h"
#include "resource/clustercache.h"

class Ship;

class Hardpoint{
public:
    Hardpoint(Ship* ship, const glm::vec3& position, Launcher *launcher);
    ~Hardpoint();
    void setLauncher(Launcher *launcher);
    //void removeGun();
    Launcher *launcher();

    void update(float delta_sec);
    AimType aimType();
    void shootAtPoint(glm::vec3 target);
    void shootAtObject(WorldObject* target);
    float range();

    void voxelRemoved();

private:
    Ship* m_ship;
    glm::vec3 m_position;
    Launcher *m_launcher;
};