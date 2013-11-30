#include "ui/letter.h"

Letter::Letter(): 
	m_voxelCluster(),
    m_transform()
{
	
}

Letter::~Letter() {

}


VoxelCluster * Letter::voxelCluster() {
    return &m_voxelCluster;
}

WorldTransform& Letter::transform() {
    return m_transform;
}
