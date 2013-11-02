#include "aabb.h"

AABB::AABB():
    m_llf(0, 0, 0),
    m_rub(0, 0, 0)
{

}

AABB::AABB(const glm::vec3 &llf, const glm::vec3 &rub)
    m_llf(llf),
    m_rub(rub)
{

}

AABB::~AABB() {

}

glm::vec3 AABB::llf() const {
    return m_llf;
}

glm::vec3 AABB::rub() const {
    return m_rub;
}

float AABB::left() const {
    return m_llf.x;
}

float AABB::right() const {
    return m_rub.x;
}

float AABB::front() const {
    return m_llf.z;
}

float AABB::back() const {
    return m_rub.z;
}

float AABB::top() const {
    return m_rub.y;
}

float AABB::bottom() const {
    return m_llf.y;
}

AABB AABB::movedLeft(float delta) const {
    return AABB(glm::vec3(m_llf.x - delta, m_llf.y, m_llf.z), glm::vec3(m_rub.x - delta, m_rub.y, m_rub.z));
}

AABB AABB::movedRight(float delta) const {
    return AABB(glm::vec3(m_llf.x + delta, m_llf.y, m_llf.z), glm::vec3(m_rub.x + delta, m_rub.y, m_rub.z));
}

AABB AABB::movedFront(float delta) const {
    return AABB(glm::vec3(m_llf.x, m_llf.y, m_llf.z - delta), glm::vec3(m_rub.x, m_rub.y, m_rub.z - delta));
}

AABB AABB::movedBack(float delta) const {
    return AABB(glm::vec3(m_llf.x, m_llf.y, m_llf.z + delta), glm::vec3(m_rub.x, m_rub.y, m_rub.z + delta));
}

AABB AABB::movedUp(float delta) const {
    return AABB(glm::vec3(m_llf.x, m_llf.y + delta, m_llf.z), glm::vec3(m_rub.x, m_rub.y + delta, m_rub.z));
}

AABB AABB::movedDown(float delta) const {
    return AABB(glm::vec3(m_llf.x, m_llf.y - delta, m_llf.z), glm::vec3(m_rub.x, m_rub.y - delta, m_rub.z));
}

AABB AABB::moved(const glm::vec3 &delta) const {
    return AABB(m_llf + delta, m_rub + delta);
}

void AABB::moveLeft(float delta) {
    m_llf.x -= delta;
    m_rub.x -= delta;
}

void AABB::moveRight(float delta) {
    m_llf.x += delta;
    m_rub.x += delta;
}

void AABB::moveFront(float delta) {
    m_llf.z -= delta;
    m_rub.z -= delta;
}

void AABB::moveBack(float delta) {
    m_llf.z += delta;
    m_rub.z += delta;
}

void AABB::moveUp(float delta) {
    m_llf.y += delta;
    m_rub.y += delta;
}

void AABB::moveDown(float delta) {
    m_llf.y -= delta;
    m_rub.y -= delta;
}

void AABB::move(const glm::vec3& delta) {
    m_llf += delta;
    m_rub += delta;
}

bool AABB::intersects(const AABB& other) const {

}

bool AABB::contains(const AABB& other) const {

}

std::list AABB::split(Axis axis) {

}

std::list AABB::recursiveSplit(int depth, Axis axis) {

}

