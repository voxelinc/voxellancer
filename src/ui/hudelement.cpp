#include "ui/hudelement.h"

HUDElement::HUDElement(): 
	VoxelCluster(),
	m_offset(0,0,0),
	m_origin(Center),
    m_transform()
{
	
}


VoxelCluster * HUDElement::voxelCluster() {
    return this;
}


WorldTransform& HUDElement::transform() {
    return m_transform;
}
