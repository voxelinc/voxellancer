#include "aabb.h"

#include <cassert>
#include <algorithm>

AABB::AABB():
    m_llf(0, 0, 0),
    m_rub(0, 0, 0)
{

}

AABB::AABB(const glm::vec3 &llf, const glm::vec3 &rub):
    m_llf(llf),
    m_rub(rub)
{
    assert(m_llf.x <= m_rub.x && m_llf.y <= m_rub.y && m_llf.z <= m_rub.z);
}

AABB::~AABB() {

}

const glm::vec3 &AABB::llf() const {
    return m_llf;
}

void AABB::setLlf(const glm::vec3 &llf) {
    assert(llf.x <= m_rub.x && llf.y <= m_rub.y && llf.z <= m_rub.z);
    m_llf = llf;
}

const glm::vec3 &AABB::rub() const {
    return m_rub;
}

void AABB::setRub(const glm::vec3 &rub) {
    assert(m_llf.x <= rub.x && m_llf.y <= rub.y && m_llf.z <= rub.z);
    m_rub = rub;
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

float AABB::axisMin(Axis axis) const {
    return m_llf[(int)axis];
}

float AABB::axisMax(Axis axis) const {
    return m_rub[(int)axis];
}

float AABB::width() const {
    return m_rub.x - m_llf.x;
}

float AABB::height() const {
    return m_rub.y - m_llf.y;
}

float AABB::depth() const {
    return m_rub.z - m_llf.z;
}

float AABB::extent(Axis axis) const {
    return m_rub[(int)axis] - m_llf[(int)axis];
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

AABB AABB::moved(Axis axis, float delta) const {
    AABB result(*this);
    result.move(axis, delta);
    return result;
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

void AABB::move(Axis axis, float delta) {
    m_llf[(int)axis] += delta;
    m_rub[(int)axis] += delta;
}

void AABB::move(const glm::vec3& delta) {
    m_llf += delta;
    m_rub += delta;
}

void AABB::expand(Axis axis, float delta) {
    if(delta > 0) {
        m_rub[(int)axis] += delta;
    }
    else {
        m_llf[(int)axis] += delta;
    }
}

AABB AABB::expanded(Axis axis, float delta) const {
    AABB result(*this);
    result.expand(axis, delta);
    return result;
}

bool AABB::intersects(const AABB& other) const {
    AABB unitedAABB(united(other));

    return
        unitedAABB.width() < width() + other.width() &&
        unitedAABB.height() < height() + other.height() &&
        unitedAABB.depth() < depth() + other.depth();
}

bool AABB::contains(const AABB& other) const {
    return
        m_llf.x <= other.m_llf.x &&
        m_llf.y <= other.m_llf.y &&
        m_llf.z <= other.m_llf.z &&
        m_rub.x >= other.m_rub.x &&
        m_rub.y >= other.m_rub.y &&
        m_rub.z >= other.m_rub.z;
}

AABB AABB::united(const AABB &other) const {
    AABB result(*this);
    result.unite(other);
    return result;
}

void AABB::unite(const AABB &other) {
    m_llf.x = std::min(m_llf.x, other.m_llf.x);
    m_llf.y = std::min(m_llf.y, other.m_llf.y);
    m_llf.z = std::min(m_llf.z, other.m_llf.z);
    m_rub.x = std::max(m_rub.x, other.m_rub.x);
    m_rub.y = std::max(m_rub.y, other.m_rub.y);
    m_rub.z = std::max(m_rub.z, other.m_rub.z);
}

std::list<AABB> AABB::split(Axis axis) const {
    std::list<AABB> result;
    AABB a, b;

    split(a, b, axis);
    result.push_back(a);
    result.push_back(b);

    return result;
}

void AABB::split(AABB &a, AABB &b, Axis axis) const {
    glm::vec3 newRub(m_rub), newLlf(m_llf);
    newRub[(int)axis] -= extent(axis)/2;
    newLlf[(int)axis] += extent(axis)/2;

    a = AABB(m_llf, newRub);
    b = AABB(newLlf, m_rub);
}

std::list<AABB> AABB::recursiveSplit(int recursions, Axis axis) const {
    assert(recursions >= 0);

    if(recursions == 0) {
        return split(axis);
    }

    std::list<AABB> result, subResult;
    Axis nextAxis;

    subResult = split(axis);

    nextAxis = (Axis)(((int)axis + 1) % 3);

    result.splice(result.end(), subResult.front().recursiveSplit(recursions-1, nextAxis));
    result.splice(result.end(), subResult.back().recursiveSplit(recursions-1, nextAxis));

    return result;
}

