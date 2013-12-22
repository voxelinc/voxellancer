#pragma once

#include <list>
#include <glm/glm.hpp>

#include "axis.h"

class Ray;
class Line;
class Sphere;
class WorldTransform;

template<typename T>
class TAABB
{
public:
    TAABB();
    TAABB(const glm::detail::tvec3<T> &llf, const glm::detail::tvec3<T> &rub);

    const glm::detail::tvec3<T> &llf() const;
    void setLlf(const glm::detail::tvec3<T> &llf);

    const glm::detail::tvec3<T> &rub() const;
    void setRub(const glm::detail::tvec3<T> &rub);

    T axisMin(Axis axis) const;
    T axisMax(Axis axis) const;

    glm::detail::tvec3<T> middle() const;

    virtual T extent(Axis axis) const;

    TAABB<T> moved(Axis axis, T delta) const;
    TAABB<T> moved(const glm::detail::tvec3<T> &delta) const;

    void move(Axis axis, T delta);
    void move(const glm::detail::tvec3<T> &delta);

    void expand(Axis axis, T delta);
    TAABB<T> expanded(Axis axis, T delta) const;

    bool intersects(const TAABB<T> &other) const;

    bool contains(const TAABB<T> &other) const;
    bool contains(const glm::detail::tvec3<T> &vec) const;
    bool contains(const Sphere& sphere) const;
    bool contains(const Ray& ray) const;
    bool contains(const Line& line) const;

    bool nearTo(const TAABB<T>& other) const;

    TAABB<T> united(const TAABB<T> &other) const ;
    void unite(const TAABB<T> &other);

    std::list<TAABB<T>> split(Axis axis) const;
    void split(TAABB<T> &a, TAABB<T> &b, Axis axis) const;
    std::list<TAABB<T>> recursiveSplit(int recursions, Axis axis) const;

    bool operator==(const TAABB<T> &other) const;

    void extend(const glm::detail::tvec3<T> & point);

    static TAABB<float> containing(const Sphere &sphere);

    TAABB<T> applied(const WorldTransform& transform) const;
    TAABB<T> inverseApplied(const WorldTransform& transform) const;


protected:
    glm::detail::tvec3<T> m_llf, m_rub;
};

typedef TAABB<glm::mediump_float> AABB;
typedef TAABB<int> IAABB;
typedef TAABB<unsigned char> CAABB;


#include "aabb.inl"
