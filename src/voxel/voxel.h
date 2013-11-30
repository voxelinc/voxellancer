#pragma once

#include <functional>

#include <glm/glm.hpp>
#include "geometry/sphere.h"


typedef glm::detail::tvec3<unsigned char> cvec3;

namespace std {
    template<> struct hash<glm::ivec3>
    {
        std::size_t operator()(const glm::ivec3 &v) const {
            return v.x + (v.y << 8) + (v.z << 16);
        }
    };
}

class Voxel
{
public:
    Voxel(const glm::ivec3 &gridCell, const cvec3 &color, float mass = 1.0f);
    virtual ~Voxel();

    virtual Voxel *clone();

    const glm::ivec3 &gridCell() const;

    const cvec3 &color() const;

    float hp() const;
    void applyDamage(float deltaHp);

    float mass() const;

    virtual void onDestruction();



protected:
    glm::ivec3 m_gridCell;
    cvec3 m_color;
    float m_hp;
    float m_mass;
};

