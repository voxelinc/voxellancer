#include "gridaabb.h"


GridAABB::GridAABB() {

}

GridAABB::GridAABB(const glm::ivec3 &llf, const glm::ivec3 &urb):
    m_llf(llf),
    m_urb(urb)
{

}

const glm::ivec3 &GridAABB::llf() const {
    return m_llf;
}

void GridAABB::setLLF(const glm::ivec3& llf) {
    m_llf = llf;
}

const glm::ivec3 &GridAABB::urb() const {
    return m_urb;
}

void GridAABB::setURB(const glm::ivec3& urb) {
    m_urb = urb;
}

bool GridAABB::contains(const glm::ivec3& cell) const {
    return
        cell.x >= m_llf.x && cell.x <= m_urb.x &&
        cell.y >= m_llf.y && cell.y <= m_urb.y &&
        cell.z >= m_llf.z && cell.z <= m_urb.z;
}

int GridAABB::extent(Axis axis) const {
    return m_urb[(int)axis] - m_llf[(int)axis] + 1;
}

float GridAABB::diameter() const {
    return glm::length(glm::vec3(m_urb - m_llf));
}

bool GridAABB::operator==(const GridAABB& other) const {
     return m_llf == other.llf() && m_urb == other.urb();
}

