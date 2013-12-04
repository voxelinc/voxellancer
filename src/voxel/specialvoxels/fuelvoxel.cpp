#include "fuelvoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"

FuelVoxel::FuelVoxel(const glm::ivec3 &gridCell, int color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_object(nullptr)
{
}

FuelVoxel::~FuelVoxel() {
}

void FuelVoxel::addToObject(WorldObject *object){
    m_object = object;
    object->addVoxel(this);
}

void FuelVoxel::onDestruction(){
    //TODO: Explode
}
