#include "gridaabb.h"


GridAABB::GridAABB() {

}

GridAABB::GridAABB(const glm::ivec3 &llf, const glm::ivec3 &rub):
    m_llf(llf),
    m_rub(rub)
{

}

const glm::ivec3 &GridAABB::llf() const {
    return m_llf;
}

void GridAABB::setLLF(const glm::ivec3& llf) {
    m_llf = llf;
}

const glm::ivec3 &GridAABB::rub() const {
    return m_rub;
}

void GridAABB::setRUB(const glm::ivec3& rub) {
    m_rub = rub;
}

bool GridAABB::contains(const glm::ivec3& cell) const {
    return
        cell.x >= m_llf.x && cell.x <= m_rub.x &&
        cell.y >= m_llf.y && cell.y <= m_rub.y &&
        cell.z >= m_llf.z && cell.z <= m_rub.z;
}

int GridAABB::extent(Axis axis) const {
    return m_rub[(int)axis] - m_llf[(int)axis] + 1;
}

float GridAABB::diameter() const {
    return glm::length(m_rub - m_llf);
}

bool GridAABB::operator==(const GridAABB& other) {
     return m_llf == other.llf() && m_rub == other.rub();
}
