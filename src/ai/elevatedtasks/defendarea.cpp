//#include "defendarea.h"
//
//#include "worldobject/ship.h"
//#include "world/world.h"
//
//DefendArea::DefendArea(Ship& ship, std::list<glm::vec3> points, int attackRange) :
//ElevatedTask(ship),
//m_points(points),
//m_currentPoint(m_points.begin()),
//m_flyTask(ship),
//m_fightTask(ship, std::list<std::shared_ptr<WorldObjectHandle>>{}),
//m_attackRange(attackRange),
//m_enemiesInRange(){
//}
//
//void DefendArea::update(float deltaSec) {
//    if (glm::length(*m_currentPoint - m_ship.transform().position()) < m_ship.minimalGridSphere().radius() * m_ship.transform().scale()) {
//        m_currentPoint++;
//        if (m_currentPoint == m_points.end()) {
//            m_currentPoint = m_points.begin();
//        }
//    }
//    for (World::instance()->worldObjects().begin)
//    m_flyTask.setTargetPoint(*m_currentPoint);
//    m_flyTask.update(deltaSec);
//}
