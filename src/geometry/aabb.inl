#include "aabb.h"

#include <cassert>
#include <algorithm>

#include "geometry/transform.h"

#include "sphere.h"
#include "line.h"
#include "ray.h"


template<typename T>
TAABB<T>::TAABB():
    m_llf(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)),
    m_urb(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0))
{

}

template<typename T>
TAABB<T>::TAABB(const glm::detail::tvec3<T> &llf, const glm::detail::tvec3<T> &urb):
    m_llf(llf),
    m_urb(urb)
{
    assert(m_llf.x <= m_urb.x && m_llf.y <= m_urb.y && m_llf.z <= m_urb.z);
}

template<typename T>
template<typename OtherT>
TAABB<T>::TAABB(const TAABB<OtherT>& other) {
    m_llf = static_cast<glm::detail::tvec3<T>>(other.llf());
    m_urb = static_cast<glm::detail::tvec3<T>>(other.urb());
}

template<typename T>
const glm::detail::tvec3<T> &TAABB<T>::llf() const {
    return m_llf;
}

template<typename T>
void TAABB<T>::setLLF(const glm::detail::tvec3<T> &llf) {
    assert(llf.x <= m_urb.x && llf.y <= m_urb.y && llf.z <= m_urb.z);
    m_llf = llf;
}

template<typename T>
const glm::detail::tvec3<T> &TAABB<T>::urb() const {
    return m_urb;
}

template<typename T>
void TAABB<T>::setURB(const glm::detail::tvec3<T> &urb) {
    assert(m_llf.x <= urb.x && m_llf.y <= urb.y && m_llf.z <= urb.z);
    m_urb = urb;
}

template<typename T>
T TAABB<T>::axisMin(Axis axis) const {
    return m_llf[(int)axis];
}

template<typename T>
T TAABB<T>::axisMax(Axis axis) const {
    return m_urb[(int)axis];
}

template<typename T>
glm::detail::tvec3<T> TAABB<T>::middle() const {
    return (m_urb + m_llf) / static_cast<T>(2);
}

template<typename T>
T TAABB<T>::extent(Axis axis) const {
    return m_urb[(int)axis] - m_llf[(int)axis];
}

template<typename T>
glm::detail::tvec3<T> TAABB<T>::extent() const {
    return m_urb - m_llf;
}

template<typename T>
T TAABB<T>::diameter() const {
    return static_cast<T>(glm::length(glm::vec3(m_urb - m_llf)));
}

template<typename T>
TAABB<T> TAABB<T>::moved(Axis axis, T delta) const {
    TAABB result(*this);
    result.move(axis, delta);
    return result;
}

template<typename T>
TAABB<T> TAABB<T>::moved(const glm::detail::tvec3<T> &delta) const {
    return TAABB(m_llf + delta, m_urb + delta);
}

template<typename T>
void TAABB<T>::move(Axis axis, T delta) {
    m_llf[(int)axis] += delta;
    m_urb[(int)axis] += delta;
}

template<typename T>
void TAABB<T>::move(const glm::detail::tvec3<T>& delta) {
    m_llf += delta;
    m_urb += delta;
}

template<typename T>
void TAABB<T>::expand(Axis axis, T delta) {
    if(delta > 0) {
        m_urb[(int)axis] += delta;
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
        if(other.llf().x >= m_urb.x) {
            return false;
        }
    } else {
        if(m_llf.x >= other.urb().x) {
            return false;
        }
    }

    if(m_llf.y < other.llf().y) {
        if(other.llf().y >= m_urb.y) {
            return false;
        }
    } else {
        if(m_llf.y >= other.urb().y) {
            return false;
        }
    }

    if(m_llf.z < other.llf().z) {
        if(other.llf().z >= m_urb.z) {
            return false;
        }
    } else {
        if(m_llf.z >= other.urb().z) {
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
bool TAABB<T>::containedBy(const TAABB<int>& other) const {
    return
        other.llf().x <= m_llf.x &&
        other.llf().y <= m_llf.y &&
        other.llf().z <= m_llf.z &&
        other.urb().x >= m_urb.x &&
        other.urb().y >= m_urb.y &&
        other.urb().z >= m_urb.z;
}

template<typename T>
bool TAABB<T>::contains(const TAABB& other) const {
    return
        m_llf.x <= other.m_llf.x &&
        m_llf.y <= other.m_llf.y &&
        m_llf.z <= other.m_llf.z &&
        m_urb.x >= other.m_urb.x &&
        m_urb.y >= other.m_urb.y &&
        m_urb.z >= other.m_urb.z;
}

template<typename T>
template<typename OtherT>
bool TAABB<T>::contains(const glm::detail::tvec3<OtherT> &vec) const {
    return
        vec.x >= m_llf.x &&
        vec.y >= m_llf.y &&
        vec.z >= m_llf.z &&
        vec.x <= m_urb.x &&
        vec.y <= m_urb.y &&
        vec.z <= m_urb.z;
}

template<typename T>
bool TAABB<T>::nearTo(const TAABB<int>& other) const {
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
    m_urb.x = std::max(m_urb.x, other.m_urb.x);
    m_urb.y = std::max(m_urb.y, other.m_urb.y);
    m_urb.z = std::max(m_urb.z, other.m_urb.z);
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
    glm::detail::tvec3<T> newRub(m_urb), newLlf(m_llf);
    newRub[(int)axis] -= extent(axis)/2;
    newLlf[(int)axis] += extent(axis)/2;

    a = TAABB(m_llf, newRub);
    b = TAABB(newLlf, m_urb);
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
    return m_llf == other.llf() && m_urb == other.urb();
}

template<typename T>
TAABB<float> TAABB<T>::containing(const Sphere &sphere) {
    return TAABB<float>(
        sphere.position() - glm::vec3(sphere.radius(), sphere.radius(), sphere.radius()),
        sphere.position() + glm::vec3(sphere.radius(), sphere.radius(), sphere.radius()));
}

template<typename T>
void TAABB<T>::extend(const glm::detail::tvec3<T> &point) {
    m_urb = glm::max(m_urb, point);
    m_llf = glm::min(m_llf, point);
}
