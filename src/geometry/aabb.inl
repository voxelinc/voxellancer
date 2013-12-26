#include "aabb.h"

#include <cassert>
#include <algorithm>

#include "worldtransform.h"

#include "sphere.h"
#include "line.h"
#include "ray.h"


template<typename T>
TAABB<T>::TAABB():
    m_llf(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)),
    m_rub(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0))
{

}

template<typename T>
TAABB<T>::TAABB(const glm::detail::tvec3<T> &llf, const glm::detail::tvec3<T> &rub):
    m_llf(llf),
    m_rub(rub)
{
    assert(m_llf.x <= m_rub.x && m_llf.y <= m_rub.y && m_llf.z <= m_rub.z);
}

template<typename T>
const glm::detail::tvec3<T> &TAABB<T>::llf() const {
    return m_llf;
}

template<typename T>
void TAABB<T>::setLlf(const glm::detail::tvec3<T> &llf) {
    assert(llf.x <= m_rub.x && llf.y <= m_rub.y && llf.z <= m_rub.z);
    m_llf = llf;
}

template<typename T>
const glm::detail::tvec3<T> &TAABB<T>::rub() const {
    return m_rub;
}

template<typename T>
void TAABB<T>::setRub(const glm::detail::tvec3<T> &rub) {
    assert(m_llf.x <= rub.x && m_llf.y <= rub.y && m_llf.z <= rub.z);
    m_rub = rub;
}

template<typename T>
T TAABB<T>::axisMin(Axis axis) const {
    return m_llf[(int)axis];
}

template<typename T>
T TAABB<T>::axisMax(Axis axis) const {
    return m_rub[(int)axis];
}

template<typename T>
glm::detail::tvec3<T> TAABB<T>::middle() const {
    return (m_rub + m_llf) / static_cast<T>(2);
}

template<typename T>
T TAABB<T>::extent(Axis axis) const {
    return m_rub[(int)axis] - m_llf[(int)axis];
}

template<typename T>
TAABB<T> TAABB<T>::moved(Axis axis, T delta) const {
    TAABB result(*this);
    result.move(axis, delta);
    return result;
}

template<typename T>
TAABB<T> TAABB<T>::moved(const glm::detail::tvec3<T> &delta) const {
    return TAABB(m_llf + delta, m_rub + delta);
}

template<typename T>
void TAABB<T>::move(Axis axis, T delta) {
    m_llf[(int)axis] += delta;
    m_rub[(int)axis] += delta;
}

template<typename T>
void TAABB<T>::move(const glm::detail::tvec3<T>& delta) {
    m_llf += delta;
    m_rub += delta;
}

template<typename T>
void TAABB<T>::expand(Axis axis, T delta) {
    if(delta > 0) {
        m_rub[(int)axis] += delta;
    }
    else {
        m_llf[(int)axis] += delta;
    }
}

template<typename T>
TAABB<T> TAABB<T>::expanded(Axis axis, T delta) const {
    TAABB result(*this);
    result.expand(axis, delta);
    return result;
}

template<typename T>
template<typename OtherT>
bool TAABB<T>::intersects(const TAABB<OtherT>& other) const {
    if(m_llf.x < other.llf().x) {
        if(other.llf().x >= m_rub.x) {
            return false;
        }
    } else {
        if(m_llf.x >= other.rub().x) {
            return false;
        }
    }

    if(m_llf.y < other.llf().y) {
        if(other.llf().y >= m_rub.y) {
            return false;
        }
    } else {
        if(m_llf.y >= other.rub().y) {
            return false;
        }
    }

    if(m_llf.z < other.llf().z) {
        if(other.llf().z >= m_rub.z) {
            return false;
        }
    } else {
        if(m_llf.z >= other.rub().z) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool TAABB<T>::intersects(const Sphere& sphere) const {
    assert(false); // Not implemented yet
    return false;
}

template<typename T>
bool TAABB<T>::containedBy(const TAABB<float>& other) const {
    return
        other.llf().x <= m_llf.x &&
        other.llf().y <= m_llf.y &&
        other.llf().z <= m_llf.z &&
        other.rub().x >= m_rub.x &&
        other.rub().y >= m_rub.y &&
        other.rub().z >= m_rub.z;
}

template<typename T>
bool TAABB<T>::contains(const TAABB& other) const {
    return
        m_llf.x <= other.m_llf.x &&
        m_llf.y <= other.m_llf.y &&
        m_llf.z <= other.m_llf.z &&
        m_rub.x >= other.m_rub.x &&
        m_rub.y >= other.m_rub.y &&
        m_rub.z >= other.m_rub.z;
}

template<typename T>
bool TAABB<T>::contains(const glm::detail::tvec3<T> &vec) const {
    return
        vec.x >= m_llf.x &&
        vec.y >= m_llf.y &&
        vec.z >= m_llf.z &&
        vec.x <= m_rub.x &&
        vec.y <= m_rub.y &&
        vec.z <= m_rub.z;
}

template<typename T>
bool TAABB<T>::nearTo(const TAABB<float>& other) const {
    return intersects(other);
}

template<typename T>
TAABB<T> TAABB<T>::united(const TAABB &other) const {
    TAABB result(*this);
    result.unite(other);
    return result;
}

template<typename T>
void TAABB<T>::unite(const TAABB &other) {
    m_llf.x = std::min(m_llf.x, other.m_llf.x);
    m_llf.y = std::min(m_llf.y, other.m_llf.y);
    m_llf.z = std::min(m_llf.z, other.m_llf.z);
    m_rub.x = std::max(m_rub.x, other.m_rub.x);
    m_rub.y = std::max(m_rub.y, other.m_rub.y);
    m_rub.z = std::max(m_rub.z, other.m_rub.z);
}

template<typename T>
std::list<TAABB<T>> TAABB<T>::split(Axis axis) const {
    std::list<TAABB> result;
    TAABB a, b;

    split(a, b, axis);
    result.push_back(a);
    result.push_back(b);

    return result;
}

template<typename T>
void TAABB<T>::split(TAABB &a, TAABB &b, Axis axis) const {
    glm::detail::tvec3<T> newRub(m_rub), newLlf(m_llf);
    newRub[(int)axis] -= extent(axis)/2;
    newLlf[(int)axis] += extent(axis)/2;

    a = TAABB(m_llf, newRub);
    b = TAABB(newLlf, m_rub);
}

template<typename T>
std::list<TAABB<T>> TAABB<T>::recursiveSplit(int recursions, Axis axis) const {
    assert(recursions >= 0);

    if(recursions == 0) {
        return split(axis);
    }

    std::list<TAABB> result, subResult;
    Axis nextAxis;

    subResult = split(axis);

    nextAxis = (Axis)(((int)axis + 1) % 3);

    result.splice(result.end(), subResult.front().recursiveSplit(recursions-1, nextAxis));
    result.splice(result.end(), subResult.back().recursiveSplit(recursions-1, nextAxis));

    return result;
}

template<typename T>
bool TAABB<T>::operator==(const TAABB<T> &other) const {
    return m_llf == other.llf() && m_rub == other.rub();
}

template<typename T>
TAABB<float> TAABB<T>::containing(const Sphere &sphere) {
    return TAABB<float>(
        sphere.position() - glm::vec3(sphere.radius(), sphere.radius(), sphere.radius()),
        sphere.position() + glm::vec3(sphere.radius(), sphere.radius(), sphere.radius()));
}

template<typename T>
void TAABB<T>::extend(const glm::detail::tvec3<T> &point) {
    m_rub = glm::max(m_rub, point);
    m_llf = glm::min(m_llf, point);
}
