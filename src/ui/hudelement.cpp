#include "ui/hudelement.h"

HUDElement::HUDElement(): 
	VoxelCluster(),
	m_offset(0,0,0),
	m_origin(Center),
    m_transform()
{
	
}

HUDElement::HUDElement(const HUDElement& other) :
	VoxelCluster(other),
	m_offset(0, 0, 0),
	m_origin(Center),
    m_transform()
{

}

VoxelCluster * HUDElement::voxelCluster()
{
    return this;
}

glm::mat4 HUDElement::matrix()
{
    return m_transform.matrix();
}
