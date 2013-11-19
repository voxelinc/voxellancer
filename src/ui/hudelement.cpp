#include "ui/hudelement.h"

HUDElement::HUDElement(): 
	VoxelCluster(),
	m_offset(0,0,0),
	m_origin(Center)
{
	
}

HUDElement::HUDElement(const VoxelCluster& other) :
	VoxelCluster(other),
	m_offset(0, 0, 0),
	m_origin(Center)
{

}