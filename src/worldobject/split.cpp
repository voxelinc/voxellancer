#include "split.h"

Split::Split(const WorldTransform& transform) :
    WorldObject(transform.scale()) 
{
    m_transform.setPosition(transform.position());
    m_transform.setOrientation(transform.orientation());
    m_transform.setCenter(transform.center());
}

void Split::finishInitialization() {
    m_transform.setCenterAndAdjustPosition(m_physics->calculateMassAndCenter());
    m_collisionDetector->finishInitialization();
}
