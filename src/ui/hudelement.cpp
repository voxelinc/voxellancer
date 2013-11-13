#include "ui/hudelement.h"

HUDElement::HUDElement() : 
	m_offset(0,0,0),
	m_origin(Center){
	VoxelCluster();
}