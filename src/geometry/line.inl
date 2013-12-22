#pragma once

#include <algorithm>

#include "aabb.h"


template<typename T>
bool Line::nearTo(const TAABB<T>& aabb) const {
    glm::vec3 llf(std::min(m_a.x, m_b.x), std::min(m_a.y, m_b.y), std::min(m_a.z, m_b.z));
    glm::vec3 rub(std::max(m_a.x, m_b.x), std::max(m_a.y, m_b.y), std::max(m_a.z, m_b.z));

    TAABB<T> lineAABB(llf, rub);
    return lineAABB.intersects(aabb);
}

